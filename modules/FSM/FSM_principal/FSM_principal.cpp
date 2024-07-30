//=====[Libraries]=============================================================
#include "FSM_principal.h"
#include "button.h"
#include "UART.h"
#include "timer.h"
#include "led.h"

//=====[Declaration and initialization of private global variables]============
static      modes_t                     activeMode;
static      principalMachineStates_t    currentState    = STATE_WAITING;
static      bool                        countdownActive = false;


//=====[Declarations (prototypes) of private functions]========================
static void                     principalMachineOutputs             ();
static principalMachineStates_t determineNewStateFromWaitingState   (buttons_t input);
static principalMachineStates_t determineNewStateFromSelectModeState(buttons_t input);

//=====[Implementations of public functions]===================================
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

bool readCountdownState() {
    return countdownActive;
}

void setCountdownState(bool countdownState) {
    countdownActive = countdownState;
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
            checkValuesOfCurrentModeAndReassignIfCorresponds();
            updateLEDGroup();
            decrementTemporalValuesOfActiveMode();
            display();
            break;
        case STATE_WAITING:
        default:
            setCountdownState(false);
            display();
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