#ifndef FSM_SETTING_H
#define FSM_SETTING_H

#include "traffic_light.h"

void fsm_setting_init(TrafficTiming *timing);
void fsm_setting_enter(TrafficColor color, uint8_t mode);
void fsm_setting_run(void);

#endif /* FSM_SETTING_H */
