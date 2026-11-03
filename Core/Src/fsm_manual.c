#include "fsm_manual.h"

#include "button.h"
#include "fsm_automatic.h"
#include "fsm_setting.h"

void fsm_manual_init(void)
{
  fsm_automatic_init();
}

void fsm_manual_run(void)
{
  if (button_was_pressed(BUTTON_MODE))
  {
    global_next_mode();

    if (global_get_mode() == MODE_AUTOMATIC)
    {
      fsm_automatic_init();
    }

    if (global_get_mode() != MODE_AUTOMATIC)
    {
      fsm_setting_init();
    }
  }

  switch (global_get_mode())
  {
    case MODE_AUTOMATIC:
      fsm_automatic_run();
      break;

    case MODE_SET_RED:
    case MODE_SET_AMBER:
    case MODE_SET_GREEN:
      fsm_setting_run();
      break;

    default:
      global_set_mode(MODE_AUTOMATIC);
      fsm_automatic_init();
      break;
  }
}

SystemMode fsm_manual_get_mode(void)
{
  return global_get_mode();
}
