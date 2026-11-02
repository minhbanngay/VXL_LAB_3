#include "software_timer.h"

static volatile uint32_t remaining_ms[SOFTWARE_TIMER_COUNT];
static volatile bool expired_flags[SOFTWARE_TIMER_COUNT];

void software_timer_init(void)
{
  for (uint8_t i = 0U; i < SOFTWARE_TIMER_COUNT; ++i)
  {
    remaining_ms[i] = 0U;
    expired_flags[i] = false;
  }
}

void software_timer_set(uint8_t timer_id, uint32_t duration_ms)
{
  if (timer_id >= SOFTWARE_TIMER_COUNT)
  {
    return;
  }

  remaining_ms[timer_id] = duration_ms;
  expired_flags[timer_id] = (duration_ms == 0U);
}

void software_timer_cancel(uint8_t timer_id)
{
  if (timer_id >= SOFTWARE_TIMER_COUNT)
  {
    return;
  }

  remaining_ms[timer_id] = 0U;
  expired_flags[timer_id] = false;
}

void software_timer_tick(uint32_t elapsed_ms)
{
  for (uint8_t i = 0U; i < SOFTWARE_TIMER_COUNT; ++i)
  {
    if (remaining_ms[i] == 0U)
    {
      continue;
    }

    if (remaining_ms[i] <= elapsed_ms)
    {
      remaining_ms[i] = 0U;
      expired_flags[i] = true;
    }
    else
    {
      remaining_ms[i] -= elapsed_ms;
    }
  }
}

bool software_timer_expired(uint8_t timer_id)
{
  if ((timer_id >= SOFTWARE_TIMER_COUNT) || !expired_flags[timer_id])
  {
    return false;
  }

  expired_flags[timer_id] = false;
  return true;
}

bool software_timer_is_running(uint8_t timer_id)
{
  return (timer_id < SOFTWARE_TIMER_COUNT) && (remaining_ms[timer_id] > 0U);
}
