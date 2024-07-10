/* Temporizador para ejericicio
TP 1 del curso de Sistemas Embebidos basado en libro de ARM
Alumno: Fernando Gonzalez
*/

/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define TIME_BETWEEN_COUNTDOWNS 1000ms
#define DEAD_TIME_FOR_DEBOUNCING 200ms

void blinkLEDs();
void countdown();
void decrease();
bool decreaseTime();
void decreaseRepetitions();
void display();
void displayModeSeleted();
void displayRepetitions();
void displayTime();
void increase();
void increaseRepetitions();
bool increaseTime();
void manageLEDs();
void onRXInterrupt();
void playPause();
void readButtons();
void restoreInitialValues();
void saveInitialValues();
void selectMode();
void startTheNextCountdown();
void updateIndexSelectionMode();
void writeSeparatorBar();

int indexSelectionMode = 0;
int initialTimesAndRepetitions[4] = {0,0,0,0};
int timesAndRepetitions[5] = {0,0,0,0,0};

char receivedChar = '\0';

bool TrueIfSelectionButtonWasPressedForTheFirstTime = false;
bool playTruePauseFalse = false;
bool falseIfCountdownFinished = true;

Ticker timeOut;

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

DigitalIn selectionButton(D7);
DigitalIn increaseButton(D6);
DigitalIn decreaseButton(D5);
DigitalIn playPauseButton(D4);

DigitalOut exerciseLED(D15);
DigitalOut restLED(D14);
DigitalOut repetitionLED(D13);

int main()
{
    selectionButton.mode(PullDown);
    increaseButton.mode(PullDown);
    decreaseButton.mode(PullDown);
    playPauseButton.mode(PullDown);

    writeSeparatorBar();

    timeOut.attach(&countdown,TIME_BETWEEN_COUNTDOWNS);
    
    while (true) {
        readButtons();
        ThisThread::sleep_for(DEAD_TIME_FOR_DEBOUNCING);
    }
}


void blinkLEDs() {
    switch (indexSelectionMode) {
        case 0:
            exerciseLED   = !exerciseLED;
            restLED       = false;
            repetitionLED = false;
            break;
        case 2:
            exerciseLED   = false;
            restLED       = !restLED;
            repetitionLED = false;
            break;
        default:
            exerciseLED   = false;
            restLED       = false;
            repetitionLED = false;
            break;
    }
}

void countdown() {
    if (playTruePauseFalse) {
        //exerciseLED = !exerciseLED;
        decrease();
        display();
        blinkLEDs();
    }
}

void decrease() {
    uartUsb.write("\r\ndecrement\r\n",13);

    if (indexSelectionMode == 4) {
        decreaseRepetitions();
        return;
    } 
    falseIfCountdownFinished = decreaseTime();
    if (indexSelectionMode < 4 && falseIfCountdownFinished == false && playTruePauseFalse == true) {
        startTheNextCountdown();
    }
    return;
};

bool decreaseTime() {
    if (timesAndRepetitions[indexSelectionMode + 1] == 00) {
        if (timesAndRepetitions[indexSelectionMode] == 00) {
        return false;
    }
        timesAndRepetitions[indexSelectionMode]    -= 1;
        timesAndRepetitions[indexSelectionMode + 1] = 59;
        return true;
    }
    
    timesAndRepetitions[indexSelectionMode + 1] -= 1;
    return true;
}

void decreaseRepetitions() {
    if (timesAndRepetitions[indexSelectionMode] == 0) {
        return;
    }

    timesAndRepetitions[indexSelectionMode] -= 1;
    return;
}

void display() {
    if (indexSelectionMode == 4) {
        displayRepetitions();
        return;
    } 
    displayTime();
};

void displayModeSeleted() {
    switch (indexSelectionMode) {
        case 0:
            uartUsb.write(" exercise time selected\r\n",25);
            break;
        case 2:
            uartUsb.write(" rest time selected\r\n",21);
            break;
        case 4:
            uartUsb.write(" repetitions selected\r\n",23);
            break;
        default:
            indexSelectionMode = 0;
            break;
    }

}

void displayRepetitions() {
    char str[2];
    sprintf(str,"%d",timesAndRepetitions[indexSelectionMode]);
    uartUsb.write(&str,2);
    displayModeSeleted();
    uartUsb.write("\r\n",2);
    uartUsb.write(" \r\n",3);
};

