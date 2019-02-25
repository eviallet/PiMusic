#include "mediaplayer.h"

MediaPlayer::MediaPlayer(QObject *parent) : QObject(parent) {
    network = new QNetworkAccessManager();

    url = QUrl(QString("http://%1:%2/requests/status.xml")
               .arg(conf->getSubString("http","host"))
               .arg(conf->getSubInt("http","port")));
    url.setPassword(conf->getSubString("http","pswd"));

    QStringList args;
    args << "-I" << "http"
         << "--http-host" << conf->getSubString("http","host")
         << "--http-port" << QString::number(conf->getSubInt("http","port"))
         << "--http-password" << conf->getSubString("http","pswd")
         << "-LZ" << conf->getString("music_dir");

    player = new QProcess(this);
    player->start(conf->getString("vlc_path"), args);

    timer = new QTimer();
    timer->setInterval(100);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &MediaPlayer::currentTrack);

    timer->start();
}


void MediaPlayer::play() {
    timer->stop();

    QUrlQuery query;
    query.addQueryItem("command", "pl_pause");
    url.setQuery(query);

    network->get(QNetworkRequest(url));

    currentTrack();
}

void MediaPlayer::previous() {
    timer->stop();

    // first press will replay current song
    if(_currentTrack.time()>10) {
        QUrlQuery query;
        query.addQueryItem("command", QString("pl_play&id=%1").arg(_currentTrack.id()));
        url.setQuery(query);

        network->get(QNetworkRequest(url));
    } else {
        QUrlQuery query;
        query.addQueryItem("command", "pl_previous");
        url.setQuery(query);

        network->get(QNetworkRequest(url));
    }

    currentTrack();
}

void MediaPlayer::next() {
    timer->stop();

    QUrlQuery query;
    query.addQueryItem("command", "pl_next");
    url.setQuery(query);

    network->get(QNetworkRequest(url));

    currentTrack();
}

void MediaPlayer::remove() {
    Track playing = _currentTrack;
    next();
    //system(QString("rm ").append(playing.path()).toLatin1().data());
}

void MediaPlayer::like() {
    //
}

void MediaPlayer::currentTrack() {
    if(url.hasQuery())
        url.setQuery(QString()); // reset the query string
    QNetworkReply* reply = network->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::readyRead, [=](){
        QByteArray track = reply->readAll();
        _waitingTrack.update(track);
        if(_waitingTrack != _currentTrack) {
            _currentTrack = _waitingTrack;
            emit onTrackChanged(_currentTrack);
        }
        delete reply;
    });

    timer->start();
}
