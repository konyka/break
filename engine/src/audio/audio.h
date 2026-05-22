#pragma once
#include <core/types.h>
#include <math/math.h>

typedef struct AudioSource AudioSource;

typedef struct {
    void       *engine;
    AudioSource *sources;
    u32         source_count;
    u32         source_cap;
    Vec3        listener_pos;
    Vec3        listener_forward;
    Vec3        listener_up;
} AudioSystem;

AudioSystem *audio_system_create(void);
void         audio_system_destroy(AudioSystem *as);
void         audio_system_update(AudioSystem *as, Vec3 listener_pos, Vec3 forward, Vec3 up);

u32          audio_play(AudioSystem *as, const char *path, f32 volume, bool looping);
void         audio_play_3d(AudioSystem *as, const char *path, Vec3 position, f32 volume, bool looping);
void         audio_stop(AudioSystem *as, u32 source_id);
void         audio_set_listener(AudioSystem *as, Vec3 pos, Vec3 forward, Vec3 up);
