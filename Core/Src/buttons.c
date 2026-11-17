#include "buttons.h"

#define NUM_BUTTONS 3
#define DEBOUNCE_SAMPLES 3

static const uint16_t button_pins[NUM_BUTTONS] = {
    MODE_Pin,
    MODIFY_Pin,
    SET_Pin
};

static uint8_t stable[NUM_BUTTONS];
static uint8_t last_raw[NUM_BUTTONS];
static uint8_t count[NUM_BUTTONS];

static volatile uint8_t events = 0;

void Buttons_Init(void)
{
    events = 0;

    for (uint8_t i = 0; i < NUM_BUTTONS; i++)
    {
        stable[i] = 1;
        last_raw[i] = 1;
        count[i] = 0;
    }
}

void Buttons_Tick10ms(void)
{
    for (uint8_t i = 0; i < NUM_BUTTONS; i++)
    {
        uint8_t raw =
            (HAL_GPIO_ReadPin(GPIOB, button_pins[i])
             == GPIO_PIN_SET) ? 1 : 0;

        if (raw == last_raw[i])
        {
            if (count[i] < DEBOUNCE_SAMPLES)
            {
                count[i]++;
            }
        }
        else
        {
            last_raw[i] = raw;
            count[i] = 1;
        }

        if (count[i] >= DEBOUNCE_SAMPLES &&
            stable[i] != raw)
        {
            stable[i] = raw;

            if (raw == 0)
            {
                events |= (1U << i);
            }
        }
    }
}

uint8_t Buttons_GetEvents(void)
{
    uint8_t result = events;
    events = 0;
    return result;
}

int isButtonPressed(uint8_t index)
{
    if (index >= NUM_BUTTONS) return 0;

    if (events & (1U << index))
    {
        events &= ~(1U << index);
        return 1;
    }
    return 0;
}

int isButton1Pressed(void)
{
    return isButtonPressed(BUTTON_1);
}

int isButton2Pressed(void)
{
    return isButtonPressed(BUTTON_2);
}

int isButton3Pressed(void)
{
    return isButtonPressed(BUTTON_3);
}

void getKeyInput(void)
{
    Buttons_Tick10ms();
}
