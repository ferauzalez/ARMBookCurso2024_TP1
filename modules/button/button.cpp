//=====[Libraries]=============================================================
#include "mbed.h"
#include "button.h"
#include "microcontroller.h"

//=====[Declaration and initialization of private global objects]===============
static DigitalIn selectModeButton   (D7);
static DigitalIn increaseButton     (D6);
static DigitalIn decreaseButton     (D5);
static DigitalIn playPauseButton    (D4);

//=====[Declaration and initialization of private global variables]=============
static buttons_t currentInput;

//=====[Implementations of public functions]===================================
bool itIsNecessaryToMakeATransition() {
    readButtons();

    if (currentInput == NONE_BUTTON_SELECTED) {
        return false;
    } else {
        microcontrollerDelay();

        return true;
    }
}

void buttonsInit() {
    selectModeButton.mode(PullDown);
    increaseButton.mode(PullDown);
    decreaseButton.mode(PullDown);
    playPauseButton.mode(PullDown);
}

buttons_t readButtons() {
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

    return currentInput;
}

buttons_t readCurrentInput() {
    return currentInput;
}