#include "fsm_manual.h"

#include "button.h"
#include "fsm_automatic.h"
#include "fsm_setting.h"
#include "global.h"

void fsm_manual_init(void)
{
  fsm_automatic_init();
}

void fsm_manual_run(void)
{
  if (!button_was_pressed(BUTTON_MODE))
  {
    return;
  }

  switch (global_get_mode())
  {
    case MODE_AUTOMATIC:
      global_set_mode(MODE_SET_RED);
      fsm_setting_init();
      break;

    case MODE_SET_RED:
      global_set_mode(MODE_SET_AMBER);
      fsm_setting_init();
      break;

    case MODE_SET_AMBER:
      global_set_mode(MODE_SET_GREEN);
      fsm_setting_init();
      break;

    case MODE_SET_GREEN:
    default:
      global_set_mode(MODE_AUTOMATIC);
      fsm_automatic_init();
      break;
  }
}
