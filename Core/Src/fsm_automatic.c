#include "fsm_automatic.h"
#include "fsm_manual.h"

void fsm_automatic_init(void)
{
    status = AUTO_RED_GREEN;
    countA = time_red;
    countB = time_green;

    Traffic_Show(COLOR_RED, COLOR_GREEN);
    Display_Set(countA, countB);

    setTimer(0, time_green * 1000);
    setTimer(1, 1000);
}

void fsm_automatic_run(void)
{
    switch (status)
    {
        case AUTO_RED_GREEN:
            Traffic_Show(COLOR_RED, COLOR_GREEN);
            Display_Set(countA, countB);

            if (isButton1Pressed())
            {
                status = SET_RED;
                temp_red = time_red;
                setTimer(0, 250);
                break;
            }

            if (isButton2Pressed())
            {
                fsm_manual_init();
                break;
            }

            if (timer_flag[0] == 1)
            {
                status = AUTO_RED_AMBER;
                countB = time_amber;
                setTimer(0, time_amber * 1000);
            }
            break;

        case AUTO_RED_AMBER:
            Traffic_Show(COLOR_RED, COLOR_AMBER);
            Display_Set(countA, countB);

            if (isButton1Pressed())
            {
                status = SET_RED;
                temp_red = time_red;
                setTimer(0, 250);
                break;
            }

            if (isButton2Pressed())
            {
                fsm_manual_init();
                break;
            }

            if (timer_flag[0] == 1)
            {
                status = AUTO_GREEN_RED;
                countA = time_green;
                countB = time_red;
                setTimer(0, time_green * 1000);
            }
            break;

        case AUTO_GREEN_RED:
            Traffic_Show(COLOR_GREEN, COLOR_RED);
            Display_Set(countA, countB);

            if (isButton1Pressed())
            {
                status = SET_RED;
                temp_red = time_red;
                setTimer(0, 250);
                break;
            }

            if (isButton2Pressed())
            {
                fsm_manual_init();
                break;
            }

            if (timer_flag[0] == 1)
            {
                status = AUTO_AMBER_RED;
                countA = time_amber;
                setTimer(0, time_amber * 1000);
            }
            break;

        case AUTO_AMBER_RED:
            Traffic_Show(COLOR_AMBER, COLOR_RED);
            Display_Set(countA, countB);

            if (isButton1Pressed())
            {
                status = SET_RED;
                temp_red = time_red;
                setTimer(0, 250);
                break;
            }

            if (isButton2Pressed())
            {
                fsm_manual_init();
                break;
            }

            if (timer_flag[0] == 1)
            {
                status = AUTO_RED_GREEN;
                countA = time_red;
                countB = time_green;
                setTimer(0, time_green * 1000);
            }
            break;

        default:
            break;
    }
}
