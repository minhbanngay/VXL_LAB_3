#include "button.h"

#define BUTTON_DEBOUNCE_SAMPLES 2U
#define BUTTON_LONG_PRESS_TICKS 100U

typedef struct
{
  ButtonConfig config;
  GPIO_PinState previous_raw;
  GPIO_PinState stable_state;
  uint8_t matching_samples;
  uint16_t pressed_ticks;
  bool press_event;
  bool long_press_event;
  bool configured;
} ButtonData;

static ButtonData buttons[BUTTON_COUNT];

void button_init(const ButtonConfig configs[BUTTON_COUNT])
{
  for (uint8_t i = 0U; i < BUTTON_COUNT; ++i)
  {
    buttons[i].configured = (configs != NULL) && (configs[i].port != NULL);
    buttons[i].config = buttons[i].configured
                          ? configs[i]
                          : (ButtonConfig){NULL, 0U, GPIO_PIN_RESET};
    buttons[i].previous_raw = GPIO_PIN_SET;
    buttons[i].stable_state = GPIO_PIN_SET;
    buttons[i].matching_samples = 0U;
    buttons[i].pressed_ticks = 0U;
    buttons[i].press_event = false;
    buttons[i].long_press_event = false;

    if (buttons[i].configured)
    {
      buttons[i].previous_raw = HAL_GPIO_ReadPin(buttons[i].config.port,
                                                 buttons[i].config.pin);
      buttons[i].stable_state = buttons[i].previous_raw;
    }
  }
}

void button_tick(void)
{
  for (uint8_t i = 0U; i < BUTTON_COUNT; ++i)
  {
    if (!buttons[i].configured)
    {
      continue;
    }

    GPIO_PinState raw = HAL_GPIO_ReadPin(buttons[i].config.port,
                                         buttons[i].config.pin);

    if (raw == buttons[i].previous_raw)
    {
      if (buttons[i].matching_samples < BUTTON_DEBOUNCE_SAMPLES)
      {
        ++buttons[i].matching_samples;
      }
    }
    else
    {
      buttons[i].previous_raw = raw;
      buttons[i].matching_samples = 1U;
    }

    if ((buttons[i].matching_samples >= BUTTON_DEBOUNCE_SAMPLES) &&
        (buttons[i].stable_state != raw))
    {
      buttons[i].stable_state = raw;
      buttons[i].pressed_ticks = 0U;

      if (raw == buttons[i].config.pressed_level)
      {
        buttons[i].press_event = true;
      }
    }

    if (buttons[i].stable_state == buttons[i].config.pressed_level)
    {
      if (buttons[i].pressed_ticks < BUTTON_LONG_PRESS_TICKS)
      {
        ++buttons[i].pressed_ticks;
      }
      else if (buttons[i].pressed_ticks == BUTTON_LONG_PRESS_TICKS)
      {
        buttons[i].long_press_event = true;
        ++buttons[i].pressed_ticks;
      }
    }
    else
    {
      buttons[i].pressed_ticks = 0U;
    }
  }
}

bool button_is_pressed(ButtonId button)
{
  return (button < BUTTON_COUNT) && buttons[button].configured &&
         (buttons[button].stable_state == buttons[button].config.pressed_level);
}

bool button_was_pressed(ButtonId button)
{
  if ((button >= BUTTON_COUNT) || !buttons[button].press_event)
  {
    return false;
  }

  buttons[button].press_event = false;
  return true;
}

bool button_was_long_pressed(ButtonId button)
{
  if ((button >= BUTTON_COUNT) || !buttons[button].long_press_event)
  {
    return false;
  }

  buttons[button].long_press_event = false;
  return true;
}
