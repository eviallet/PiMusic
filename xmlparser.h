#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "track.h"
#include <QByteArray>
#include <QString>
#include <QUrl>

class XmlParser {
public:
    static QByteArray _xml;
    static void parse(Track *track, QByteArray& xml);
private:
    static QString attributeValue(QString attr);    // <attr>value</attr>
    static QString infoValue(QString attr);         // <info name='attr'>value</info>

};


#endif // XMLPARSER_H
