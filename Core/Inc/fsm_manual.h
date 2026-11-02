#ifndef FSM_MANUAL_H
#define FSM_MANUAL_H

#include <stdint.h>

typedef enum
{
  MODE_AUTOMATIC = 1,
  MODE_SET_RED,
  MODE_SET_AMBER,
  MODE_SET_GREEN
} SystemMode;

void fsm_manual_init(void);
void fsm_manual_run(void);
SystemMode fsm_manual_get_mode(void);

#endif /* FSM_MANUAL_H */
