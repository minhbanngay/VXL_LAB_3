#include "fsm_setting.h"

static TrafficColor selected_color;
static uint8_t selected_mode;

void fsm_setting_init(void)
{
  selected_color = TRAFFIC_RED;
  selected_mode = 2U;
}

void fsm_setting_enter(TrafficColor color, uint8_t mode)
{
  selected_color = color;
  selected_mode = mode;
}

void fsm_setting_run(void)
{
  (void)selected_color;
  (void)selected_mode;
  /* Exercises 6-9 will add blinking, MODIFY and SET button handling here. */
}
