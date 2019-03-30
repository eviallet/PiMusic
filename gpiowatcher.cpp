#include "gpiowatcher.h"

GPIOWatcher::GPIOWatcher(int pin, QObject *parent) : QThread(parent), pin(pin) {
    pinMode(pin, INPUT);
}

void GPIOWatcher::run() {
    int newState = LOW;
    while(true) {
        if((newState=digitalRead(pin)) != state) {
            state = newState;
            emit onGPIOChanged(pin, state);
        }
        wait(50); // ms
    }

}

