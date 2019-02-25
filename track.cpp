#include "track.h"

Track::Track() {
}

void Track::update(QByteArray xml) {
    XmlParser::parse(this, xml);
}

QString Track::title() {
    return _title;
}

void Track::setTitle(QString title) {
    _title = title;
}


QString Track::artist() {
    return _artist;
}

void Track::setArtist(QString artist) {
    _artist = artist;
}

QString Track::path() {
    return _path;
}

void Track::setPath(QString path) {
    _path = path;
}


unsigned short Track::time() {
    return _time;
}

void Track::setTime(unsigned short time) {
    _time = time;
}

unsigned short Track::duration() {
    return _duration;
}

void Track::setDuration(unsigned short duration) {
    _duration = duration;
}

unsigned short Track::year() {
    return _year;
}

void Track::setYear(unsigned short year) {
    _year = year;
}

unsigned short Track::id() {
    return _id;
}

void Track::setId(unsigned short id) {
    _id = id;
}

QString Track::toString() {
    return QString("title : %1 ; artist : %2 ; time : %3 ; duration : %4 ; year : %5 ; path : %6 ; id : %7")
            .arg(_title)
            .arg(_artist)
            .arg(_time)
            .arg(_duration)
            .arg(_year)
            .arg(_path)
            .arg(_id);
}
