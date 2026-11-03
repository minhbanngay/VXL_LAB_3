#include "fsm_setting.h"

#include "button.h"
#include "global.h"
#include "software_timer.h"
#include "traffic_light.h"

#include <stdbool.h>
#include <stdint.h>

#define SETTING_BLINK_HALF_PERIOD_MS 250U

static uint8_t candidate_value;
static bool blink_visible;

void fsm_setting_init(void)
{
  blink_visible = true;

  switch (global_get_mode())
  {
    case MODE_SET_RED:
      candidate_value = global_get_duration(TRAFFIC_RED);
      traffic_light_show_setting(TRAFFIC_RED, 2U, candidate_value,
                                 blink_visible);
      break;

    case MODE_SET_AMBER:
      candidate_value = global_get_duration(TRAFFIC_AMBER);
      traffic_light_show_setting(TRAFFIC_AMBER, 3U, candidate_value,
                                 blink_visible);
      break;

    case MODE_SET_GREEN:
      candidate_value = global_get_duration(TRAFFIC_GREEN);
      traffic_light_show_setting(TRAFFIC_GREEN, 4U, candidate_value,
                                 blink_visible);
      break;

    case MODE_AUTOMATIC:
    default:
      break;
  }

  setTimer(SETTING_BLINK_HALF_PERIOD_MS);
}

void fsm_setting_run(void)
{
  bool modify_pressed = button_was_pressed(BUTTON_MODIFY);
  bool set_pressed = button_was_pressed(BUTTON_SET);

  switch (global_get_mode())
  {
    case MODE_SET_RED:
      if (modify_pressed)
      {
        ++candidate_value;
        if (candidate_value > TRAFFIC_TIME_MAX_SECONDS)
        {
          candidate_value = TRAFFIC_TIME_MIN_SECONDS;
        }
      }
      if (set_pressed)
      {
        (void)global_set_duration(TRAFFIC_RED, candidate_value);
      }
      if (timer_flag == 1)
      {
        blink_visible = !blink_visible;
        setTimer(SETTING_BLINK_HALF_PERIOD_MS);
      }
      traffic_light_show_setting(TRAFFIC_RED, 2U, candidate_value,
                                 blink_visible);
      break;

    case MODE_SET_AMBER:
      if (modify_pressed)
      {
        ++candidate_value;
        if (candidate_value > TRAFFIC_TIME_MAX_SECONDS)
        {
          candidate_value = TRAFFIC_TIME_MIN_SECONDS;
        }
      }
      if (set_pressed)
      {
        (void)global_set_duration(TRAFFIC_AMBER, candidate_value);
      }
      if (timer_flag == 1)
      {
        blink_visible = !blink_visible;
        setTimer(SETTING_BLINK_HALF_PERIOD_MS);
      }
      traffic_light_show_setting(TRAFFIC_AMBER, 3U, candidate_value,
                                 blink_visible);
      break;

    case MODE_SET_GREEN:
      if (modify_pressed)
      {
        ++candidate_value;
        if (candidate_value > TRAFFIC_TIME_MAX_SECONDS)
        {
          candidate_value = TRAFFIC_TIME_MIN_SECONDS;
        }
      }
      if (set_pressed)
      {
        (void)global_set_duration(TRAFFIC_GREEN, candidate_value);
      }
      if (timer_flag == 1)
      {
        blink_visible = !blink_visible;
        setTimer(SETTING_BLINK_HALF_PERIOD_MS);
      }
      traffic_light_show_setting(TRAFFIC_GREEN, 4U, candidate_value,
                                 blink_visible);
      break;

    case MODE_AUTOMATIC:
    default:
      break;
  }
}
