#include "EpisodeNumber.h"

#include <QRegExp>
#include <QString>

EpisodeNumber::EpisodeNumber(int episodeNumber) :
    // Any number lower than 0 is regarded invalid => no episode number
    m_episodeNumber(episodeNumber > -1 ? episodeNumber : -1)
{
}

const EpisodeNumber EpisodeNumber::NoEpisode = EpisodeNumber(-2);

bool EpisodeNumber::operator==(const EpisodeNumber &other) const
{
    // Only valid IMDb id's are comparable
    return m_episodeNumber == other.m_episodeNumber;
}

bool EpisodeNumber::operator!=(const EpisodeNumber &other) const
{
    return !(*this == other);
}

bool EpisodeNumber::operator>(const EpisodeNumber &other) const
{
    return m_episodeNumber > other.m_episodeNumber;
}

bool EpisodeNumber::operator<(const EpisodeNumber &other) const
{
    return m_episodeNumber < other.m_episodeNumber;
}

int EpisodeNumber::toInt() const
{
    return m_episodeNumber;
}

QString EpisodeNumber::toPaddedString() const
{
    if (m_episodeNumber == EpisodeNumber::NoEpisode.toInt()) {
        return QStringLiteral("xx");
    }
    return QString::number(m_episodeNumber).prepend((m_episodeNumber < 10) ? "0" : "");
}

QString EpisodeNumber::toString() const
{
    return QString::number(m_episodeNumber);
}
