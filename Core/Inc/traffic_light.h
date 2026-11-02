#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
  TRAFFIC_RED = 0,
  TRAFFIC_AMBER,
  TRAFFIC_GREEN
} TrafficColor;

typedef enum
{
  TRAFFIC_NORTH_SOUTH = 0,
  TRAFFIC_EAST_WEST
} TrafficRoad;

typedef struct
{
  uint8_t red_seconds;
  uint8_t amber_seconds;
  uint8_t green_seconds;
} TrafficTiming;

void traffic_light_init(void);
void traffic_light_all_off(void);
void traffic_light_set_road(TrafficRoad road, TrafficColor color);
void traffic_light_set_blink(TrafficColor color, bool visible);
void traffic_light_display_times(uint8_t north_south, uint8_t east_west);
void traffic_light_display_setting(uint8_t mode, uint8_t value);
void traffic_light_refresh_10ms(void);

#endif /* TRAFFIC_LIGHT_H */
