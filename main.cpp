#include "playerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(
        "QProgressBar {"
            "background-color: #000000;"
            "border-style: solid;"
            "border-width: 2px;"
            "border-color: #222222;"
            "border-radius: 9px;"
        "}"

        "QProgressBar::chunk {"
            "background-color: #F47B22;"
            "border: 1px;"
            "border-radius: 8px;"
        "}"
    );

    PlayerWindow w;
    w.show();

    return a.exec();
}
