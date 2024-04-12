#include "TFT_Display.h"
#include "enumerates.h"

Displayer::Displayer(TFT_eSPI* const pTftLcd):
pTft(pTftLcd) {
    /* TFT LCDの準備 */
    (this -> pTft) -> begin();
    (this -> pTft) -> setRotation(3);
    (this -> pTft) -> setTextSize(3);
    (this -> pTft) -> setTextColor(TFT_KUROBENI);
    /* トップ画面を表示する */
    this -> privateFShowMainScreen();
}
// Displayer::~Displayer() {}

void Displayer::privateFShowMainScreen() {
    /* 背景初期化 */
    (this -> pTft) -> fillScreen(TFT_TOKINEZU);
    /* ボタン指示 */
    (this -> pTft) -> drawString("A", 166, 2);
    (this -> pTft) -> drawString("B", 82, 2);
    /* メッセージ */
    (this -> pTft) -> drawString("Push button", 60, 110);
    (this -> pTft) -> drawString("A or B", 110, 135);
    this -> privateFChangeDisplayState(MAIN_SCREEN);
}

void Displayer::privateFChangeScreen(const DisplayState newState) {
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
        (this -> pTft) -> fillScreen(TFT_TOKINEZU);
        (this -> pTft) -> drawString(message, 85, 110);
        (this -> pTft) -> drawString("C", 10, 2);
        (this -> pTft) -> drawString("Push C to back.", 25, 205);
        this -> privateFChangeDisplayState(newState);
    }
}

void Displayer::privateFChangeDisplayState(const DisplayState newState) {
    if (this -> currentDisplayState != newState)
        this -> currentDisplayState = newState;
}

void Displayer::mFChangeDisplay(const Wio3Button* const pButtonInput) {
    switch (*pButtonInput) {
        case BUTTON_A:
            /* トップ画面ならA画面に遷移する */
            if (this -> currentDisplayState == MAIN_SCREEN) {
                this -> privateFChangeScreen(DISPLAY_A);
            }
            break;

        case BUTTON_B:
            /* トップ画面ならB画面に遷移する */
            if (this -> currentDisplayState == MAIN_SCREEN) {
                this -> privateFChangeScreen(DISPLAY_B);
            }
            break;

        case BUTTON_C:
            /* トップ画面でないならトップ画面に戻る */
            if (this -> currentDisplayState != MAIN_SCREEN) {
                this -> privateFShowMainScreen();
            }
            break;

        default:
            break;
    }
}
