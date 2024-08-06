//=====[Libraries]=============================================================
#include "button.h"
#include "FSM_principal.h"
#include "mbed.h"

//=====[Implementations of public functions]===================================
int main() {
    buttonsInit();
    startThePrincipalMachine();

    while (true) {      
        updateStateOfprincipalMachine();
    }
}