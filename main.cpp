//=====[Libraries]=============================================================
#include "button.h"
#include "FSM_principal.h"
#include "mbed.h"

//=====[Declaration of private defines]========================================
#define TIME_BETWEEN_COUNTDOWNS 1000ms

//=====[Declaration and initialization of public global objects]===============
Ticker timeOut;

//=====[Declarations (prototypes) of private functions]========================
void updateCountdown();

//=====[Implementations of public functions]===================================
int main() {
    buttonsInit();

    timeOut.attach(&updateCountdown,TIME_BETWEEN_COUNTDOWNS);

    while (true) {      
        if (itIsNecessaryToMakeATransition() == true) {
            updateStateOfprincipalMachine();
        }
    }
}

//=====[Implementations of private functions]==================================
void updateCountdown() {
    bool countdownState = readCountdownState();
    if (countdownState == true) {
        updateStateOfprincipalMachine();
    }
}