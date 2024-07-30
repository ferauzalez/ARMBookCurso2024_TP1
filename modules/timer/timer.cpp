//=====[Libraries]=============================================================
#include "timer.h"
#include "FSM_principal.h"
#include "UART.h"

//=====[Declaration and initialization of private global variables]============

// The following arrays contains four values, one for each seven-segment display
// The seven segment display is not implemented yet
static  int     exerciseModeInitialValues   [4]     = {0,0,1,0}; // Initialization with random value
static  int     restModeInitialValues       [4]     = {0,0,0,5}; // Initialization with random value
static  int     repetitionModeInitialValues [4]     = {0,0,0,3}; // Initialization with random value

static  int     exerciseModeTemporalValues  [4]     = {0,0,0,0};
static  int     restModeTemporalValues      [4]     = {0,0,0,0};
static  int     repetitionModeTemporalValues[4]     = {0,0,0,0};

static  int     errorValues                 [4]     = {8,8,8,8}; // For error cases. All segments of each seven-segment display would turn on.

static modes_t  currentMode                         = MODE_REPETITIONS;

//=====[Declarations (prototypes) of private functions]========================
static void incrementFirstDigitValue    (int& firstDigitInitialValue);
static void incrementSecondDigitValue   (int& secondDigitInitialValue, int& firstDigitInitialValue);
static void incrementThirdDigitValue    (int& thirdDigitInitialValue,  int& secondDigitInitialValue,int& firstDigitInitialValue);
static void incrementFourthDigitValue   (int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue);

static void decrementFirstDigitValue    (int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue);
static void decrementSecondDigitValue   (int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue);
static void decrementThirdDigitValue    (int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue);
static void decrementFourthDigitValue   (int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue);

static int * readInitialValueOfSpecificMode             (modes_t mode);
static int * readTemporalValueOfSpecificMode            (modes_t mode);
static void  copyInitialToTemporalValuesOfTheActiveMode ();
static void  assignValuesForANewCicle                   ();

//=====[Implementations of public functions]===================================
void checkValuesOfCurrentModeAndReassignIfCorresponds() {
    if (currentMode == MODE_EXERCISE) {
        if (
            exerciseModeTemporalValues[3]   == 0  && 
            exerciseModeTemporalValues[2]   == 0  && 
            exerciseModeTemporalValues[1]   == 0  && 
            exerciseModeTemporalValues[0]   == 0
        ) {
            currentMode = MODE_REST;
            return;
        } else {
            return;
        }
    }

    if (currentMode == MODE_REST) {
        if (
            restModeTemporalValues[3]   == 0  && 
            restModeTemporalValues[2]   == 0  && 
            restModeTemporalValues[1]   == 0  && 
            restModeTemporalValues[0]   == 0
        ) {
            currentMode = MODE_REPETITIONS;
            return;
        } else {
            return;
        }
    }

    if (currentMode == MODE_REPETITIONS) {
        if (
            repetitionModeTemporalValues[3]   == 0  && 
            repetitionModeTemporalValues[2]   == 0  && 
            repetitionModeTemporalValues[1]   == 0  && 
            repetitionModeTemporalValues[0]   == 0
        ) {
            setCountdownState(false);
            informThatCountdownIsFinished();
            currentMode = MODE_EXERCISE;
            return;
        } else {
            assignValuesForANewCicle();
            return;
        }
    }
    return;
}

int * readInitialValueOfTheModeActive() {
    switch (currentMode){
        case MODE_EXERCISE:     return exerciseModeInitialValues;
        case MODE_REST:         return restModeInitialValues;
        case MODE_REPETITIONS:  return repetitionModeInitialValues;
        default:                return errorValues;
    }
}

int * readTemporalValueOfTheModeActive() {
    switch (currentMode){
        case MODE_EXERCISE:     return exerciseModeTemporalValues;
        case MODE_REST:         return restModeTemporalValues;
        case MODE_REPETITIONS:  return repetitionModeTemporalValues;
        default:                return errorValues;
    }
}

modes_t readModeActive() {
    return currentMode;
}

