#include "fsm_automatic.h"

#include "global.h"
#include "software_timer.h"
#include "traffic_light.h"

#include <stdint.h>

#define AUTOMATIC_SECOND_TIMER_ID 1U
#define ONE_SECOND_MS 1000U

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
static uint8_t phase_countdown;

static void automatic_enter_state(AutomaticState new_state)
{
  TrafficTiming timing = global_get_timing();

  automatic_state = new_state;

  switch (automatic_state)
  {
    case AUTO_NS_GREEN_EW_RED:
      north_south_countdown = timing.green_seconds;
      east_west_countdown = timing.red_seconds;
      phase_countdown = timing.green_seconds;
      traffic_light_set_road(TRAFFIC_NORTH_SOUTH, TRAFFIC_GREEN);
      traffic_light_set_road(TRAFFIC_EAST_WEST, TRAFFIC_RED);
      break;

    case AUTO_NS_AMBER_EW_RED:
      north_south_countdown = timing.amber_seconds;
      phase_countdown = timing.amber_seconds;
      traffic_light_set_road(TRAFFIC_NORTH_SOUTH, TRAFFIC_AMBER);
      traffic_light_set_road(TRAFFIC_EAST_WEST, TRAFFIC_RED);
      break;

    case AUTO_NS_RED_EW_GREEN:
      north_south_countdown = timing.red_seconds;
      east_west_countdown = timing.green_seconds;
      phase_countdown = timing.green_seconds;
      traffic_light_set_road(TRAFFIC_NORTH_SOUTH, TRAFFIC_RED);
      traffic_light_set_road(TRAFFIC_EAST_WEST, TRAFFIC_GREEN);
      break;

    case AUTO_NS_RED_EW_AMBER:
      east_west_countdown = timing.amber_seconds;
      phase_countdown = timing.amber_seconds;
      traffic_light_set_road(TRAFFIC_NORTH_SOUTH, TRAFFIC_RED);
      traffic_light_set_road(TRAFFIC_EAST_WEST, TRAFFIC_AMBER);
      break;

    default:
      break;
  }

  traffic_light_display_times(north_south_countdown,
                              east_west_countdown);
  software_timer_set(AUTOMATIC_SECOND_TIMER_ID, ONE_SECOND_MS);
}

static AutomaticState automatic_next_state(void)
{
  switch (automatic_state)
  {
    case AUTO_NS_GREEN_EW_RED:
      return AUTO_NS_AMBER_EW_RED;

    case AUTO_NS_AMBER_EW_RED:
      return AUTO_NS_RED_EW_GREEN;

    case AUTO_NS_RED_EW_GREEN:
      return AUTO_NS_RED_EW_AMBER;

    case AUTO_NS_RED_EW_AMBER:
    default:
      return AUTO_NS_GREEN_EW_RED;
  }
}

void fsm_automatic_init(void)
{
  traffic_light_all_off();
  automatic_enter_state(AUTO_NS_GREEN_EW_RED);
}

void fsm_automatic_run(void)
{
  if (!software_timer_expired(AUTOMATIC_SECOND_TIMER_ID))
  {
    return;
  }

  if (north_south_countdown > 0U)
  {
    --north_south_countdown;
  }

  if (east_west_countdown > 0U)
  {
    --east_west_countdown;
  }

  if (phase_countdown > 0U)
  {
    --phase_countdown;
  }

  if (phase_countdown == 0U)
  {
    automatic_enter_state(automatic_next_state());
  }
  else
  {
    traffic_light_display_times(north_south_countdown,
                                east_west_countdown);
    software_timer_set(AUTOMATIC_SECOND_TIMER_ID, ONE_SECOND_MS);
  }
}
