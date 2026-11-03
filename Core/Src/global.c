#include "global.h"

static SystemMode current_mode;
static TrafficTiming traffic_timing;

void global_init(void)
{
  current_mode = MODE_AUTOMATIC;
  traffic_timing.red_seconds = 5U;
  traffic_timing.amber_seconds = 2U;
  traffic_timing.green_seconds = 3U;
}

SystemMode global_get_mode(void)
{
  return current_mode;
}

void global_set_mode(SystemMode mode)
{
  if ((mode >= MODE_AUTOMATIC) && (mode <= MODE_SET_GREEN))
  {
    current_mode = mode;
  }
}

void global_next_mode(void)
{
  current_mode = (current_mode == MODE_SET_GREEN)
                   ? MODE_AUTOMATIC
                   : (SystemMode)(current_mode + 1);
}

TrafficTiming global_get_timing(void)
{
  return traffic_timing;
}

uint8_t global_get_duration(TrafficColor color)
{
  switch (color)
  {
    case TRAFFIC_RED:
      return traffic_timing.red_seconds;

    case TRAFFIC_AMBER:
      return traffic_timing.amber_seconds;

    case TRAFFIC_GREEN:
      return traffic_timing.green_seconds;

    default:
      return 0U;
  }
}

bool global_set_duration(TrafficColor color, uint8_t seconds)
{
  if ((seconds < TRAFFIC_TIME_MIN_SECONDS) ||
      (seconds > TRAFFIC_TIME_MAX_SECONDS))
  {
    return false;
  }

  switch (color)
  {
    case TRAFFIC_RED:
      traffic_timing.red_seconds = seconds;
      break;

    case TRAFFIC_AMBER:
      traffic_timing.amber_seconds = seconds;
      break;

    case TRAFFIC_GREEN:
      traffic_timing.green_seconds = seconds;
      break;

    default:
      return false;
  }

  return true;
}
