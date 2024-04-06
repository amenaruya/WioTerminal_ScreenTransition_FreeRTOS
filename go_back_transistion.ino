/*
画面遷移
トップ画面からA画面とB画面の孰れかに遷移できる
Aボタンを押せば画面Aへ
Bボタンを押せば画面Bへ遷移する
遷移先でCボタンを押すことでトップ画面に復帰する
*/

#include <Seeed_Arduino_FreeRTOS.h>
#include "queue.h"

#include "enumerates.h"
#include "readButton.h"
#include "TFT_Display.h"

/* タスクの許容領域 */
#define STACK_SIZE  256
/* キューの容量 */
#define QUEUE_SIZE  16

TaskHandle_t        taskHandlerLCD,
                    taskHandlerButton;

QueueHandle_t       queueButton;

/*
TFT LCDの初期化
クラスメンバーに含めたり函数内で初期化したりすると
正しく動作しない
*/
TFT_eSPI LIQUID_CRYSTAL_DISPLAY;

static void ThreadButton(void* pvParameters);
static void ThreadLCD(void* pvParameters);

void setup() {
    /* キューを作る */
    queueButton = xQueueCreate(
        QUEUE_SIZE,
        sizeof(Wio3Button)
    );
    /* タスクを作る */
    xTaskCreate(
        ThreadLCD,
        "TFT LCD",
        STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1,
        &taskHandlerLCD
    );
    xTaskCreate(
        ThreadButton,
        "Button",
        STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY,
        &taskHandlerButton
    );
    /* タスクを開始する */
    vTaskStartScheduler();
}
void loop() {}

/* ボタン入力処理 */
static void ThreadButton(void* pvParameters) {
    (void) pvParameters;

    /* 初期化 */
    ButtonReader buttonReader;
    /* 入力検知 */
    ButtonInputDetection resultCode;

    Wio3Button* (ButtonReader::*pmFpW3BGetInput)()
        = &ButtonReader::mFpW3BGetInput;
    void (ButtonReader::*pmFReadButtonInput)(
        ButtonInputDetection* const pResult
        
    )   = &ButtonReader::mFReadButtonInput;

    while (1) {
        (buttonReader.*pmFReadButtonInput)(&resultCode);
        if (resultCode == INPUT_DETECTED) {
            /* 入力を検知した場合ボタンの種類をqueueに送信する */
            xQueueSend(
                queueButton,
                (buttonReader.*pmFpW3BGetInput)(),
                portMAX_DELAY
            );
        }
        delay(100);
    }
}

/* 画面処理 */
static void ThreadLCD(void* pvParameters) {
    (void) pvParameters;

    /* 初期化 */
    Displayer displayer(&LIQUID_CRYSTAL_DISPLAY);
    /* ボタン入力を受信する変数 */
    Wio3Button receivedInputButton;

    void (Displayer::*pmFChangeDisplay)(
        const Wio3Button* const pButtonInput,
        TFT_eSPI* const pTftLcd
    )   = &Displayer::mFChangeDisplay;

    while (1) {
        /* ボタン入力を受信する */
        xQueueReceive(
            queueButton,
            &receivedInputButton,
            portMAX_DELAY
        );
        (displayer.*pmFChangeDisplay)(&receivedInputButton, &LIQUID_CRYSTAL_DISPLAY);
        delay(150);
    }
}