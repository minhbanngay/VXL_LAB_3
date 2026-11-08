#include "traffic_light.h"
#include "main.h"

#define ALL_TRAFFIC_LED_PINS (NS_RED_Pin | NS_YELLOW_Pin | NS_GREEN_Pin | \
                              EW_RED_Pin | EW_YELLOW_Pin | EW_GREEN_Pin)

void traffic_light_init(void)
{
  HAL_GPIO_WritePin(GPIOA, ALL_TRAFFIC_LED_PINS, GPIO_PIN_RESET);
}

void traffic_light_show(TrafficColor north_south_color,
                        TrafficColor east_west_color)
{
  uint16_t active_pins = 0U;

  switch (north_south_color)
  {
    case TRAFFIC_RED:   active_pins |= NS_RED_Pin;    break;
    case TRAFFIC_AMBER: active_pins |= NS_YELLOW_Pin; break;
    case TRAFFIC_GREEN: active_pins |= NS_GREEN_Pin;  break;
    case TRAFFIC_OFF:
    default: break;
  }

  switch (east_west_color)
  {
    case TRAFFIC_RED:   active_pins |= EW_RED_Pin;    break;
    case TRAFFIC_AMBER: active_pins |= EW_YELLOW_Pin; break;
    case TRAFFIC_GREEN: active_pins |= EW_GREEN_Pin;  break;
    case TRAFFIC_OFF:
    default: break;
  }

  HAL_GPIO_WritePin(GPIOA, ALL_TRAFFIC_LED_PINS, GPIO_PIN_RESET);

  if (active_pins != 0U)
  {
    HAL_GPIO_WritePin(GPIOA, active_pins, GPIO_PIN_SET);
  }
}
