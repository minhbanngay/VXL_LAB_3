#include "traffic_light.h"
#include "main.h"

/*
 * This module is the only application module that may write traffic LEDs and
 * seven-segment GPIOs. The GPIO implementation will be added after CubeMX has
 * generated the final Lab 3 pin names.
 */

static volatile uint8_t displayed_values[4];
static uint8_t scan_index;

#define ALL_TRAFFIC_LED_PINS (NS_RED_Pin | NS_YELLOW_Pin | NS_GREEN_Pin | \
                              EW_RED_Pin | EW_YELLOW_Pin | EW_GREEN_Pin)
#define ALL_DIGIT_ENABLE_PINS (EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin)
#define ALL_SEGMENT_PINS (SEG_A_Pin | SEG_B_Pin | SEG_C_Pin | SEG_D_Pin | \
                          SEG_E_Pin | SEG_F_Pin | SEG_G_Pin)
#define DISPLAY_BLANK 0xFFU

static const uint16_t digit_segments[10] = {
  SEG_A_Pin | SEG_B_Pin | SEG_C_Pin | SEG_D_Pin | SEG_E_Pin | SEG_F_Pin,
  SEG_B_Pin | SEG_C_Pin,
  SEG_A_Pin | SEG_B_Pin | SEG_D_Pin | SEG_E_Pin | SEG_G_Pin,
  SEG_A_Pin | SEG_B_Pin | SEG_C_Pin | SEG_D_Pin | SEG_G_Pin,
  SEG_B_Pin | SEG_C_Pin | SEG_F_Pin | SEG_G_Pin,
  SEG_A_Pin | SEG_C_Pin | SEG_D_Pin | SEG_F_Pin | SEG_G_Pin,
  SEG_A_Pin | SEG_C_Pin | SEG_D_Pin | SEG_E_Pin | SEG_F_Pin | SEG_G_Pin,
  SEG_A_Pin | SEG_B_Pin | SEG_C_Pin,
  ALL_SEGMENT_PINS,
  SEG_A_Pin | SEG_B_Pin | SEG_C_Pin | SEG_D_Pin | SEG_F_Pin | SEG_G_Pin
};

static const uint16_t digit_enable_pins[4] = {
  EN0_Pin, EN1_Pin, EN2_Pin, EN3_Pin
};

void traffic_light_init(void)
{
  scan_index = 0U;
  for (uint8_t i = 0U; i < 4U; ++i)
  {
    displayed_values[i] = DISPLAY_BLANK;
  }
  HAL_GPIO_WritePin(GPIOA, ALL_TRAFFIC_LED_PINS, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, ALL_DIGIT_ENABLE_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, ALL_SEGMENT_PINS, GPIO_PIN_SET);
}

void traffic_light_show_automatic(TrafficColor north_south_color,
                                  TrafficColor east_west_color,
                                  uint8_t north_south_time,
                                  uint8_t east_west_time)
{
  uint16_t north_south_pin = (north_south_color == TRAFFIC_RED)
                               ? NS_RED_Pin
                               : (north_south_color == TRAFFIC_AMBER)
                                   ? NS_YELLOW_Pin
                                   : NS_GREEN_Pin;
  uint16_t east_west_pin = (east_west_color == TRAFFIC_RED)
                             ? EW_RED_Pin
                             : (east_west_color == TRAFFIC_AMBER)
                                 ? EW_YELLOW_Pin
                                 : EW_GREEN_Pin;

  HAL_GPIO_WritePin(GPIOA, ALL_TRAFFIC_LED_PINS, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, north_south_pin | east_west_pin, GPIO_PIN_SET);

  north_south_time %= 100U;
  east_west_time %= 100U;
  displayed_values[0] = north_south_time / 10U;
  displayed_values[1] = north_south_time % 10U;
  displayed_values[2] = east_west_time / 10U;
  displayed_values[3] = east_west_time % 10U;
}

void traffic_light_show_setting(TrafficColor color, uint8_t mode,
                                uint8_t value, bool visible)
{
  uint16_t color_pins = (color == TRAFFIC_RED)
                          ? (NS_RED_Pin | EW_RED_Pin)
                          : (color == TRAFFIC_AMBER)
                              ? (NS_YELLOW_Pin | EW_YELLOW_Pin)
                              : (NS_GREEN_Pin | EW_GREEN_Pin);

  HAL_GPIO_WritePin(GPIOA, ALL_TRAFFIC_LED_PINS, GPIO_PIN_RESET);
  if (visible)
  {
    HAL_GPIO_WritePin(GPIOA, color_pins, GPIO_PIN_SET);
  }

  mode %= 100U;
  value %= 100U;
  displayed_values[0] = mode / 10U;
  displayed_values[1] = mode % 10U;
  displayed_values[2] = value / 10U;
  displayed_values[3] = value % 10U;
}

void traffic_light_refresh_10ms(void)
{
  HAL_GPIO_WritePin(GPIOA, ALL_DIGIT_ENABLE_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, ALL_SEGMENT_PINS, GPIO_PIN_SET);

  uint8_t digit = displayed_values[scan_index];
  if (digit <= 9U)
  {
    HAL_GPIO_WritePin(GPIOB, digit_segments[digit], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, digit_enable_pins[scan_index], GPIO_PIN_RESET);
  }

  scan_index = (scan_index + 1U) % 4U;
}
