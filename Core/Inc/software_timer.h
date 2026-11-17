#ifndef SOFTWARE_TIMER_H_
#define SOFTWARE_TIMER_H_

#define TIMER_CYCLE    10

extern volatile int timer_flag[3];
extern volatile int timer_counter[3];

void setTimer(int index, int duration);
void timerRun(void);

#endif /* SOFTWARE_TIMER_H_ */
