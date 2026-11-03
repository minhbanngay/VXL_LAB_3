#include "fsm_setting.h"

#include "button.h"
#include "global.h"
#include "software_timer.h"
#include "traffic_light.h"

#include <stdbool.h>
#include <stdint.h>

#define SETTING_BLINK_TIMER_ID 0U
#define SETTING_BLINK_HALF_PERIOD_MS 250U

static uint8_t candidate_value;
static bool blink_visible;
static bool setting_entry_flag;

void fsm_setting_init(void)
{
  setting_entry_flag = true;
  blink_visible = false;
  software_timer_cancel(SETTING_BLINK_TIMER_ID);
}

void fsm_setting_run(void)
{
  bool modify_pressed = button_was_pressed(BUTTON_MODIFY);
  bool set_pressed = button_was_pressed(BUTTON_SET);

  switch (global_get_mode())
  {
    case MODE_SET_RED:
      if (setting_entry_flag)
      {
        candidate_value = global_get_duration(TRAFFIC_RED);
        blink_visible = true;
        traffic_light_all_off();
        traffic_light_set_blink(TRAFFIC_RED, blink_visible);
        traffic_light_display_setting(2U, candidate_value);
        software_timer_set(SETTING_BLINK_TIMER_ID,
                           SETTING_BLINK_HALF_PERIOD_MS);
        setting_entry_flag = false;
      }
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
      if (software_timer_expired(SETTING_BLINK_TIMER_ID))
      {
        blink_visible = !blink_visible;
        traffic_light_set_blink(TRAFFIC_RED, blink_visible);
        software_timer_set(SETTING_BLINK_TIMER_ID,
                           SETTING_BLINK_HALF_PERIOD_MS);
      }
      traffic_light_display_setting(2U, candidate_value);
      break;

    case MODE_SET_AMBER:
      if (setting_entry_flag)
      {
        candidate_value = global_get_duration(TRAFFIC_AMBER);
        blink_visible = true;
        traffic_light_all_off();
        traffic_light_set_blink(TRAFFIC_AMBER, blink_visible);
        traffic_light_display_setting(3U, candidate_value);
        software_timer_set(SETTING_BLINK_TIMER_ID,
                           SETTING_BLINK_HALF_PERIOD_MS);
        setting_entry_flag = false;
      }
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
      if (software_timer_expired(SETTING_BLINK_TIMER_ID))
      {
        blink_visible = !blink_visible;
        traffic_light_set_blink(TRAFFIC_AMBER, blink_visible);
        software_timer_set(SETTING_BLINK_TIMER_ID,
                           SETTING_BLINK_HALF_PERIOD_MS);
      }
      traffic_light_display_setting(3U, candidate_value);
      break;

    case MODE_SET_GREEN:
      if (setting_entry_flag)
      {
        candidate_value = global_get_duration(TRAFFIC_GREEN);
        blink_visible = true;
        traffic_light_all_off();
        traffic_light_set_blink(TRAFFIC_GREEN, blink_visible);
        traffic_light_display_setting(4U, candidate_value);
        software_timer_set(SETTING_BLINK_TIMER_ID,
                           SETTING_BLINK_HALF_PERIOD_MS);
        setting_entry_flag = false;
      }
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
      if (software_timer_expired(SETTING_BLINK_TIMER_ID))
      {
        blink_visible = !blink_visible;
        traffic_light_set_blink(TRAFFIC_GREEN, blink_visible);
        software_timer_set(SETTING_BLINK_TIMER_ID,
                           SETTING_BLINK_HALF_PERIOD_MS);
      }
      traffic_light_display_setting(4U, candidate_value);
      break;

    case MODE_AUTOMATIC:
    default:
      break;
  }
}
