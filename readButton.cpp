/* WIO_KEY_A WIO_KEY_B WIO_KEY_C */
#include <variant.h>
/* pinMode() */
#include <wiring_digital.h>
/* HIGH LOW */
#include <wiring_constants.h>
/* delay() */
#include <delay.h>

#include "readButton.h"
#include "enumerates.h"

ButtonReader::ButtonReader() {
    /* ボタンA・B・Cピンを入力に設定する */
    pinMode(WIO_KEY_A, INPUT);
    pinMode(WIO_KEY_B, INPUT);
    pinMode(WIO_KEY_C, INPUT);
    /* 無入力を初期状態とする */
    this -> mLatestInput = NO_INPUT;
}
// ButtonReader::~ButtonReader() {}

void ButtonReader::mFReadButtonInput(ButtonInputDetection* const pResult) {
    /* 入力検知の有無を記録する */
    *pResult = NO_INPUT_DETECTED;
    if (this -> mLatestInput == NO_INPUT) {
        /* 直前に入力が無かった場合 */
        if (digitalRead(WIO_KEY_A) == LOW) {
            this -> mInputButton = BUTTON_A;
            this -> mLatestInput = INPUT_A;
            *pResult = INPUT_DETECTED;
        }
        else if (digitalRead(WIO_KEY_B) == LOW) {
            this -> mInputButton = BUTTON_B;
            this -> mLatestInput = INPUT_B;
            *pResult = INPUT_DETECTED;
        }
        else if (digitalRead(WIO_KEY_C) == LOW) {
            this -> mInputButton = BUTTON_C;
            this -> mLatestInput = INPUT_C;
            *pResult = INPUT_DETECTED;
        }
    }
    else {
        /*
        直前に入力があった場合
        現在孰れのボタンも押されていない場合のみ
        NO_INPUTに更新する
        */
        if (
            digitalRead(WIO_KEY_A) == HIGH &&
            digitalRead(WIO_KEY_B) == HIGH &&
            digitalRead(WIO_KEY_C) == HIGH
        ) {
            this -> mLatestInput = NO_INPUT;
        }
    }
}

Wio3Button* ButtonReader::mFpW3BGetInput() {
    return &(this -> mInputButton);
}
