#include "traffic_light.h"

/*
 * This module is the only application module that may write traffic LEDs and
 * seven-segment GPIOs. The GPIO implementation will be added after CubeMX has
 * generated the final Lab 3 pin names.
 */

static TrafficColor road_colors[2];
static uint8_t displayed_values[4];

void traffic_light_init(void)
{
  road_colors[TRAFFIC_NORTH_SOUTH] = TRAFFIC_RED;
  road_colors[TRAFFIC_EAST_WEST] = TRAFFIC_RED;
  traffic_light_all_off();
}

void traffic_light_all_off(void)
{
  /* TODO: turn off all 12 traffic LEDs and all four seven-segment digits. */
}

void traffic_light_set_road(TrafficRoad road, TrafficColor color)
{
  if (road > TRAFFIC_EAST_WEST)
  {
    return;
  }

  road_colors[road] = color;
  /* TODO: apply road_colors to the 12 traffic-light GPIOs. */
}

void traffic_light_set_blink(TrafficColor color, bool visible)
{
  (void)color;
  (void)visible;
  /* TODO: show or hide all four LEDs of the selected color. */
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
