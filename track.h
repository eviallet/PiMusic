#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QByteArray>
#include <QDebug>

class Track;

#include "xmlparser.h"

class Track {
public:
    Track();
    void update(QByteArray xml);

    QString toString();

    // getters
    unsigned short year();
    unsigned short duration();
    unsigned short time();
    unsigned short id();
    QString path();
    QString artist();
    QString title();

    // setters
    void setTitle(QString title);
    void setArtist(QString artist);
    void setPath(QString path);
    void setTime(unsigned short time);
    void setDuration(unsigned short duration);
    void setYear(unsigned short year);
    void setId(unsigned short id);

    // operators
    bool operator==(Track& other) {
        return _path==other.path()
            && _time==other.time()
            && _id==other.id();
    }

    bool operator!=(Track& other) {
        return !operator==(other);
    }
private:
    QString _title;
    QString _artist;
    QString _path;
    unsigned short _year;
    unsigned short _duration; // s
    unsigned short _time; // s
    unsigned short _id;
};

#endif // TRACK_H
