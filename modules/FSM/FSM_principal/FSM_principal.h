//=====[Declaration of public data types]======================================
typedef enum {
    STATE_WAITING,
    STATE_INCREASE,
    STATE_DECREASE,
    STATE_COUNTDOWN,
    STATE_SELECT_MODE,
    STATE_SELECT_DIGIT
} principalMachineStates_t;

//=====[Declarations (prototypes) of public functions]=========================
void                        updateStateOfprincipalMachine   ();
principalMachineStates_t    readCurrentState                ();
bool                        readCountdownState              ();
void                        setCountdownState               (bool countdownState);