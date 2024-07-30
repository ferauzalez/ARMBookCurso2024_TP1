//=====[Libraries]=============================================================
#include "mbed.h"
#include "led.h"
#include "timer.h"
#include "FSM_principal.h"

//=====[Declaration and initialization of private global variables]============
static DigitalOut exerciseLED   (D15);
static DigitalOut restLED       (D14);
static DigitalOut repetitionLED (D13);

//=====[Declarations (prototypes) of private functions]========================
static void blinkLEDs           (modes_t mode);
static void changeWhichLEDIsOn  (modes_t mode);

//=====[Implementations of public functions]===================================
void updateLEDGroup() {
    bool    countdownState  = readCountdownState();
    modes_t operationMode   = readModeActive();

    if (countdownState == true) {
        blinkLEDs(operationMode);
    } else {
        changeWhichLEDIsOn(operationMode);
    }
}

//=====[Implementations of private functions]==================================
static void blinkLEDs(modes_t mode) {
    switch (mode) {
        case MODE_EXERCISE:
            exerciseLED   = !exerciseLED;
            restLED       = false;
            repetitionLED = false;
            break;
        case MODE_REST:
            exerciseLED   = false;
            restLED       = !restLED;
            repetitionLED = false;
            break;
        default: // Switch case shouldn't come here. In that case, all three LEDs would blinking for make the error more noticeable.
            exerciseLED   = !exerciseLED;
            restLED       = !restLED;
            repetitionLED = !repetitionLED;
            break;
    }
}

void changeWhichLEDIsOn(modes_t mode) {
    switch (mode) {
        case MODE_EXERCISE:
            exerciseLED   = true;
            restLED       = false;
            repetitionLED = false;
            break;
        case MODE_REST:
            exerciseLED   = false;
            restLED       = true;
            repetitionLED = false;
            break;
        case MODE_REPETITIONS:
            exerciseLED   = false;
            restLED       = false;
            repetitionLED = true;
            break;
        default: // Switch case shouldn't come here. In that case, all three LEDs would light up for make the error more noticeable.
            exerciseLED   = true;
            restLED       = true;
            repetitionLED = true;
            break;
    }
}