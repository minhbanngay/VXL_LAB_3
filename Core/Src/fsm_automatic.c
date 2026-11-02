#include "fsm_automatic.h"

#include <stddef.h>

static const TrafficTiming *active_timing;

void fsm_automatic_init(const TrafficTiming *timing)
{
  active_timing = timing;
}

void fsm_automatic_run(void)
{
  if (active_timing == NULL)
  {
    return;
  }

  /* Exercise 10 will implement the complete normal traffic-light FSM here. */
}
