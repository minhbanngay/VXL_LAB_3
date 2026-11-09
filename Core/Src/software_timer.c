#include "software_timer.h"
#include "global.h"

volatile int timer_counter[3] = {0};
volatile int timer_flag[3] = {0};

void setTimer(int index, int duration)
{
    if (index >= 0 && index < 3)
    {
        timer_flag[index] = 0;
        int ticks = duration / TIMER_CYCLE;

        if (ticks <= 0)
        {
            ticks = 1;
        }
        timer_counter[index] = ticks;
    }
}

void timerRun(void)
{
    for (int i = 0; i < 3; i++)
    {
        if (timer_counter[i] > 0)
        {
            timer_counter[i]--;
            if (timer_counter[i] <= 0)
            {
                timer_flag[i] = 1;
            }
        }
    }

    if (timer_flag[1] == 1)
    {
        timer_flag[1] = 0;
        timer_counter[1] = 1000 / TIMER_CYCLE;

        if (status >= AUTO_RED_GREEN && status <= AUTO_AMBER_RED)
        {
            if (countA > 0) countA--;
            if (countB > 0) countB--;
        }
    }
}
