#include "fsm_automatic.h"

#include "global.h"
#include "software_timer.h"
#include "traffic_light.h"

#include <stdint.h>

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

void fsm_automatic_init(void)
{
  TrafficTiming timing = global_get_timing();

  automatic_state = AUTO_NS_GREEN_EW_RED;
  north_south_countdown = timing.green_seconds;
  east_west_countdown = timing.red_seconds;
  phase_countdown = timing.green_seconds;
  traffic_light_show_automatic(TRAFFIC_GREEN, TRAFFIC_RED,
                               north_south_countdown,
                               east_west_countdown);
  setTimer(ONE_SECOND_MS);
}

void fsm_automatic_run(void)
{
  TrafficTiming timing = global_get_timing();

  switch (automatic_state)
  {
    case AUTO_NS_GREEN_EW_RED:
      if (timer_flag == 0)
      {
        break;
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
      if (phase_countdown > 0U)
      {
        traffic_light_show_automatic(TRAFFIC_GREEN, TRAFFIC_RED,
                                     north_south_countdown,
                                     east_west_countdown);
        setTimer(ONE_SECOND_MS);
        break;
      }
      automatic_state = AUTO_NS_AMBER_EW_RED;
      north_south_countdown = timing.amber_seconds;
      phase_countdown = timing.amber_seconds;
      traffic_light_show_automatic(TRAFFIC_AMBER, TRAFFIC_RED,
                                   north_south_countdown,
                                   east_west_countdown);
      setTimer(ONE_SECOND_MS);
      break;

    case AUTO_NS_AMBER_EW_RED:
      if (timer_flag == 0)
      {
        break;
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
      if (phase_countdown > 0U)
      {
        traffic_light_show_automatic(TRAFFIC_AMBER, TRAFFIC_RED,
                                     north_south_countdown,
                                     east_west_countdown);
        setTimer(ONE_SECOND_MS);
        break;
      }
      automatic_state = AUTO_NS_RED_EW_GREEN;
      north_south_countdown = timing.red_seconds;
      east_west_countdown = timing.green_seconds;
      phase_countdown = timing.green_seconds;
      traffic_light_show_automatic(TRAFFIC_RED, TRAFFIC_GREEN,
                                   north_south_countdown,
                                   east_west_countdown);
      setTimer(ONE_SECOND_MS);
      break;

    case AUTO_NS_RED_EW_GREEN:
      if (timer_flag == 0)
      {
        break;
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
      if (phase_countdown > 0U)
      {
        traffic_light_show_automatic(TRAFFIC_RED, TRAFFIC_GREEN,
                                     north_south_countdown,
                                     east_west_countdown);
        setTimer(ONE_SECOND_MS);
        break;
      }
      automatic_state = AUTO_NS_RED_EW_AMBER;
      east_west_countdown = timing.amber_seconds;
      phase_countdown = timing.amber_seconds;
      traffic_light_show_automatic(TRAFFIC_RED, TRAFFIC_AMBER,
                                   north_south_countdown,
                                   east_west_countdown);
      setTimer(ONE_SECOND_MS);
      break;

    case AUTO_NS_RED_EW_AMBER:
      if (timer_flag == 0)
      {
        break;
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
      if (phase_countdown > 0U)
      {
        traffic_light_show_automatic(TRAFFIC_RED, TRAFFIC_AMBER,
                                     north_south_countdown,
                                     east_west_countdown);
        setTimer(ONE_SECOND_MS);
        break;
      }
      automatic_state = AUTO_NS_GREEN_EW_RED;
      north_south_countdown = timing.green_seconds;
      east_west_countdown = timing.red_seconds;
      phase_countdown = timing.green_seconds;
      traffic_light_show_automatic(TRAFFIC_GREEN, TRAFFIC_RED,
                                   north_south_countdown,
                                   east_west_countdown);
      setTimer(ONE_SECOND_MS);
      break;

    default:
      automatic_state = AUTO_NS_GREEN_EW_RED;
      north_south_countdown = timing.green_seconds;
      east_west_countdown = timing.red_seconds;
      phase_countdown = timing.green_seconds;
      traffic_light_show_automatic(TRAFFIC_GREEN, TRAFFIC_RED,
                                   north_south_countdown,
                                   east_west_countdown);
      setTimer(ONE_SECOND_MS);
      break;
  }
}
