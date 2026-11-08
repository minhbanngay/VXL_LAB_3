#include "software_timer.h"

volatile int timer_counter[SOFTWARE_TIMER_COUNT] = {0};
volatile int timer_flag[SOFTWARE_TIMER_COUNT] = {0};

void setTimer(int index, int duration)
{
  if ((index < 0) || (index >= SOFTWARE_TIMER_COUNT))
  {
    return;
  }

  timer_counter[index] = duration / TIMER_CYCLE;
  if (timer_counter[index] <= 0)
  {
    timer_counter[index] = 1;
  }

  timer_flag[index] = 0;
}

void timerRun(void)
{
  for (int i = 0; i < SOFTWARE_TIMER_COUNT; ++i)
  {
    if (timer_counter[i] > 0)
    {
      --timer_counter[i];

      if (timer_counter[i] == 0)
      {
        timer_flag[i] = 1;
      }
    }
  }
}
