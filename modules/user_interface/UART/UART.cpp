//=====[Libraries]=============================================================
#include "UART.h"
#include "mbed.h"
#include "timer.h"

//=====[Declaration and initialization of private global objects]===============
UnbufferedSerial static uartUsb(USBTX, USBRX, 115200);

//=====[Declarations (prototypes) of private functions]========================
static void displayActiveMode();

//=====[Implementations of public functions]===================================
void display() {    
    int *valuesToDisplay;
    valuesToDisplay = readTemporalValueOfTheModeActive();
    
    displayActiveMode();

    for (int i = 0; i < 4; i++) {
        char str[3];
        sprintf(str,"%d",*(valuesToDisplay + i));
        uartUsb.write(&str,2);

        if (i==1) {
            char colonSeparator[4] = " : ";
            uartUsb.write(&colonSeparator,3);
        }
    }
    uartUsb.write("\r\n",2);
}

void informThatCountdownIsFinished() {
    uartUsb.write("------------------------------\r\n",33);
    uartUsb.write("COUNTDOWN IS FINISHED!\r\n",25);
    uartUsb.write("------------------------------\r\n",33);
}

//=====[Implementations of private functions]==================================
static void displayActiveMode() {
    modes_t activeMode = readModeActive();

    switch (activeMode) {
        case MODE_EXERCISE:
            uartUsb.write("MODE: Exercise\r\n",16);
            break;
        case MODE_REST:
            uartUsb.write("MODE: Rest\r\n",12);
            break;
        case MODE_REPETITIONS:
            uartUsb.write("MODE: Repetitions\r\n",19);
            break;
        default:
            uartUsb.write("ERROR: Something went wrong when reading the active mode\r\n",58);
            break;
    }
}