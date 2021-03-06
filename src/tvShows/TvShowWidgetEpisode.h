#ifndef TVSHOWWIDGETEPISODE_H
#define TVSHOWWIDGETEPISODE_H

#include "data/TvShowEpisode.h"
#include "globals/DownloadManager.h"

#include <QLabel>
#include <QPointer>
#include <QTableWidgetItem>
#include <QWidget>

namespace Ui {
class TvShowWidgetEpisode;
}

/**
 * @brief The TvShowWidgetEpisode class
 */
class TvShowWidgetEpisode : public QWidget
{
    Q_OBJECT

public:
    explicit TvShowWidgetEpisode(QWidget *parent = nullptr);
    ~TvShowWidgetEpisode() override;
    void setEpisode(TvShowEpisode *episode);
    void updateEpisodeInfo();

public slots:
    void onSetEnabled(bool enabled);
    void onClear();
    void onSaveInformation();
    void onStartScraperSearch();

signals:
    void sigSetActionSearchEnabled(bool, MainWidgets);
    void sigSetActionSaveEnabled(bool, MainWidgets);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onAddDirector();
    void onRemoveDirector();
    void onAddWriter();
    void onRemoveWriter();
    void onChooseThumbnail();
    void onDeleteThumbnail();
    void onImageDropped(ImageType imageType, QUrl imageUrl);
    void onPosterDownloadFinished(DownloadManagerElement elem);
    void onLoadDone();
    void onRevertChanges();
    void onCaptureImage();

    void onNameChange(QString text);
    void onShowTitleChange(QString text);
    void onSeasonChange(int value);
    void onEpisodeChange(int value);
    void onDisplaySeasonChange(int value);
    void onDisplayEpisodeChange(int value);
    void onRatingChange(double value);
    void onVotesChange(int value);
    void onTop250Change(int value);
    void onCertificationChange(QString text);
    void onFirstAiredChange(QDate date);
    void onPlayCountChange(int value);
    void onLastPlayedChange(QDateTime dateTime);
    void onStudioChange(QString text);
    void onEpBookmarkChange(QTime time);
    void onOverviewChange();
    void onDirectorEdited(QTableWidgetItem *item);
    void onWriterEdited(QTableWidgetItem *item);
    void onStreamDetailsEdited();
    void onReloadStreamDetails();
    void updateStreamDetails(bool reloadFromFile = false);

    void onAddActor();
    void onRemoveActor();
    void onActorChanged();
    void onChangeActorImage();
    void onActorEdited(QTableWidgetItem *item);

private:
    Ui::TvShowWidgetEpisode *ui;
    QPointer<TvShowEpisode> m_episode;
    QLabel *m_savingWidget;
    QMovie *m_loadingMovie;
    DownloadManager *m_posterDownloadManager;
    QList<QWidget *> m_streamDetailsWidgets;
    QList<QList<QLineEdit *>> m_streamDetailsAudio;
    QList<QList<QLineEdit *>> m_streamDetailsSubtitles;
};

#endif // TVSHOWWIDGETEPISODE_H
