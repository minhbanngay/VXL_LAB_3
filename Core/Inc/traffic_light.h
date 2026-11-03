#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "global.h"

#include <stdbool.h>
#include <stdint.h>

void traffic_light_init(void);
void traffic_light_show_automatic(TrafficColor north_south_color,
                                  TrafficColor east_west_color,
                                  uint8_t north_south_time,
                                  uint8_t east_west_time);
void traffic_light_show_setting(TrafficColor color, uint8_t mode,
                                uint8_t value, bool visible);
void traffic_light_refresh_10ms(void);

#endif /* TRAFFIC_LIGHT_H */
