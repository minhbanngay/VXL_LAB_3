#include "fsm_automatic.h"

#include "global.h"
#include "software_timer.h"
#include "traffic_light.h"

#include <stdbool.h>
#include <stdint.h>

#define AUTOMATIC_TIMER_ID 1U
#define ONE_SECOND_MS 1000U

typedef enum
{
  AUTO_NS_GREEN_EW_RED = 0,
  AUTO_NS_AMBER_EW_RED,
  AUTO_NS_RED_EW_GREEN,
  AUTO_NS_RED_EW_AMBER
} AutomaticState;

static AutomaticState automatic_state;
static bool automatic_entry_flag;
static uint8_t north_south_countdown;
static uint8_t east_west_countdown;
static uint8_t phase_countdown;

void fsm_automatic_init(void)
{
  automatic_state = AUTO_NS_GREEN_EW_RED;
  automatic_entry_flag = true;
  software_timer_cancel(AUTOMATIC_TIMER_ID);
  traffic_light_all_off();
}

void fsm_automatic_run(void)
{
  TrafficTiming timing = global_get_timing();

  switch (automatic_state)
  {
    case AUTO_NS_GREEN_EW_RED:
      if (automatic_entry_flag)
      {
        north_south_countdown = timing.green_seconds;
        east_west_countdown = timing.red_seconds;
        phase_countdown = timing.green_seconds;
        traffic_light_set_road(TRAFFIC_NORTH_SOUTH, TRAFFIC_GREEN);
        traffic_light_set_road(TRAFFIC_EAST_WEST, TRAFFIC_RED);
        traffic_light_display_times(north_south_countdown,
                                    east_west_countdown);
        software_timer_set(AUTOMATIC_TIMER_ID, ONE_SECOND_MS);
        automatic_entry_flag = false;
      }
      if (!software_timer_expired(AUTOMATIC_TIMER_ID))
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
        traffic_light_display_times(north_south_countdown,
                                    east_west_countdown);
        software_timer_set(AUTOMATIC_TIMER_ID, ONE_SECOND_MS);
        break;
      }
      automatic_state = AUTO_NS_AMBER_EW_RED;
      automatic_entry_flag = true;
      break;

    case AUTO_NS_AMBER_EW_RED:
      if (automatic_entry_flag)
      {
        north_south_countdown = timing.amber_seconds;
        phase_countdown = timing.amber_seconds;
        traffic_light_set_road(TRAFFIC_NORTH_SOUTH, TRAFFIC_AMBER);
        traffic_light_set_road(TRAFFIC_EAST_WEST, TRAFFIC_RED);
        traffic_light_display_times(north_south_countdown,
                                    east_west_countdown);
        software_timer_set(AUTOMATIC_TIMER_ID, ONE_SECOND_MS);
        automatic_entry_flag = false;
      }
      if (!software_timer_expired(AUTOMATIC_TIMER_ID))
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
        traffic_light_display_times(north_south_countdown,
                                    east_west_countdown);
        software_timer_set(AUTOMATIC_TIMER_ID, ONE_SECOND_MS);
        break;
      }
      automatic_state = AUTO_NS_RED_EW_GREEN;
      automatic_entry_flag = true;
      break;

    case AUTO_NS_RED_EW_GREEN:
      if (automatic_entry_flag)
      {
        north_south_countdown = timing.red_seconds;
        east_west_countdown = timing.green_seconds;
        phase_countdown = timing.green_seconds;
        traffic_light_set_road(TRAFFIC_NORTH_SOUTH, TRAFFIC_RED);
        traffic_light_set_road(TRAFFIC_EAST_WEST, TRAFFIC_GREEN);
        traffic_light_display_times(north_south_countdown,
                                    east_west_countdown);
        software_timer_set(AUTOMATIC_TIMER_ID, ONE_SECOND_MS);
        automatic_entry_flag = false;
      }
      if (!software_timer_expired(AUTOMATIC_TIMER_ID))
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
        traffic_light_display_times(north_south_countdown,
                                    east_west_countdown);
        software_timer_set(AUTOMATIC_TIMER_ID, ONE_SECOND_MS);
        break;
      }
      automatic_state = AUTO_NS_RED_EW_AMBER;
      automatic_entry_flag = true;
      break;

    case AUTO_NS_RED_EW_AMBER:
      if (automatic_entry_flag)
      {
        east_west_countdown = timing.amber_seconds;
        phase_countdown = timing.amber_seconds;
        traffic_light_set_road(TRAFFIC_NORTH_SOUTH, TRAFFIC_RED);
        traffic_light_set_road(TRAFFIC_EAST_WEST, TRAFFIC_AMBER);
        traffic_light_display_times(north_south_countdown,
                                    east_west_countdown);
        software_timer_set(AUTOMATIC_TIMER_ID, ONE_SECOND_MS);
        automatic_entry_flag = false;
      }
      if (!software_timer_expired(AUTOMATIC_TIMER_ID))
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
        traffic_light_display_times(north_south_countdown,
                                    east_west_countdown);
        software_timer_set(AUTOMATIC_TIMER_ID, ONE_SECOND_MS);
        break;
      }
      automatic_state = AUTO_NS_GREEN_EW_RED;
      automatic_entry_flag = true;
      break;

    default:
      automatic_state = AUTO_NS_GREEN_EW_RED;
      automatic_entry_flag = true;
      break;
  }
}
