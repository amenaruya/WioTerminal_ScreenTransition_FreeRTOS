#ifndef __TFT_DISPLAY__
#define __TFT_DISPLAY__

#include "TFT_eSPI.h"
#include "enumerates.h"

/* 黒紅 */
#define TFT_KUROBENI    0x2926
/* 鴇鼠 */
#define TFT_TOKINEZU    0xDE7A

class Displayer {
private:
    TFT_eSPI* pTft;
    /* 画面表示の状態 */
    DisplayState currentDisplayState;
    void privateFShowMainScreen();
    void privateFChangeScreen(const DisplayState newState);
    void privateFChangeDisplayState(const DisplayState newState);

public:
    Displayer(TFT_eSPI* const pTftLcd);
    // ~Displayer();
    void mFChangeDisplay(const Wio3Button* const pButtonInput);
};

#endif
