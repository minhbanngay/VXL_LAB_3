#include "display.h"
#include "main.h"

#define ALL_DIGIT_ENABLE_PINS (EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin)
#define ALL_SEGMENT_PINS (SEG_A_Pin | SEG_B_Pin | SEG_C_Pin | SEG_D_Pin | \
                          SEG_E_Pin | SEG_F_Pin | SEG_G_Pin)

static volatile uint8_t display_digits[4];
static uint8_t scan_index;

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

void display_init(void)
{
  scan_index = 0U;
  display_set(0U, 0U);
  HAL_GPIO_WritePin(GPIOA, ALL_DIGIT_ENABLE_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, ALL_SEGMENT_PINS, GPIO_PIN_SET);
}

void display_set(uint8_t left, uint8_t right)
{
  left %= 100U;
  right %= 100U;

  display_digits[0] = left / 10U;
  display_digits[1] = left % 10U;
  display_digits[2] = right / 10U;
  display_digits[3] = right % 10U;
}

void display_refresh_10ms(void)
{
  HAL_GPIO_WritePin(GPIOA, ALL_DIGIT_ENABLE_PINS, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, ALL_SEGMENT_PINS, GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOB, digit_segments[display_digits[scan_index]],
                    GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, digit_enable_pins[scan_index], GPIO_PIN_RESET);

  ++scan_index;
  if (scan_index >= 4U)
  {
    scan_index = 0U;
  }
}

