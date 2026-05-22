#pragma once
#include <core/types.h>

void  time_init(void);
f64   time_seconds(void);
u64   time_microseconds(void);
f64   time_delta_since(u64 last_us);
void  time_sleep_us(u64 microseconds);
