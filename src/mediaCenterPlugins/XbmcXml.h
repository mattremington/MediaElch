#ifndef XBMCXML_H
#define XBMCXML_H

#include "data/Concert.h"
#include "data/MediaCenterInterface.h"
#include "music/Album.h"
#include "music/Artist.h"

#include <QByteArray>
#include <QDomDocument>
#include <QList>
#include <QObject>
#include <QString>
#include <QXmlStreamWriter>

class Movie;
class TvShow;
class TvShowEpisode;
class Subtitle;

/**
 * @brief The XbmcXml class
 */
class XbmcXml : public MediaCenterInterface
{
    Q_OBJECT
public:
    explicit XbmcXml(QObject *parent = nullptr);
    ~XbmcXml() override;

    bool saveMovie(Movie *movie) override;
    bool loadMovie(Movie *movie, QString initialNfoContent = "") override;
    bool saveConcert(Concert *concert) override;
    bool loadConcert(Concert *concert, QString initialNfoContent = "") override;
    void loadConcertImages(Concert *concert);
    bool loadTvShow(TvShow *show, QString initialNfoContent = "") override;
    bool loadTvShowEpisode(TvShowEpisode *episode, QString initialNfoContent = "") override;
    bool saveTvShow(TvShow *show) override;
    bool saveTvShowEpisode(TvShowEpisode *episode) override;
    bool hasFeature(int feature) override;
    QStringList extraFanartNames(Movie *movie) override;
    QStringList extraFanartNames(Concert *concert) override;
    QStringList extraFanartNames(TvShow *show) override;
    QStringList extraFanartNames(Artist *artist) override;
    QImage movieSetPoster(QString setName) override;
    QImage movieSetBackdrop(QString setName) override;
    void saveMovieSetPoster(QString setName, QImage poster) override;
    void saveMovieSetBackdrop(QString setName, QImage backdrop) override;

    bool saveArtist(Artist *artist) override;
    bool saveAlbum(Album *album) override;
    bool loadArtist(Artist *artist, QString initialNfoContent = "") override;
    bool loadAlbum(Album *album, QString initialNfoContent = "") override;

    QString actorImageName(Movie *movie, Actor actor) override;
    QString actorImageName(TvShow *show, Actor actor) override;
    QString actorImageName(TvShowEpisode *episode, Actor actor) override;

    QString imageFileName(const Movie *movie,
        ImageType type,
        QList<DataFile> dataFiles = QList<DataFile>(),
        bool constructName = false) override;
    QString imageFileName(const Concert *concert,
        ImageType type,
        QList<DataFile> dataFiles = QList<DataFile>(),
        bool constructName = false) override;
    QString imageFileName(const TvShowEpisode *episode,
        ImageType type,
        QList<DataFile> dataFiles = QList<DataFile>(),
        bool constructName = false) override;
    QString imageFileName(const TvShow *show,
        ImageType type,
        SeasonNumber season = SeasonNumber::NoSeason,
        QList<DataFile> dataFiles = QList<DataFile>(),
        bool constructName = false) override;
    QString imageFileName(const Artist *artist,
        ImageType type,
        QList<DataFile> dataFiles = QList<DataFile>(),
        bool constructName = false) override;
    QString imageFileName(const Album *album,
        ImageType type,
        QList<DataFile> dataFiles = QList<DataFile>(),
        bool constructName = false) override;

    QString nfoFilePath(Movie *movie) override;
    QString nfoFilePath(Concert *concert) override;
    QString nfoFilePath(TvShowEpisode *episode) override;
    QString nfoFilePath(TvShow *show) override;
    QString nfoFilePath(Artist *artist) override;
    QString nfoFilePath(Album *album) override;

    static void writeTvShowEpisodeXml(QXmlStreamWriter &xml, TvShowEpisode *episode);
    static void writeStreamDetails(QXmlStreamWriter &xml, StreamDetails *streamDetails);
    static void writeStreamDetails(QDomDocument &doc,
        const StreamDetails *streamDetails,
        QList<Subtitle *> subtitles = QList<Subtitle *>());
    static void setListValue(QDomDocument &doc, const QString &name, const QStringList &values);
    static QDomElement addTextValue(QDomDocument &doc, const QString &name, const QString &value);
    static void appendXmlNode(QDomDocument &doc, QDomNode &node);
    static void removeChildNodes(QDomDocument &doc, const QString &name);
    static QDomElement setTextValue(QDomDocument &doc, const QString &name, const QString &value);

    void loadBooklets(Album *album) override;

private:
    QByteArray getMovieXml(Movie *movie);
    QByteArray getConcertXml(Concert *concert);
    QByteArray getTvShowXml(TvShow *show);
    QByteArray getArtistXml(Artist *artist);
    QByteArray getAlbumXml(Album *album);
    bool loadStreamDetails(StreamDetails *streamDetails, QDomDocument domDoc);
    void loadStreamDetails(StreamDetails *streamDetails, QDomElement elem);
    bool saveFile(QString filename, QByteArray data);
    QString getPath(const Movie *movie);
    QString getPath(const Concert *concert);
    QString movieSetFileName(QString setName, DataFile *dataFile);
};

#endif // XBMCXML_H
