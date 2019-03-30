#include "lcdscreen.h"

LCDScreen::LCDScreen(QObject *parent) : QObject(parent) {
    lcd = lcdInit (2 /* rows */, 16 /* cols */, 4 /* bits */,
                   LCD_RS, LCD_E,
                   LCD_D0, LCD_D1, LCD_D2, LCD_D3,  // same constructor for 4&8 bits but unused pins
                   LCD_D4, LCD_D5, LCD_D6, LCD_D7); // used pins
    lcdPutQString(lcd, "PiMusic");
}

// TITLE
// ARTIST YEAR
void LCDScreen::lcdPutTrack(int fd, Track track) {
    lcdPutQString(fd, track.title());
    lcdPosition(fd, 0, 1);
    lcdPutQString(fd, track.artist());
    lcdPosition(fd, 16-4, 1);
    if(track.year()!=0)
        lcdPutQString(fd, QString::number(track.year()));
}

// 00:00 00:00
// =======
void LCDScreen::lcdPutTrackTime(int fd, Track track) {
    QString timeCur = getDisplayableTime(track.time(), track.duration()/3600);
    QString timeEnd = getDisplayableTime(track.duration(), track.duration()/3600);
    int progress = static_cast<int>(track.time()*16./track.duration());
    QString progressBar = "";
    for(int i=0; i<progress; i++)
        progressBar+="=";

    lcdClear(fd);
    lcdPutQString(fd, timeCur);
    lcdPosition(fd, 16-timeEnd.length(), 0);
    lcdPutQString(fd, timeEnd);
    lcdPosition(fd, 0, 1);
    lcdPutQString(fd, progressBar);
}

void LCDScreen::lcdPutQString(int fd, QString str) {
    lcdPuts(fd, str.toLatin1().data());
}

void LCDScreen::onTrackChanged(Track track) {
    if(track.title()!=curTrack.title()) {
        lcdClear(lcd);
        lcdPutTrack(lcd, track);
    } else if(showingTime) {
        lcdPutTrackTime(lcd, curTrack);
    }
}

void LCDScreen::toggleScreen() {
    isOn = !isOn;
    lcdDisplay(lcd, isOn);
}

void LCDScreen::toggleInfos() {
    showingTime = !showingTime;
    lcdClear(lcd);
    if(showingTime) lcdPutTrackTime(lcd, curTrack);
    else            lcdPutTrack(lcd, curTrack);
}

QString LCDScreen::getDisplayableTime(unsigned short secs, bool showHours) {
    return (showHours?QString("%1:").arg(secs/3600, 2, 10, QChar('0')):"")+QString("%1:%2").arg(secs/60, 2, 10, QChar('0')).arg(secs%60, 2, 10, QChar('0'));
}

LCDScreen::~LCDScreen() {
}

