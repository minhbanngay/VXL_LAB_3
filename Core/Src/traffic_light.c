#include "traffic_light.h"
#include "main.h"

/*
 * This module is the only application module that may write traffic LEDs and
 * seven-segment GPIOs. The GPIO implementation will be added after CubeMX has
 * generated the final Lab 3 pin names.
 */

static TrafficColor road_colors[2];
static uint8_t displayed_values[4];

#define ALL_TRAFFIC_LED_PINS (NS_RED_Pin | NS_YELLOW_Pin | NS_GREEN_Pin | \
                              EW_RED_Pin | EW_YELLOW_Pin | EW_GREEN_Pin)
#define ALL_DIGIT_ENABLE_PINS (EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin)
#define ALL_SEGMENT_PINS (SEG_A_Pin | SEG_B_Pin | SEG_C_Pin | SEG_D_Pin | \
                          SEG_E_Pin | SEG_F_Pin | SEG_G_Pin)

void traffic_light_init(void)
{
  road_colors[TRAFFIC_NORTH_SOUTH] = TRAFFIC_RED;
  road_colors[TRAFFIC_EAST_WEST] = TRAFFIC_RED;
  traffic_light_all_off();
}

void traffic_light_all_off(void)
{
  HAL_GPIO_WritePin(GPIOA, ALL_TRAFFIC_LED_PINS, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, ALL_DIGIT_ENABLE_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, ALL_SEGMENT_PINS, GPIO_PIN_SET);
}

void traffic_light_set_road(TrafficRoad road, TrafficColor color)
{
  if (road > TRAFFIC_EAST_WEST)
  {
    return;
  }

  road_colors[road] = color;

  uint16_t road_pins = (road == TRAFFIC_NORTH_SOUTH)
                         ? (NS_RED_Pin | NS_YELLOW_Pin | NS_GREEN_Pin)
                         : (EW_RED_Pin | EW_YELLOW_Pin | EW_GREEN_Pin);
  uint16_t active_pin = 0U;

  if (road == TRAFFIC_NORTH_SOUTH)
  {
    active_pin = (color == TRAFFIC_RED) ? NS_RED_Pin
                 : (color == TRAFFIC_AMBER) ? NS_YELLOW_Pin
                                             : NS_GREEN_Pin;
  }
  else
  {
    active_pin = (color == TRAFFIC_RED) ? EW_RED_Pin
                 : (color == TRAFFIC_AMBER) ? EW_YELLOW_Pin
                                             : EW_GREEN_Pin;
  }

  HAL_GPIO_WritePin(GPIOA, road_pins, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, active_pin, GPIO_PIN_SET);
}

void traffic_light_set_blink(TrafficColor color, bool visible)
{
  uint16_t color_pins = (color == TRAFFIC_RED)
                          ? (NS_RED_Pin | EW_RED_Pin)
                          : (color == TRAFFIC_AMBER)
                              ? (NS_YELLOW_Pin | EW_YELLOW_Pin)
                              : (NS_GREEN_Pin | EW_GREEN_Pin);

  HAL_GPIO_WritePin(GPIOA, color_pins,
                    visible ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void traffic_light_display_times(uint8_t north_south, uint8_t east_west)
{
  displayed_values[0] = north_south / 10U;
  displayed_values[1] = north_south % 10U;
  displayed_values[2] = east_west / 10U;
  displayed_values[3] = east_west % 10U;
}

void traffic_light_display_setting(uint8_t mode, uint8_t value)
{
  displayed_values[0] = mode / 10U;
  displayed_values[1] = mode % 10U;
  displayed_values[2] = value / 10U;
  displayed_values[3] = value % 10U;
}

void traffic_light_refresh_10ms(void)
{
  (void)road_colors;
  (void)displayed_values;
  /* TODO: scan one of the four seven-segment digits on each call. */
}
