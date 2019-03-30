#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QByteArray>

#include <wiringpi.h>
#include <lcd.h>
#include "track.h"

#define LCD_RS  24               //Register select pin
#define LCD_E   25               //Enable Pin

#define LCD_D4  23               //Data pin D4
#define LCD_D5  27               //Data pin D5
#define LCD_D6  28               //Data pin D6
#define LCD_D7  29               //Data pin D7

#define LCD_D0  0
#define LCD_D1  0
#define LCD_D2  0
#define LCD_D3  0

class LCDScreen : public QObject {
    Q_OBJECT

public:
    explicit LCDScreen(QObject *parent = nullptr);
    ~LCDScreen();

public slots:
    void onTrackChanged(Track track);
    void toggleScreen();
    void toggleInfos();

private:
    QString getDisplayableTime(unsigned short secs, bool showHours);
    void lcdPutQString(int fd, QString str);
    void lcdPutTrack(int fd, Track track);
    void lcdPutTrackTime(int fd, Track track);

    int lcd;
    bool isOn = true;
    bool showingTime = false;

    Track curTrack;
};

#endif // PLAYERWINDOW_H
