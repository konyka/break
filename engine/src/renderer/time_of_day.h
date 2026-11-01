#pragma once
#include <core/types.h>
#include <math/math.h>

typedef struct TimeOfDayLighting {
    Vec3 sun_dir;
    Vec3 sun_color;
    Vec3 ambient;
    f32 fog;
} TimeOfDayLighting;

/* Midnight ambient is (0.03, 0.03, 0.05). Noon puts the sun on +Y. */
void time_of_day_eval(f32 seconds, f32 day_length, TimeOfDayLighting *out);
