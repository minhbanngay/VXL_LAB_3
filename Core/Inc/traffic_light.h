#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "global.h"

void traffic_light_init(void);
void traffic_light_show(TrafficColor north_south_color,
                        TrafficColor east_west_color);

#endif /* TRAFFIC_LIGHT_H */
