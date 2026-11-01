#include <renderer/time_of_day.h>
#include <math.h>

void time_of_day_eval(f32 seconds, f32 day_length, TimeOfDayLighting *out) {
    if (!out) return;
    f32 len = day_length > 0.0f ? day_length : 1.0f;
    if (!isfinite(seconds)) seconds = 0.0f;
    f32 t = fmodf(seconds, len);
    if (t < 0.0f) t += len;
    f32 u = t / len;
    f32 phase = (u * 2.0f - 1.0f) * 3.14159265f;
    f32 y = cosf(phase);
    f32 x = sinf(phase);
    out->sun_dir = vec3(x, y, 0.0f);
    if (y > 0.0f) {
        out->sun_color = vec3(y, y, y);
        out->ambient = vec3(0.03f + 0.15f * y, 0.03f + 0.15f * y, 0.05f + 0.15f * y);
        out->fog = 0.35f - 0.15f * y;
    } else {
        out->sun_color = vec3(0, 0, 0);
        out->ambient = vec3(0.03f, 0.03f, 0.05f);
        out->fog = 0.35f;
    }
}
