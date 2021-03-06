#ifndef IMAGEPROVIDERINTERFACE_H
#define IMAGEPROVIDERINTERFACE_H

#include <QList>
#include <QMap>
#include <QSettings>
#include <QString>

#include "data/Concert.h"
#include "data/EpisodeNumber.h"
#include "data/Movie.h"
#include "data/SeasonNumber.h"
#include "data/TvShow.h"
#include "globals/Globals.h"


/**
 * @brief The ImageProviderInterface class
 */
class ImageProviderInterface : public QObject
{
public:
    virtual QString name() = 0;
    virtual QString identifier() = 0;
    virtual void movieImages(Movie *movie, TmdbId tmdbId, QList<ImageType> types) = 0;
    virtual void moviePosters(TmdbId tmdbId) = 0;
    virtual void movieBackdrops(TmdbId tmdbId) = 0;
    virtual void movieLogos(TmdbId tmdbId) = 0;
    virtual void movieBanners(TmdbId tmdbId) = 0;
    virtual void movieThumbs(TmdbId tmdbId) = 0;
    virtual void movieClearArts(TmdbId tmdbId) = 0;
    virtual void movieCdArts(TmdbId tmdbId) = 0;
    virtual void concertImages(Concert *concert, TmdbId tmdbId, QList<ImageType> types) = 0;
    virtual void concertPosters(TmdbId tmdbId) = 0;
    virtual void concertBackdrops(TmdbId tmdbId) = 0;
    virtual void concertLogos(TmdbId tmdbId) = 0;
    virtual void concertClearArts(TmdbId tmdbId) = 0;
    virtual void concertCdArts(TmdbId tmdbId) = 0;
    virtual void tvShowImages(TvShow *show, TvDbId tvdbId, QList<ImageType> types) = 0;
    virtual void tvShowPosters(TvDbId tvdbId) = 0;
    virtual void tvShowBackdrops(TvDbId tvdbId) = 0;
    virtual void tvShowLogos(TvDbId tvdbId) = 0;
    virtual void tvShowClearArts(TvDbId tvdbId) = 0;
    virtual void tvShowCharacterArts(TvDbId tvdbId) = 0;
    virtual void tvShowBanners(TvDbId tvdbId) = 0;
    virtual void tvShowEpisodeThumb(TvDbId tvdbId, SeasonNumber season, EpisodeNumber episode) = 0;
    virtual void tvShowSeason(TvDbId tvdbId, SeasonNumber season) = 0;
    virtual void tvShowSeasonBanners(TvDbId tvdbId, SeasonNumber season) = 0;
    virtual void tvShowSeasonBackdrops(TvDbId tvdbId, SeasonNumber season) = 0;
    virtual void tvShowSeasonThumbs(TvDbId tvdbId, SeasonNumber season) = 0;
    virtual void tvShowThumbs(TvDbId tvdbId) = 0;
    virtual void artistFanarts(QString mbId) = 0;
    virtual void artistLogos(QString mbId) = 0;
    virtual void artistThumbs(QString mbId) = 0;
    virtual void albumCdArts(QString mbId) = 0;
    virtual void albumThumbs(QString mbId) = 0;
    virtual void albumBooklets(QString mbId) = 0;
    virtual void artistImages(Artist *artist, QString mbId, QList<ImageType> types) = 0;
    virtual void albumImages(Album *album, QString mbId, QList<ImageType> types) = 0;
    virtual QList<ImageType> provides() = 0;
    virtual bool hasSettings() = 0;
    virtual void loadSettings(QSettings &settings) = 0;
    virtual void saveSettings(QSettings &settings) = 0;
    virtual QWidget *settingsWidget() = 0;
    virtual QUrl siteUrl() = 0;

public slots:
    virtual void searchMovie(QString searchStr, int limit) = 0;
    virtual void searchConcert(QString searchStr, int limit) = 0;
    virtual void searchTvShow(QString searchStr, int limit) = 0;
    virtual void searchArtist(QString searchStr, int limit) = 0;
    virtual void searchAlbum(QString artistName, QString searchStr, int limit) = 0;
signals:
    virtual void sigSearchDone(QList<ScraperSearchResult>) = 0;
    virtual void sigImagesLoaded(QList<Poster>) = 0;
    virtual void sigImagesLoaded(Movie *, QMap<ImageType, QList<Poster>>) = 0;
    virtual void sigImagesLoaded(Concert *, QMap<ImageType, QList<Poster>>) = 0;
    virtual void sigImagesLoaded(TvShow *, QMap<ImageType, QList<Poster>>) = 0;
    virtual void sigImagesLoaded(Artist *, QMap<ImageType, QList<Poster>>) = 0;
    virtual void sigImagesLoaded(Album *, QMap<ImageType, QList<Poster>>) = 0;
};

Q_DECLARE_METATYPE(ImageProviderInterface *)
Q_DECLARE_OPAQUE_POINTER(ImageProviderInterface *)

#endif // IMAGEPROVIDERINTERFACE_H
