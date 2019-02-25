#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "config.h"
#include "mediaplayer.h"
#include "gpiowatcher.h"

//#define RPI
#define WINOS


namespace Ui {
    class PlayerWindow;
}

class PlayerWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit PlayerWindow(QWidget *parent = nullptr);
    ~PlayerWindow();

public slots:
    void onTrackChanged(Track track);

private:
    Ui::PlayerWindow *ui;
    MediaPlayer *vlc;

    GPIOWatcher *play;
    GPIOWatcher *previous;
    GPIOWatcher *next;
    GPIOWatcher *remove;
    GPIOWatcher *like;
    QString getDisplayableTime(unsigned short secs, bool showHours);
};

#endif // PLAYERWINDOW_H
