//=====[Libraries]=============================================================
#include "mbed.h"
#include "FSM_principal.h"
#include "button.h"
#include "UART.h"
#include "timer.h"
#include "led.h"


using namespace std::chrono;

//=====[Declaration and initialization of private global objects]===============
static      LowPowerTimer timer;

//=====[Declaration and initialization of private global variables]============
static      modes_t                     activeMode;
static      principalMachineStates_t    currentState;
static      bool                        countdownActive;


//=====[Declarations (prototypes) of private functions]========================
static void                     principalMachineOutputs             ();
static principalMachineStates_t determineNewStateFromWaitingState   (buttons_t input);
static principalMachineStates_t determineNewStateFromSelectModeState(buttons_t input);

//=====[Implementations of public functions]===================================
bool readCountdownState() {
    return countdownActive;
}

void setCountdownState(bool countdownState) {
    countdownActive = countdownState;
}

void startThePrincipalMachine() {
    currentState    = STATE_WAITING;
    countdownActive = false;

    timer.start();
}

void updateStateOfprincipalMachine() {
    buttons_t                   input   = readCurrentInput();
    principalMachineStates_t    newState;

    switch (currentState) {
        case STATE_SELECT_MODE:
            newState = determineNewStateFromSelectModeState(input);  
            break;
        case STATE_INCREASE:
            if (input == BUTTON_INCREASE) {
                newState = STATE_INCREASE;
            } else {
                newState = STATE_WAITING;
            }    
            break;
        case STATE_DECREASE:
            if (input == BUTTON_DECREASE) {
                newState = STATE_DECREASE;
            } else {
                newState = STATE_WAITING; 
            }           
            break;
        case STATE_COUNTDOWN:
            if (input == BUTTON_PLAY_PAUSE || countdownActive == false) {
                newState = STATE_WAITING;
            } else {
                newState = STATE_COUNTDOWN;
            }
            break;
        case STATE_WAITING:
        default:
            newState = determineNewStateFromWaitingState(input);
            break;
    }

    currentState = newState;
    principalMachineOutputs();
}

principalMachineStates_t readCurrentState() {
    return currentState;
}

//=====[Implementations of private functions]==================================
static void principalMachineOutputs() {
    switch (currentState) {
        case STATE_SELECT_MODE:
            updateMode();
            updateLEDGroup();
            display();
            break;
        case STATE_INCREASE:
            updateInitialValuesOfActiveMode();
            display();
            break;
        case STATE_DECREASE:
            updateInitialValuesOfActiveMode();
            display();
            break;
        case STATE_COUNTDOWN:
            setCountdownState(true);
    
            if (duration_cast<milliseconds>(timer.elapsed_time()).count() >= 1000) { //Se lee el valor del objeto timer
                checkValuesOfCurrentModeAndReassignIfCorresponds();
                updateLEDGroup();
                decrementTemporalValuesOfActiveMode();
                display();

                timer.reset();
            }
            break;
        case STATE_WAITING:
        default:
            setCountdownState(false);
            break;
    }
}

static principalMachineStates_t determineNewStateFromWaitingState(buttons_t input) {
    switch (input) {
        case BUTTON_SELECT_MODE:    return STATE_SELECT_MODE;
        case BUTTON_INCREASE:       return STATE_INCREASE;
        case BUTTON_DECREASE:       return STATE_DECREASE;
        case BUTTON_PLAY_PAUSE:     return STATE_COUNTDOWN;
        default:                    return STATE_WAITING;
    }
}

static principalMachineStates_t determineNewStateFromSelectModeState(buttons_t input) {
    switch (input) {
        case BUTTON_SELECT_MODE:    return STATE_SELECT_MODE;
        case BUTTON_PLAY_PAUSE:     return STATE_COUNTDOWN;
        default:                    return STATE_WAITING;
    }
}