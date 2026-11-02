#ifndef FSM_AUTOMATIC_H
#define FSM_AUTOMATIC_H

#include "traffic_light.h"

void fsm_automatic_init(const TrafficTiming *timing);
void fsm_automatic_run(void);

#endif /* FSM_AUTOMATIC_H */