void displayTime() {
    char str[2];
    sprintf(str,"%d",timesAndRepetitions[indexSelectionMode]);
    uartUsb.write(&str,2);
    uartUsb.write(" : ",3);
    sprintf(str,"%d",timesAndRepetitions[indexSelectionMode + 1]);
    uartUsb.write(&str,2);
    displayModeSeleted();
    uartUsb.write("\r\n",2);
    uartUsb.write(" \r\n",3);
};

void increase() {
    uartUsb.write("\r\nincrement\r\n",13);

    if (indexSelectionMode == 4) {
        increaseRepetitions();
        return;
    } 
    increaseTime();
    return;
};

void increaseRepetitions() {
    if (timesAndRepetitions[indexSelectionMode] == 99) {
        timesAndRepetitions[indexSelectionMode] = 0;

        return;
    }

    timesAndRepetitions[indexSelectionMode] += 1;
    return;
}

bool increaseTime() {
    if (timesAndRepetitions[indexSelectionMode + 1] == 59) {
        if (timesAndRepetitions[indexSelectionMode] == 99) {
        return false;
    }
        timesAndRepetitions[indexSelectionMode]    += 1;
        timesAndRepetitions[indexSelectionMode + 1] = 0;
        return true;
    }
    
    timesAndRepetitions[indexSelectionMode + 1] += 1;
    return true;
}

void manageLEDs() {
    switch (indexSelectionMode) {
        case 0:
            exerciseLED   = true;
            restLED       = false;
            repetitionLED = false;
            break;
        case 2:
            exerciseLED   = false;
            restLED       = true;
            repetitionLED = false;
            break;
        case 4:
            exerciseLED   = false;
            restLED       = false;
            repetitionLED = true;
            break;
        default:
            exerciseLED   = false;
            restLED       = false;
            repetitionLED = true;
            break;
    }
}

void onRXInterrupt(){
    char receivedChar;

    if (uartUsb.read(&receivedChar, 1)) {
        switch (receivedChar) {
            case 'n':
                selectMode();
                break;
            case 'i':
                increase();
                break;
            case 'd':
                decrease();
                break;
            case 'p':
                playPause();
                break;
            default:
                uartUsb.write("\r\ninvalid command\r\n",19);
                break;
            
        }
        display();
    }
}

void playPause() {
    uartUsb.write("\r\nplay-pause\r\n",14);
    playTruePauseFalse = !playTruePauseFalse;
}

void readButtons() {
    if (selectionButton) {
        selectMode();
        display();
        return;
    }

    if (increaseButton) {
        increase();
        display();
        return;
    }

    if (decreaseButton) {
        decrease();
        display();
        return;
    }

    if (playPauseButton) {
        playPause();
        display();
        return;
    }
}

void restoreInitialValues() {
    for(int i=0;i<4;i++){
        timesAndRepetitions[i] = initialTimesAndRepetitions[i];
    }
}

void saveInitialValues() {
    for(int i=0;i<4;i++){
        initialTimesAndRepetitions[i] = timesAndRepetitions[i];
    }
}

void selectMode() {
    updateIndexSelectionMode();
        
    uartUsb.write("\r\nSelect mode\r\n",15);
    if (indexSelectionMode == 0) {
        TrueIfSelectionButtonWasPressedForTheFirstTime = true;
    }

    manageLEDs();
    
    saveInitialValues();
}

void startTheNextCountdown() {
    if (timesAndRepetitions[4] == 0) {
        uartUsb.write("\r\nCountdown finished. The system will entry in waiting mode.\r\n",62);
        playTruePauseFalse = false;
        return;
    }
    

    if (indexSelectionMode == 0) {
        indexSelectionMode += 2;
    } else if (indexSelectionMode == 2 && timesAndRepetitions[4] > 0) {
        timesAndRepetitions[4]--;

        if (timesAndRepetitions[4] == 0){
            return;
        }
        char str[2];
        sprintf(str,"%d",timesAndRepetitions[4]);
        uartUsb.write(&str,2);
        uartUsb.write(" repetitions remains\r\n",22);

        restoreInitialValues();

        indexSelectionMode = 0;
    }

    displayModeSeleted();
}

void updateIndexSelectionMode() {
    if (!TrueIfSelectionButtonWasPressedForTheFirstTime) {
        return;
    }

    if (indexSelectionMode == 4) {
        indexSelectionMode = 0;
    } else {
        indexSelectionMode +=2;
    }
}

void writeSeparatorBar() {
    uartUsb.write("\r\n----------------------------------------------\r\n",50);
}