void updateMode() {
    switch (currentMode){
        case MODE_EXERCISE:     
            currentMode = MODE_REST;
            break;
        case MODE_REST:         
            currentMode = MODE_REPETITIONS;
            break;
        case MODE_REPETITIONS:  
            currentMode = MODE_EXERCISE;
            break;
        default:                
            currentMode = MODE_EXERCISE;
            break;
    }

    copyInitialToTemporalValuesOfTheActiveMode(); // I notice that is necessary to make this call at least for the case when the first button pressed is BUTTON_SELECT_MODE 
}

void updateInitialValuesOfActiveMode() {
    int* value;
    value = readInitialValueOfTheModeActive();
    principalMachineStates_t currentState = readCurrentState();

    // These four int are declared to improve the interpretation of the code
    int firstDigitValue  = *(value + 3); // first digit from right to left 
    int secondDigitValue = *(value + 2);
    int thirdDigitValue  = *(value + 1);
    int fourthDigitValue = *(value + 0);

    if (currentState == STATE_INCREASE) {
        incrementFirstDigitValue    (firstDigitValue);
        incrementSecondDigitValue   (secondDigitValue, firstDigitValue);
        incrementThirdDigitValue    (thirdDigitValue , secondDigitValue, firstDigitValue);
        incrementFourthDigitValue   (fourthDigitValue, thirdDigitValue , secondDigitValue, firstDigitValue);

    } else if (currentState == STATE_DECREASE) {        
        decrementFirstDigitValue    (fourthDigitValue, thirdDigitValue, secondDigitValue, firstDigitValue);
        decrementSecondDigitValue   (fourthDigitValue, thirdDigitValue, secondDigitValue, firstDigitValue);
        decrementThirdDigitValue    (fourthDigitValue, thirdDigitValue, secondDigitValue, firstDigitValue);
        decrementFourthDigitValue   (fourthDigitValue, thirdDigitValue, secondDigitValue, firstDigitValue);
        
    }
        *(value + 3) = firstDigitValue;
        *(value + 2) = secondDigitValue;
        *(value + 1) = thirdDigitValue;
        *(value + 0) = fourthDigitValue;

        copyInitialToTemporalValuesOfTheActiveMode();
}

void decrementTemporalValuesOfActiveMode() {
    int* value;
    value = readTemporalValueOfTheModeActive();

    // These four int are declared to improve the interpretation of the code
    int firstDigitValue  = *(value + 3); // first digit from right to left 
    int secondDigitValue = *(value + 2);
    int thirdDigitValue  = *(value + 1);
    int fourthDigitValue = *(value + 0);

    decrementFirstDigitValue    (fourthDigitValue, thirdDigitValue, secondDigitValue, firstDigitValue);
    decrementSecondDigitValue   (fourthDigitValue, thirdDigitValue, secondDigitValue, firstDigitValue);
    decrementThirdDigitValue    (fourthDigitValue, thirdDigitValue, secondDigitValue, firstDigitValue);
    decrementFourthDigitValue   (fourthDigitValue, thirdDigitValue, secondDigitValue, firstDigitValue);
    
    *(value + 3) = firstDigitValue;
    *(value + 2) = secondDigitValue;
    *(value + 1) = thirdDigitValue;
    *(value + 0) = fourthDigitValue;

    return;
}

//=====[Implementations of private functions]===================================
static int * readInitialValueOfSpecificMode(modes_t mode) {
    switch (mode){
        case MODE_EXERCISE:     return exerciseModeInitialValues;
        case MODE_REST:         return restModeInitialValues;
        case MODE_REPETITIONS:  return repetitionModeInitialValues;
        default:                return errorValues;
    }
}

static int * readTemporalValueOfSpecificMode(modes_t mode) {
    switch (mode){
        case MODE_EXERCISE:     return exerciseModeTemporalValues;
        case MODE_REST:         return restModeTemporalValues;
        case MODE_REPETITIONS:  return repetitionModeTemporalValues;
        default:                return errorValues;
    }
}

