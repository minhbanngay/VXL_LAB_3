#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdbool.h>
#include <stdint.h>

#define SYSTEM_TICK_MS 10U
#define TRAFFIC_TIME_MIN_SECONDS 1U
#define TRAFFIC_TIME_MAX_SECONDS 99U

typedef enum
{
  MODE_AUTOMATIC = 1,
  MODE_SET_RED,
  MODE_SET_AMBER,
  MODE_SET_GREEN
} SystemMode;

typedef enum
{
  TRAFFIC_RED = 0,
  TRAFFIC_AMBER,
  TRAFFIC_GREEN
} TrafficColor;

typedef struct
{
  uint8_t red_seconds;
  uint8_t amber_seconds;
  uint8_t green_seconds;
} TrafficTiming;

void global_init(void);

SystemMode global_get_mode(void);
void global_set_mode(SystemMode mode);
void global_next_mode(void);

TrafficTiming global_get_timing(void);
uint8_t global_get_duration(TrafficColor color);
bool global_set_duration(TrafficColor color, uint8_t seconds);

#endif /* GLOBAL_H */
