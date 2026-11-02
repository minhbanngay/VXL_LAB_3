#include "fsm_manual.h"

#include "button.h"
#include "fsm_automatic.h"
#include "fsm_setting.h"
#include "traffic_light.h"

static SystemMode current_mode;
static TrafficTiming timing;

void fsm_manual_init(void)
{
  current_mode = MODE_AUTOMATIC;
  timing = (TrafficTiming){
    .red_seconds = 5U,
    .amber_seconds = 2U,
    .green_seconds = 3U
  };

  fsm_automatic_init(&timing);
  fsm_setting_init(&timing);
}

void fsm_manual_run(void)
{
  if (button_was_pressed(BUTTON_MODE))
  {
    current_mode = (current_mode == MODE_SET_GREEN)
                     ? MODE_AUTOMATIC
                     : (SystemMode)(current_mode + 1);

    if (current_mode != MODE_AUTOMATIC)
    {
      fsm_setting_enter((TrafficColor)(current_mode - MODE_SET_RED),
                        (uint8_t)current_mode);
    }
  }

  if (current_mode == MODE_AUTOMATIC)
  {
    fsm_automatic_run();
  }
  else
  {
    fsm_setting_run();
  }
}

SystemMode fsm_manual_get_mode(void)
{
  return current_mode;
}
