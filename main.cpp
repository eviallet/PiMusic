#include <QCoreApplication>
#include <wiringpi.h>
#include "lcdscreen.h"
#include "gpiowatcher.h"
#include "config.h"
#include "mediaplayer.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    wiringPiSetup();

    MediaPlayer *vlc = new MediaPlayer();
    LCDScreen *lcd = new LCDScreen();

    a.connect(vlc, &MediaPlayer::onTrackChanged, lcd, &LCDScreen::onTrackChanged);

    // assign actions to buttons conected to GPIOs
    GPIOWatcher *play = new GPIOWatcher(conf->getSubInt("gpio","play"));
    GPIOWatcher *previous = new GPIOWatcher(conf->getSubInt("gpio","prev"));
    GPIOWatcher *next = new GPIOWatcher(conf->getSubInt("gpio","next"));
    GPIOWatcher *remove = new GPIOWatcher(conf->getSubInt("gpio","remv"));
    GPIOWatcher *like = new GPIOWatcher(conf->getSubInt("gpio","like"));

    // connect GPIOs to the media player
    a.connect(play, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::play);
    a.connect(previous, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::previous);
    a.connect(next, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::next);
    a.connect(remove, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::remove);
    a.connect(like, &GPIOWatcher::onGPIOChanged, vlc, &MediaPlayer::like);


    return a.exec();
}
