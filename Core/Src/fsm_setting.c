#include "fsm_setting.h"

#include "button.h"
#include "display.h"
#include "global.h"
#include "software_timer.h"
#include "traffic_light.h"

#include <stdint.h>

static uint8_t candidate_value;
static uint8_t blink_state;

void fsm_setting_init(void)
{
  blink_state = 1U;

  switch (global_get_mode())
  {
    case MODE_SET_RED:
      candidate_value = global_get_duration(TRAFFIC_RED);
      break;

    case MODE_SET_AMBER:
      candidate_value = global_get_duration(TRAFFIC_AMBER);
      break;

    case MODE_SET_GREEN:
      candidate_value = global_get_duration(TRAFFIC_GREEN);
      break;

    case MODE_AUTOMATIC:
    default:
      break;
  }

  setTimer(0, 250);
}

void fsm_setting_run(void)
{
  switch (global_get_mode())
  {
    case MODE_SET_RED:
      if (timer_flag[0] == 1)
      {
        blink_state = !blink_state;
        setTimer(0, 250);
      }

      if (blink_state == 1U)
        traffic_light_show(TRAFFIC_RED, TRAFFIC_RED);
      else
        traffic_light_show(TRAFFIC_OFF, TRAFFIC_OFF);

      display_set(2U, candidate_value);

      if (button_was_pressed(BUTTON_MODIFY))
      {
        ++candidate_value;
        if (candidate_value > TRAFFIC_TIME_MAX_SECONDS)
          candidate_value = TRAFFIC_TIME_MIN_SECONDS;
      }

      if (button_was_pressed(BUTTON_SET))
      {
        global_set_duration(TRAFFIC_RED, candidate_value);
      }
      break;

    case MODE_SET_AMBER:
      if (timer_flag[0] == 1)
      {
        blink_state = !blink_state;
        setTimer(0, 250);
      }

      if (blink_state == 1U)
        traffic_light_show(TRAFFIC_AMBER, TRAFFIC_AMBER);
      else
        traffic_light_show(TRAFFIC_OFF, TRAFFIC_OFF);

      display_set(3U, candidate_value);

      if (button_was_pressed(BUTTON_MODIFY))
      {
        ++candidate_value;
        if (candidate_value > TRAFFIC_TIME_MAX_SECONDS)
          candidate_value = TRAFFIC_TIME_MIN_SECONDS;
      }

      if (button_was_pressed(BUTTON_SET))
      {
        global_set_duration(TRAFFIC_AMBER, candidate_value);
      }
      break;

    case MODE_SET_GREEN:
      if (timer_flag[0] == 1)
      {
        blink_state = !blink_state;
        setTimer(0, 250);
      }

      if (blink_state == 1U)
        traffic_light_show(TRAFFIC_GREEN, TRAFFIC_GREEN);
      else
        traffic_light_show(TRAFFIC_OFF, TRAFFIC_OFF);

      display_set(4U, candidate_value);

      if (button_was_pressed(BUTTON_MODIFY))
      {
        ++candidate_value;
        if (candidate_value > TRAFFIC_TIME_MAX_SECONDS)
          candidate_value = TRAFFIC_TIME_MIN_SECONDS;
      }

      if (button_was_pressed(BUTTON_SET))
      {
        global_set_duration(TRAFFIC_GREEN, candidate_value);
      }
      break;

    case MODE_AUTOMATIC:
    default:
      break;
  }
}
