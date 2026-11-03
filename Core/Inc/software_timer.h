#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#define TIMER_CYCLE 10

extern volatile int timer_flag;

void setTimer(int duration);
void timerRun(void);

#endif /* SOFTWARE_TIMER_H */
