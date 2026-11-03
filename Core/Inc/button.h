#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
  BUTTON_MODE = 0,
  BUTTON_MODIFY,
  BUTTON_SET,
  BUTTON_COUNT
} ButtonId;

void button_init(void);
void button_tick(void);
bool button_is_pressed(ButtonId button);
bool button_was_pressed(ButtonId button);
bool button_was_long_pressed(ButtonId button);

#endif /* BUTTON_H */
