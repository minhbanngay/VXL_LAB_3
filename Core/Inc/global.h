/* Application structure adapted from:
 * https://github.com/manhphamduy13/MicroController_Lab3
 */
#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "buttons.h"
#include "display.h"
#include "traffic_light.h"
#include <stdint.h>

#define INIT                     0

#define AUTO_RED_GREEN           1
#define AUTO_RED_AMBER           2
#define AUTO_GREEN_RED           3
#define AUTO_AMBER_RED           4

#define SET_RED                  12
#define SET_AMBER                13
#define SET_GREEN                14

#define MANUAL_RED_GREEN         21
#define MANUAL_RED_AMBER         22
#define MANUAL_GREEN_RED         23
#define MANUAL_AMBER_RED         24

extern int status;

extern int time_red;
extern int time_amber;
extern int time_green;

extern int countA;
extern int countB;

extern int temp_red;
extern int temp_amber;
extern int temp_green;

#endif /* INC_GLOBAL_H_ */