static void assignValuesForANewCicle() {
        currentMode = MODE_REST;
        copyInitialToTemporalValuesOfTheActiveMode();

        currentMode = MODE_EXERCISE;
        copyInitialToTemporalValuesOfTheActiveMode();

        return; 
}

static void copyInitialToTemporalValuesOfTheActiveMode() {
    int* initialValue;
    initialValue = readInitialValueOfTheModeActive();

    int* temporalValue;
    temporalValue = readTemporalValueOfTheModeActive();

    // These four int are declared to improve the interpretation of the code
    *(temporalValue + 3)  = *(initialValue + 3); // first digit from right to left 
    *(temporalValue + 2)  = *(initialValue + 2);
    *(temporalValue + 1)  = *(initialValue + 1);
    *(temporalValue + 0)  = *(initialValue + 0);

    return;
}

static void decrementFirstDigitValue(int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue) {
    
    if (firstDigitInitialValue == 0) {
        if (fourthDigitInitialValue == 0 && thirdDigitInitialValue == 0 && secondDigitInitialValue == 0) {
            return;
        } else {
            firstDigitInitialValue = 9;
        }
    } else {
        firstDigitInitialValue -= 1;
    }
};

static void decrementSecondDigitValue(int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue) {
    if (firstDigitInitialValue == 9) {
        if (secondDigitInitialValue == 0) {
            if (fourthDigitInitialValue != 0 || thirdDigitInitialValue != 0) {
                secondDigitInitialValue = 5;
            } else {
                return;
            }
        } else {
            secondDigitInitialValue -= 1;
        }
    } else {
        thirdDigitInitialValue = thirdDigitInitialValue;
    }
};

static void decrementThirdDigitValue(int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue) {
    if (secondDigitInitialValue == 5 && firstDigitInitialValue == 9) {
        if (thirdDigitInitialValue == 0) {
            if (fourthDigitInitialValue == 0) {
                return;
            } else {
                thirdDigitInitialValue = 9;
            }
        } else {
            thirdDigitInitialValue -= 1;
        }
    } else {
        thirdDigitInitialValue = thirdDigitInitialValue;
    }
};

static void decrementFourthDigitValue(int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue) {
    if (thirdDigitInitialValue == 9 && secondDigitInitialValue == 5 && firstDigitInitialValue == 9) {
        if (fourthDigitInitialValue == 0) {
            return;
        } else {
            fourthDigitInitialValue -= 1;
        }
    } else {
        fourthDigitInitialValue = fourthDigitInitialValue;
    }
}

static void incrementFirstDigitValue(int& firstDigitInitialValue) {
    if (firstDigitInitialValue == 9) {
        firstDigitInitialValue = 0;
    } else {
        firstDigitInitialValue += 1;
    }
}

static void incrementSecondDigitValue(int& secondDigitInitialValue, int& firstDigitInitialValue) {
    if (firstDigitInitialValue == 0) {
        if (secondDigitInitialValue == 5) {
            secondDigitInitialValue = 0;
        } else {
            secondDigitInitialValue += 1;
        }
    } else {
        secondDigitInitialValue = secondDigitInitialValue;
    }
};

static void incrementThirdDigitValue(int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue) {
    if (secondDigitInitialValue == 0 && firstDigitInitialValue == 0) {
        if (thirdDigitInitialValue == 9) {
            thirdDigitInitialValue = 0;
        } else {
            thirdDigitInitialValue += 1;
        }
    } else {
        thirdDigitInitialValue = thirdDigitInitialValue;
    }
};

static void incrementFourthDigitValue(int& fourthDigitInitialValue, int& thirdDigitInitialValue, int& secondDigitInitialValue, int& firstDigitInitialValue) {
    if (thirdDigitInitialValue == 0 && secondDigitInitialValue == 0 && firstDigitInitialValue == 0) {
        if (fourthDigitInitialValue == 9) {
            fourthDigitInitialValue = 0;
        } else {
            fourthDigitInitialValue += 1;
        }
    } else {
        fourthDigitInitialValue = fourthDigitInitialValue;
    }
};