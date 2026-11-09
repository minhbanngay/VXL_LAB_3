#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "main.h"

typedef enum
{
    COLOR_OFF,
    COLOR_RED,
    COLOR_AMBER,
    COLOR_GREEN
} TrafficColor;

void Traffic_Init(void);
void Traffic_Show(TrafficColor a, TrafficColor b);

#endif /* TRAFFIC_LIGHT_H */
