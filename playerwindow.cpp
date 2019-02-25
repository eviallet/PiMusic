#include "playerwindow.h"
#include "ui_playerwindow.h"

PlayerWindow::PlayerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayerWindow),
    play(new GPIOWatcher(conf->getSubInt("gpio","play"), this)),
    previous(new GPIOWatcher(conf->getSubInt("gpio","prev"), this)),
    next(new GPIOWatcher(conf->getSubInt("gpio","next"), this)),
    remove(new GPIOWatcher(conf->getSubInt("gpio","remv"), this)),
    like(new GPIOWatcher(conf->getSubInt("gpio","like"), this))
{
    ui->setupUi(this);

    setFixedWidth(conf->getSubInt("geometry","width"));
    setFixedHeight(conf->getSubInt("geometry","height"));

    vlc = new MediaPlayer(this);

#ifdef RPI
    // connect GPIOs to the media player
    connect(play, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::play);
    connect(previous, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::previous);
    connect(next, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::next);
    connect(remove, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::remove);
    connect(like, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::like);

    // connect GPIOs to the UI
    connect(play, &GPIOWatcher::onGPIOChanged, ui->btnPlay, &QPushButton::setChecked);
    connect(previous, &GPIOWatcher::onGPIOChanged, ui->btnPrevious, &QPushButton::setChecked);
    connect(next, &GPIOWatcher::onGPIOChanged, ui->btnNext, &QPushButton::setChecked);
    connect(remove, &GPIOWatcher::onGPIOChanged, ui->btnRemove, &QPushButton::setChecked);
    connect(like, &GPIOWatcher::onGPIOChanged, ui->btnLike, &QPushButton::setChecked);
#endif

#ifdef WINOS
    // connect UI to media player
    connect(ui->btnPlay, &QPushButton::clicked, vlc, &MediaPlayer::play);
    connect(ui->btnPrevious, &QPushButton::clicked, vlc, &MediaPlayer::previous);
    connect(ui->btnNext, &QPushButton::clicked, vlc, &MediaPlayer::next);
    connect(ui->btnRemove, &QPushButton::clicked, vlc, &MediaPlayer::remove);
    connect(ui->btnLike, &QPushButton::clicked, vlc, &MediaPlayer::like);
#endif

    connect(vlc, &MediaPlayer::onTrackChanged, this, &PlayerWindow::onTrackChanged);
}

void PlayerWindow::onTrackChanged(Track track) {
    ui->trackTitle->setText(track.title());
    ui->trackArtist->setText(track.artist());

    ui->trackTimeCurrent->setText(getDisplayableTime(track.time(), track.duration()/3600));
    ui->trackTimeEnd->setText(getDisplayableTime(track.duration(), track.duration()/3600));
    ui->trackProgress->setValue(track.time()*100./track.duration());

    if(track.year()!=0)
        ui->trackYear->setText(QString::number(track.year()));
    else
        ui->trackYear->hide();
}

QString PlayerWindow::getDisplayableTime(unsigned short secs, bool showHours) {
    return (showHours?QString("%1:").arg(secs/3600, 2, 10, QChar('0')):"")+QString("%1:%2").arg(secs/60, 2, 10, QChar('0')).arg(secs%60, 2, 10, QChar('0'));
}

PlayerWindow::~PlayerWindow() {
    delete ui;
}

