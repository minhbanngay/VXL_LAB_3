#ifndef FSM_SETTING_H
#define FSM_SETTING_H

#include "global.h"

void fsm_setting_init(void);
void fsm_setting_enter(TrafficColor color, uint8_t mode);
void fsm_setting_run(void);
void fsm_setting_exit(void);

#endif /* FSM_SETTING_H */
