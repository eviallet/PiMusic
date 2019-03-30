#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>


#define conf Config::getInstance()


class Config {
public:
    static Config* getInstance() {
        static Config* instance = new Config();
        return instance;
    }

    QString getString(QString key) {
        return json[key].toString();
    }

    int getInt(QString key) {
        return json[key].toInt();
    }

    QString getSubString(QString key, QString subkey) {
        return json[key].toObject()[subkey].toString();
    }

    int getSubInt(QString key, QString subkey) {
        return json[key].toObject()[subkey].toInt();
    }

private:
    Config() {
    #ifdef  Q_OS_WIN
        QFile file("C:\\Users\\Gueg\\OneDrive\\Progra\\PiMusic\\config.json");
    #else //Q_OS_LINUX
        QFile file("/home/pi/pimusic/config.json");
    #endif
        if(file.open(QFile::ReadOnly)) {
            QByteArray str = file.readAll();
            file.close();
            json = QJsonDocument::fromJson(str).object();
        } else
            qCritical() << "Couldn't open file : " << file.errorString();
    }

    QJsonObject json;
};


#endif // CONFIG_H
