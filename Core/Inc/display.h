#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void display_init(void);
void display_set(uint8_t left, uint8_t right);
void display_refresh_10ms(void);

#endif /* DISPLAY_H */

