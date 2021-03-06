#!/usr/bin/env bash

#
# Functions for packaging MediaElch.
# Source this script and make sure to have utils.sh loaded
#

set -e

# Creates an .AppImage file that can be distributed.
package_appimage() {
	check_dependencies_linux_appimage

	$SCRIPT_DIR/build_release.sh linux

	pushd "${BUILD_DIR}" > /dev/null
	echo ""
	print_important "Create an AppImage release"

	# Workaround for: https://github.com/probonopd/linuxdeployqt/issues/65
	unset QTDIR; unset QT_PLUGIN_PATH; unset LD_LIBRARY_PATH
	# linuxdeployqt uses this for naming the file
	export VERSION=${ME_VERSION}

	if [[ ! "$PATH" = *"qt"* ]]; then
		print_critical "/path/to/qt/bin must be in your \$PATH, e.g. \nexport PATH=\"\$PATH:/usr/lib/x86_64-linux-gnu/qt5/bin\""
	fi

	if [[ "$(qmlimportscanner)" = *"could not find a Qt installation"* ]]; then
		print_critical "qmlimportscanner could not find a Qt installation.\nInstall qtdeclarative5-dev-tools\"."
	fi

	#######################################################
	# Download linuxdeployqt

	echo ""
	print_info "Downloading linuxdeployqt"
	DEPLOYQT="${PROJECT_DIR}/linuxdeployqt.AppImage"
	if [ ! -f $DEPLOYQT ]; then
		wget --output-document "${PROJECT_DIR}/linuxdeployqt.AppImage" \
			https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
	fi
	chmod u+x $DEPLOYQT

	#######################################################
	# Install MediaElch into subdirectory

	echo ""
	print_info "Installing MediaElch in subdirectory to create basic AppDir structure"
	make INSTALL_ROOT=appdir -j $(nproc) install
	find appdir/

	#######################################################
	# Copy libmediainfo
	# 
	# libmediainfo.so.0 is loaded at runtime that's why
	# linuxdeployqt can't detect it and we have to include
	# it here.

	echo ""
	print_info "Copying libmediainfo.so"
	mkdir -p ./appdir/usr/lib
	cp /usr/lib/x86_64-linux-gnu/libmediainfo.so.0 ./appdir/usr/lib/

	#######################################################
	# Download and copy ffmpeg

	echo ""
	print_info "Downloading ffmpeg"
	# Use static ffmpeg
	wget -c https://johnvansickle.com/ffmpeg/releases/ffmpeg-release-64bit-static.tar.xz -O ffmpeg.tar.xz
	tar -xJvf ffmpeg.tar.xz
	print_info "Copying ffmpeg into AppDir"
	cp ffmpeg-*/ffmpeg appdir/usr/bin/

	#######################################################
	# Create AppImage

	echo ""
	print_important "Creating an AppImage for MediaElch ${VERSION_NAME}. This takes a while and may seem frozen."
	$DEPLOYQT appdir/usr/share/applications/MediaElch.desktop -verbose=1 -bundle-non-qt-libs -qmldir=../src/ui
	$DEPLOYQT --appimage-extract
	export PATH=$(readlink -f ./squashfs-root/usr/bin):$PATH
	# Workaround to increase compatibility with older systems
	# see https://github.com/darealshinji/AppImageKit-checkrt for details
	mkdir -p appdir/usr/optional/libstdc++/
	wget -c https://github.com/darealshinji/AppImageKit-checkrt/releases/download/continuous/exec-x86_64.so -O ./appdir/usr/optional/exec.so
	cp /usr/lib/x86_64-linux-gnu/libstdc++.so.6 ./appdir/usr/optional/libstdc++/
	rm appdir/AppRun
	wget -c https://github.com/darealshinji/AppImageKit-checkrt/releases/download/continuous/AppRun-patched-x86_64 -O appdir/AppRun
	chmod a+x appdir/AppRun
	./squashfs-root/usr/bin/appimagetool -g ./appdir/ MediaElch-${VERSION}-x86_64.AppImage
	find . -executable -type f -exec ldd {} \; | grep " => /usr" | cut -d " " -f 2-3 | sort | uniq

	#######################################################
	# Finalize AppImage (name, chmod)

	echo ""
	print_info "Renaming .AppImage"
	mv MediaElch-${VERSION}*.AppImage MediaElch_linux_${VERSION_NAME}.AppImage
	chmod +x *.AppImage

	print_success "Successfully created AppImage: "
	print_success "    $(pwd)/MediaElch_linux_${VERSION_NAME}.AppImage"
	popd > /dev/null
}
