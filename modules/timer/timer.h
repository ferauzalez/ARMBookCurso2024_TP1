#include <array>
using namespace std;
//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================
typedef enum {
    MODE_EXERCISE,
    MODE_REST,
    MODE_REPETITIONS
} modes_t;

//=====[Declarations (prototypes) of public functions]=========================
void    checkValuesOfCurrentModeAndReassignIfCorresponds();
int *   readInitialValueOfTheModeActive                 ();
int *   readTemporalValueOfTheModeActive                ();
modes_t readModeActive                                  ();
void    updateMode                                      ();
void    updateInitialValuesOfActiveMode                 ();
void    decrementTemporalValuesOfActiveMode             ();
void    startTimer                                      ();
