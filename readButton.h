#ifndef __READ_BUTTON__
#define __READ_BUTTON__

#include "enumerates.h"

class ButtonReader {
private:
    /*
    enumの値をqueueで扱うには変数を設ける
    この変数の参照を送ればよい
    */
    Wio3Button mInputButton;
    /*
    一度のボタン操作に対して処理は一度きりとするために、
    直前の入力の有無を管理する
    */
    LatestInputState mLatestInput;

public:
    ButtonReader();
    // ~ButtonReader();
    /* 入力検知 */
    void mFReadButtonInput(ButtonInputDetection* const pResult);
    /* getter */
    Wio3Button* mFpW3BGetInput();
};

#endif
