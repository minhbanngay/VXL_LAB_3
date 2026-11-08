#include "fsm_automatic.h"

#include "display.h"
#include "global.h"
#include "software_timer.h"
#include "traffic_light.h"

#include <stdint.h>

typedef enum
{
  AUTO_NS_GREEN_EW_RED = 0,
  AUTO_NS_AMBER_EW_RED,
  AUTO_NS_RED_EW_GREEN,
  AUTO_NS_RED_EW_AMBER
} AutomaticState;

static AutomaticState automatic_state;
static uint8_t north_south_countdown;
static uint8_t east_west_countdown;

void fsm_automatic_init(void)
{
  TrafficTiming timing = global_get_timing();

  automatic_state = AUTO_NS_GREEN_EW_RED;
  north_south_countdown = timing.green_seconds;
  east_west_countdown = timing.red_seconds;

  setTimer(0, timing.green_seconds * 1000);
  setTimer(1, 1000);
}

void fsm_automatic_run(void)
{
  if (global_get_mode() != MODE_AUTOMATIC)
  {
    return;
  }

  TrafficTiming timing = global_get_timing();

  if (timer_flag[1] == 1)
  {
    setTimer(1, 1000);
    if (north_south_countdown > 0U) --north_south_countdown;
    if (east_west_countdown > 0U) --east_west_countdown;
  }

  switch (automatic_state)
  {
    case AUTO_NS_GREEN_EW_RED:
      traffic_light_show(TRAFFIC_GREEN, TRAFFIC_RED);
      display_set(north_south_countdown, east_west_countdown);

      if (timer_flag[0] == 1)
      {
        automatic_state = AUTO_NS_AMBER_EW_RED;
        north_south_countdown = timing.amber_seconds;
        setTimer(0, timing.amber_seconds * 1000);
      }
      break;

    case AUTO_NS_AMBER_EW_RED:
      traffic_light_show(TRAFFIC_AMBER, TRAFFIC_RED);
      display_set(north_south_countdown, east_west_countdown);

      if (timer_flag[0] == 1)
      {
        automatic_state = AUTO_NS_RED_EW_GREEN;
        north_south_countdown = timing.red_seconds;
        east_west_countdown = timing.green_seconds;
        setTimer(0, timing.green_seconds * 1000);
      }
      break;

    case AUTO_NS_RED_EW_GREEN:
      traffic_light_show(TRAFFIC_RED, TRAFFIC_GREEN);
      display_set(north_south_countdown, east_west_countdown);

      if (timer_flag[0] == 1)
      {
        automatic_state = AUTO_NS_RED_EW_AMBER;
        east_west_countdown = timing.amber_seconds;
        setTimer(0, timing.amber_seconds * 1000);
      }
      break;

    case AUTO_NS_RED_EW_AMBER:
      traffic_light_show(TRAFFIC_RED, TRAFFIC_AMBER);
      display_set(north_south_countdown, east_west_countdown);

      if (timer_flag[0] == 1)
      {
        automatic_state = AUTO_NS_GREEN_EW_RED;
        north_south_countdown = timing.green_seconds;
        east_west_countdown = timing.red_seconds;
        setTimer(0, timing.green_seconds * 1000);
      }
      break;

    default:
      fsm_automatic_init();
      break;
  }
}
