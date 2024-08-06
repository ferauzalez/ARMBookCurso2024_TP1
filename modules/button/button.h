//=====[Declaration of public data types]======================================
typedef enum {
    BUTTON_SELECT_MODE,
    BUTTON_INCREASE,
    BUTTON_DECREASE,
    BUTTON_PLAY_PAUSE,
    NONE_BUTTON_SELECTED // For default case
} buttons_t;

//=====[Declarations (prototypes) of public functions]=========================
void        buttonsInit                     ();
buttons_t   readCurrentInput                ();