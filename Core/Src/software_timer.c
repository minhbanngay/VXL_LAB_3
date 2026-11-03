#include "software_timer.h"

static volatile int timer_counter = 0;
volatile int timer_flag = 0;

void setTimer(int duration)
{
  timer_counter = duration / TIMER_CYCLE;
  timer_flag = 0;
}

void timerRun(void)
{
  if (timer_counter > 0)
  {
    --timer_counter;
    if (timer_counter == 0)
    {
      timer_flag = 1;
    }
  }
}
