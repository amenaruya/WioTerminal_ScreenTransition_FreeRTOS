#ifndef __ENUMERATES__
#define __ENUMERATES__

typedef enum {
    BUTTON_A,
    BUTTON_B,
    BUTTON_C
} Wio3Button;

typedef enum {
    NO_INPUT,
    INPUT_A,
    INPUT_B,
    INPUT_C
} LatestInputState;

typedef enum {
    MAIN_SCREEN,
    DISPLAY_A,
    DISPLAY_B
} DisplayState;

typedef enum {
    NO_INPUT_DETECTED,
    INPUT_DETECTED
} ButtonInputDetection;

#endif
