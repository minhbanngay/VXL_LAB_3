#include "fsm_manual.h"

#include "button.h"
#include "fsm_automatic.h"
#include "fsm_setting.h"

void fsm_manual_init(void)
{
  fsm_automatic_init();
  fsm_setting_init();
}

void fsm_manual_run(void)
{
  if (button_was_pressed(BUTTON_MODE))
  {
    global_next_mode();
    SystemMode current_mode = global_get_mode();

    if (current_mode != MODE_AUTOMATIC)
    {
      fsm_setting_enter((TrafficColor)(current_mode - MODE_SET_RED),
                        (uint8_t)current_mode);
    }
    else
    {
      fsm_setting_exit();
    }
  }

  SystemMode current_mode = global_get_mode();

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
  return global_get_mode();
}
