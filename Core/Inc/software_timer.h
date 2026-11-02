#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#include <stdbool.h>
#include <stdint.h>

#define SOFTWARE_TIMER_COUNT 8U

void software_timer_init(void);
void software_timer_set(uint8_t timer_id, uint32_t duration_ms);
void software_timer_cancel(uint8_t timer_id);
void software_timer_tick(uint32_t elapsed_ms);
bool software_timer_expired(uint8_t timer_id);
bool software_timer_is_running(uint8_t timer_id);

#endif /* SOFTWARE_TIMER_H */
