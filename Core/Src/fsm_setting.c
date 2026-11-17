#include "fsm_setting.h"
#include "fsm_automatic.h"

static uint8_t blink_state = 1;

void fsm_setting_run(void)
{
    switch (status)
    {
        case SET_RED:
            if (timer_flag[0] == 1)
            {
                setTimer(0, 250);
                blink_state = !blink_state;
            }
            if (blink_state) Traffic_Show(COLOR_RED, COLOR_RED);
            else             Traffic_Show(COLOR_OFF, COLOR_OFF);

            Display_Set(2, temp_red);

            if (isButton2Pressed())
            {
                temp_red++;
                if (temp_red > 99) temp_red = 1;
            }

            if (isButton3Pressed())
            {
                time_red = temp_red;
                if (time_red <= time_amber)
                {
                    time_amber = 1;
                    time_green = (time_red > 1) ? (time_red - 1) : 1;
                }
                else
                {
                    time_green = time_red - time_amber;
                }
            }

            if (isButton1Pressed())
            {
                status = SET_AMBER;
                temp_amber = time_amber;
                blink_state = 1;
                setTimer(0, 250);
            }
            break;

        case SET_AMBER:
            if (timer_flag[0] == 1)
            {
                setTimer(0, 250);
                blink_state = !blink_state;
            }
            if (blink_state) Traffic_Show(COLOR_AMBER, COLOR_AMBER);
            else             Traffic_Show(COLOR_OFF, COLOR_OFF);

            Display_Set(3, temp_amber);

            if (isButton2Pressed())
            {
                temp_amber++;
                if (temp_amber > 99) temp_amber = 1;
            }

            if (isButton3Pressed())
            {
                time_amber = temp_amber;
                time_red = time_green + time_amber;
            }

            if (isButton1Pressed())
            {
                status = SET_GREEN;
                temp_green = time_green;
                blink_state = 1;
                setTimer(0, 250);
            }
            break;

        case SET_GREEN:
            if (timer_flag[0] == 1)
            {
                setTimer(0, 250);
                blink_state = !blink_state;
            }
            if (blink_state) Traffic_Show(COLOR_GREEN, COLOR_GREEN);
            else             Traffic_Show(COLOR_OFF, COLOR_OFF);

            Display_Set(4, temp_green);

            if (isButton2Pressed())
            {
                temp_green++;
                if (temp_green > 99) temp_green = 1;
            }

            if (isButton3Pressed())
            {
                time_green = temp_green;
                time_red = time_green + time_amber;
            }

            if (isButton1Pressed())
            {
                fsm_automatic_init();
            }
            break;

        default:
            break;
    }
}
