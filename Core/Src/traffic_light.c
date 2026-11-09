/* The existing Proteus circuit uses active-high traffic LEDs. */
#include "traffic_light.h"

#define A_RED     NS_RED_Pin
#define A_AMBER     NS_YELLOW_Pin
#define A_GREEN     NS_GREEN_Pin

#define B_RED     EW_RED_Pin
#define B_AMBER     EW_YELLOW_Pin
#define B_GREEN     EW_GREEN_Pin

#define ALL_TRAFFIC_PINS \
    (A_RED | A_AMBER | A_GREEN | \
     B_RED | B_AMBER | B_GREEN)

void Traffic_Init(void)
{
    HAL_GPIO_WritePin(
        GPIOA, ALL_TRAFFIC_PINS, GPIO_PIN_RESET);
}

void Traffic_Show(TrafficColor a, TrafficColor b)
{
    uint16_t pins = 0;

    switch (a)
    {
        case COLOR_RED:    pins |= A_RED;   break;
        case COLOR_AMBER:  pins |= A_AMBER; break;
        case COLOR_GREEN:  pins |= A_GREEN; break;
        default: break;
    }

    switch (b)
    {
        case COLOR_RED:    pins |= B_RED;   break;
        case COLOR_AMBER:  pins |= B_AMBER; break;
        case COLOR_GREEN:  pins |= B_GREEN; break;
        default: break;
    }

    HAL_GPIO_WritePin(
        GPIOA, ALL_TRAFFIC_PINS, GPIO_PIN_RESET);

    if (pins != 0)
    {
        HAL_GPIO_WritePin(
            GPIOA, pins, GPIO_PIN_SET);
    }
}
