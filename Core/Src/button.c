#include "button.h"
#include "main.h"

#define BUTTON_DEBOUNCE_SAMPLES 2U

static GPIO_TypeDef * const button_ports[BUTTON_COUNT] = {
  MODE_GPIO_Port,
  MODIFY_GPIO_Port,
  SET_GPIO_Port
};

static const uint16_t button_pins[BUTTON_COUNT] = {
  MODE_Pin,
  MODIFY_Pin,
  SET_Pin
};

static GPIO_PinState stable_state[BUTTON_COUNT];
static GPIO_PinState last_raw_state[BUTTON_COUNT];
static uint8_t matching_samples[BUTTON_COUNT];
static volatile uint8_t button_events;

void button_init(void)
{
  button_events = 0U;

  for (uint8_t i = 0U; i < BUTTON_COUNT; ++i)
  {
    stable_state[i] = HAL_GPIO_ReadPin(button_ports[i], button_pins[i]);
    last_raw_state[i] = stable_state[i];
    matching_samples[i] = 0U;
  }
}

void button_tick(void)
{
  for (uint8_t i = 0U; i < BUTTON_COUNT; ++i)
  {
    GPIO_PinState raw_state =
        HAL_GPIO_ReadPin(button_ports[i], button_pins[i]);

    if (raw_state == last_raw_state[i])
    {
      if (matching_samples[i] < BUTTON_DEBOUNCE_SAMPLES)
      {
        ++matching_samples[i];
      }
    }
    else
    {
      last_raw_state[i] = raw_state;
      matching_samples[i] = 1U;
    }

    if ((matching_samples[i] >= BUTTON_DEBOUNCE_SAMPLES) &&
        (stable_state[i] != raw_state))
    {
      stable_state[i] = raw_state;

      if (raw_state == GPIO_PIN_RESET)
      {
        button_events |= (uint8_t)(1U << i);
      }
    }
  }
}

bool button_was_pressed(ButtonId button)
{
  if (button >= BUTTON_COUNT)
  {
    return false;
  }

  uint8_t event_mask = (uint8_t)(1U << button);

  if ((button_events & event_mask) == 0U)
  {
    return false;
  }

  button_events &= (uint8_t)(~event_mask);
  return true;
}
