#include "TFT_Display.h"
#include "enumerates.h"

Displayer::Displayer(TFT_eSPI* const pTftLcd) {
    /* TFT LCDの準備 */
    pTftLcd -> begin();
    pTftLcd -> setRotation(3);
    pTftLcd -> setTextSize(3);
    pTftLcd -> setTextColor(TFT_KUROBENI);
    /* トップ画面を表示する */
    this -> privateFShowMainScreen(pTftLcd);
}
// Displayer::~Displayer() {}

void Displayer::privateFShowMainScreen(TFT_eSPI* const pTftLcd) {
    /* 背景初期化 */
    pTftLcd -> fillScreen(TFT_TOKINEZU);
    /* ボタン指示 */
    pTftLcd -> drawString("A", 166, 2);
    pTftLcd -> drawString("B", 82, 2);
    /* メッセージ */
    pTftLcd -> drawString("Push button", 60, 110);
    pTftLcd -> drawString("A or B", 110, 135);
    this -> privateFChangeDisplayState(MAIN_SCREEN);
}

void Displayer::privateFChangeScreen(const DisplayState newState, TFT_eSPI* const pTftLcd) {
    if (this -> currentDisplayState != newState) {
        char* message;
        switch (newState) {
            case DISPLAY_A:
                message = "Button A";
                break;

            case DISPLAY_B:
                message = "Button B";
                break;
            
            default:
                message = "hello?";
                break;
        }
        pTftLcd -> fillScreen(TFT_TOKINEZU);
        pTftLcd -> drawString(message, 85, 110);
        pTftLcd -> drawString("C", 10, 2);
        pTftLcd -> drawString("Back to push C.", 25, 205);
        this -> privateFChangeDisplayState(newState);
    }
}

void Displayer::privateFChangeDisplayState(const DisplayState newState) {
    if (this -> currentDisplayState != newState)
        this -> currentDisplayState = newState;
}

void Displayer::mFChangeDisplay(const Wio3Button* const pButtonInput, TFT_eSPI* const pTftLcd) {
    switch (*pButtonInput) {
        case BUTTON_A:
            /* トップ画面ならA画面に遷移する */
            if (this -> currentDisplayState == MAIN_SCREEN) {
                this -> privateFChangeScreen(DISPLAY_A, pTftLcd);
            }
            break;

        case BUTTON_B:
            /* トップ画面ならB画面に遷移する */
            if (this -> currentDisplayState == MAIN_SCREEN) {
                this -> privateFChangeScreen(DISPLAY_B, pTftLcd);
            }
            break;

        case BUTTON_C:
            /* トップ画面でないならトップ画面に戻る */
            if (this -> currentDisplayState != MAIN_SCREEN) {
                this -> privateFShowMainScreen(pTftLcd);
            }
            break;

        default:
            break;
    }
}
