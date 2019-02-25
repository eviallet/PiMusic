#include "xmlparser.h"

QByteArray XmlParser::_xml;

void XmlParser::parse(Track *track, QByteArray& xml) {
    XmlParser::_xml = xml;

    track->setTitle(infoValue("title"));
    track->setArtist(infoValue("artist"));
    track->setPath(infoValue("filename"));
    track->setYear(infoValue("date").toShort());


    track->setId(attributeValue("currentplid").toShort());
    track->setDuration(attributeValue("length").toShort());
    track->setTime(attributeValue("time").toShort());

    if(track->title().length()>100)
        track->setTitle(track->path().left(track->path().length()-4)); // path without extension
    if(track->artist().length()>100)
        track->setArtist("Unknown Artist");
}

// <attr>value</attr>
QString XmlParser::attributeValue(QString attr) {
    QString first = QString("<%1>").arg(attr);
    QString last = QString("</%1>").arg(attr);
    int firstIndex = XmlParser::_xml.indexOf(first)+first.length();

    return QUrl::fromPercentEncoding(
        XmlParser::_xml.mid(
               firstIndex,
               XmlParser::_xml.indexOf(last,firstIndex)-firstIndex
        )
    ).replace("&amp;#39;","\'").replace("&amp;amp;","&");
}

// <info name='attr'>value</info>
QString XmlParser::infoValue(QString attr) {
    QString first = QString("<info name=\'%1\'>").arg(attr);
    QString last = QString("</info>");
    int firstIndex = XmlParser::_xml.indexOf(first)+first.length();

    return QUrl::fromPercentEncoding(
        XmlParser::_xml.mid(
               firstIndex,
               XmlParser::_xml.indexOf(last,firstIndex)-firstIndex
        )
    ).replace("&amp;#39;","\'").replace("&amp;amp;","&");
}
