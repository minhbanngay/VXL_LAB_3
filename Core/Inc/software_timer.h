#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#define TIMER_CYCLE 10
#define SOFTWARE_TIMER_COUNT 2

extern volatile int timer_counter[SOFTWARE_TIMER_COUNT];
extern volatile int timer_flag[SOFTWARE_TIMER_COUNT];

void setTimer(int index, int duration);
void timerRun(void);

#endif /* SOFTWARE_TIMER_H */
