//=====[Libraries]=============================================================
#include "mbed.h"

//=====[Declaration of private defines]========================================
#define DEAD_TIME_FOR_DEBOUNCING 200ms

//=====[Implementations of public functions]===================================
void microcontrollerDelay() {
    ThisThread::sleep_for(DEAD_TIME_FOR_DEBOUNCING);
}