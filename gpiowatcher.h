#ifndef GPIOWATCHER_H
#define GPIOWATCHER_H

#include <QThread>
#include <wiringpi.h>


class GPIOWatcher : public QThread {
    Q_OBJECT

public:
    GPIOWatcher(int pin, QObject* parent = nullptr);
    void run() override;

signals:
    void onGPIOChanged(int pin, bool state);

private:
    int pin;
    int state = LOW;
};

#endif // GPIOWATCHER_H
