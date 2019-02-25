#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include "track.h"
#include "config.h"

class MediaPlayer : public QObject {
    Q_OBJECT
public:
    explicit MediaPlayer(QObject *parent = nullptr);
    void currentTrack();
public slots:
    void play();
    void previous();
    void next();
    void remove();
    void like();
signals:
    void onTrackChanged(Track);
private:
    QProcess *player;
    QNetworkAccessManager *network;
    QUrl url;
    QTimer *timer;
    Track _currentTrack;
    Track _waitingTrack;
};

#endif // MEDIAPLAYER_H
