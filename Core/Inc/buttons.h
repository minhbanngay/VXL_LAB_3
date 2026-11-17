#ifndef BUTTONS_H
#define BUTTONS_H

#include "main.h"
#include <stdint.h>

#define BUTTON_1 0
#define BUTTON_2 1
#define BUTTON_3 2

void Buttons_Init(void);
void Buttons_Tick10ms(void);
uint8_t Buttons_GetEvents(void);

int isButtonPressed(uint8_t index);
int isButton1Pressed(void);
int isButton2Pressed(void);
int isButton3Pressed(void);

void getKeyInput(void);

#endif /* BUTTONS_H */
