//=====[Libraries]=============================================================
#include "mbed.h"
#include "button.h"
#include "microcontroller.h"

//=====[Declaration of private defines]========================================
#define TIME_BETWEEN_COUNTDOWNS 1000ms

//=====[Declaration and initialization of private global objects]===============
static DigitalIn selectModeButton   (D7);
static DigitalIn increaseButton     (D6);
static DigitalIn decreaseButton     (D5);
static DigitalIn playPauseButton    (D4);

//=====[Declaration and initialization of private global variables]=============
static buttons_t currentInput;

//=====[Declarations (prototypes) of private functions]========================
static void readButtons();

//=====[Implementations of public functions]===================================

void buttonsInit() {
    selectModeButton.mode(PullDown);
    increaseButton.mode(PullDown);
    decreaseButton.mode(PullDown);
    playPauseButton.mode(PullDown);
}

buttons_t readCurrentInput() {
    readButtons();
    microcontrollerDelay();

    return currentInput;
}

//=====[Implementations of private functions]==================================
static void readButtons() {
    if (selectModeButton == !0) {
        currentInput = BUTTON_SELECT_MODE;
    } else if (increaseButton == !0) {
        currentInput = BUTTON_INCREASE;
    } else if (decreaseButton == !0) {
        currentInput = BUTTON_DECREASE;
    } else if (playPauseButton == !0) {
        currentInput = BUTTON_PLAY_PAUSE;
    } else {
        currentInput = NONE_BUTTON_SELECTED;
    }
}