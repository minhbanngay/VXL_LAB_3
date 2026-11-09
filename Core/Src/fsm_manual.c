#include "fsm_manual.h"
#include "fsm_automatic.h"

void fsm_manual_init(void)
{
    status = MANUAL_RED_GREEN;
    Traffic_Show(COLOR_RED, COLOR_GREEN);
    Display_Set(1, 1);
}

void fsm_manual_run(void)
{
    switch (status)
    {
        case MANUAL_RED_GREEN:
            Traffic_Show(COLOR_RED, COLOR_GREEN);
            Display_Set(1, 1);

            if (isButton3Pressed())
            {
                status = MANUAL_RED_AMBER;
            }
            if (isButton1Pressed())
            {
                status = SET_RED;
                temp_red = time_red;
                setTimer(0, 250);
            }
            if (isButton2Pressed())
            {
                fsm_automatic_init();
            }
            break;

        case MANUAL_RED_AMBER:
            Traffic_Show(COLOR_RED, COLOR_AMBER);
            Display_Set(1, 2);

            if (isButton3Pressed())
            {
                status = MANUAL_GREEN_RED;
            }
            if (isButton1Pressed())
            {
                status = SET_RED;
                temp_red = time_red;
                setTimer(0, 250);
            }
            if (isButton2Pressed())
            {
                fsm_automatic_init();
            }
            break;

        case MANUAL_GREEN_RED:
            Traffic_Show(COLOR_GREEN, COLOR_RED);
            Display_Set(1, 3);

            if (isButton3Pressed())
            {
                status = MANUAL_AMBER_RED;
            }
            if (isButton1Pressed())
            {
                status = SET_RED;
                temp_red = time_red;
                setTimer(0, 250);
            }
            if (isButton2Pressed())
            {
                fsm_automatic_init();
            }
            break;

        case MANUAL_AMBER_RED:
            Traffic_Show(COLOR_AMBER, COLOR_RED);
            Display_Set(1, 4);

            if (isButton3Pressed())
            {
                status = MANUAL_RED_GREEN;
            }
            if (isButton1Pressed())
            {
                status = SET_RED;
                temp_red = time_red;
                setTimer(0, 250);
            }
            if (isButton2Pressed())
            {
                fsm_automatic_init();
            }
            break;

        default:
            break;
    }
}
