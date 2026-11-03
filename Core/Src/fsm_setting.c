#include "fsm_setting.h"

#include "software_timer.h"
#include "traffic_light.h"

#include <stdbool.h>

#define SETTING_BLINK_TIMER_ID 0U
#define SETTING_BLINK_HALF_PERIOD_MS 250U

static TrafficColor selected_color;
static uint8_t selected_mode;
static uint8_t candidate_value;
static bool blink_visible;

void fsm_setting_init(void)
{
  selected_color = TRAFFIC_RED;
  selected_mode = 2U;
  candidate_value = global_get_duration(selected_color);
  blink_visible = false;
  software_timer_cancel(SETTING_BLINK_TIMER_ID);
}

void fsm_setting_enter(TrafficColor color, uint8_t mode)
{
  selected_color = color;
  selected_mode = mode;
  candidate_value = global_get_duration(color);
  blink_visible = true;

  traffic_light_all_off();
  traffic_light_set_blink(selected_color, blink_visible);
  traffic_light_display_setting(selected_mode, candidate_value);
  software_timer_set(SETTING_BLINK_TIMER_ID,
                     SETTING_BLINK_HALF_PERIOD_MS);
}

void fsm_setting_run(void)
{
  if (software_timer_expired(SETTING_BLINK_TIMER_ID))
  {
    blink_visible = !blink_visible;
    traffic_light_set_blink(selected_color, blink_visible);
    software_timer_set(SETTING_BLINK_TIMER_ID,
                       SETTING_BLINK_HALF_PERIOD_MS);
  }

  traffic_light_display_setting(selected_mode, candidate_value);
}

void fsm_setting_exit(void)
{
  software_timer_cancel(SETTING_BLINK_TIMER_ID);
  blink_visible = false;
  traffic_light_all_off();
  traffic_light_display_clear();
}
