#include "display.h"
#include "software_timer.h"

static const uint8_t SEG_CODE[10] = {
    0x40,
    0x79,
    0x24,
    0x30,
    0x19,
    0x12,
    0x02,
    0x78,
    0x00,
    0x10
};

static const uint16_t digit_pins[4] = {
    EN0_Pin, EN1_Pin,
    EN2_Pin, EN3_Pin
};

static uint8_t digits[4] = {0, 0, 0, 0};
static uint8_t scan_index = 0;

#define SCAN_TIME_MS    10

static void Display_AllOff(void)
{
    HAL_GPIO_WritePin(GPIOA,
        EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin,
        GPIO_PIN_SET);
}

void Display_Init(void)
{
    Display_AllOff();
    Display_Set(0, 0);
    scan_index = 0;

    setTimer(2, SCAN_TIME_MS);
    timer_flag[2] = 1;
}

void Display_Set(int left, int right)
{
    if (left < 0) left = 0;
    if (left > 99) left = 99;
    if (right < 0) right = 0;
    if (right > 99) right = 99;

    digits[0] = (uint8_t)(left / 10);
    digits[1] = (uint8_t)(left % 10);
    digits[2] = (uint8_t)(right / 10);
    digits[3] = (uint8_t)(right % 10);
}

void display(void)
{
    if (timer_flag[2] == 1)
    {
        timer_flag[2] = 0;
        setTimer(2, SCAN_TIME_MS);

        Display_AllOff();

        uint8_t code = SEG_CODE[digits[scan_index]];
        GPIOB->BSRR = (uint32_t)(code & 0x7F);
        GPIOB->BRR  = (uint32_t)((~code) & 0x7F);

        HAL_GPIO_WritePin(GPIOA, digit_pins[scan_index], GPIO_PIN_RESET);

        scan_index++;
        if (scan_index >= 4)
            scan_index = 0;
    }
}
