#pragma once
#include <core/types.h>
#include <math/math.h>

#define VISAREA_MAX_ROOMS 128u
#define VISAREA_MAX_OBJECTS 512u

typedef struct VisPortal {
    Vec3 center;
    Vec3 half_extent;
    u32 neighbor_room; /* UINT32_MAX means outdoors */
} VisPortal;

typedef struct VisRoom {
    Vec3 center;
    Vec3 half_extent;
    VisPortal portals[8];
    u32 portal_count;
    const u32 *object_ids;
    u32 object_count;
} VisRoom;

typedef struct VisQuery {
    const VisRoom *rooms;
    u32 room_count;
    Vec3 camera;
    Vec3 camera_forward;
    const u32 *outdoor_ids;
    u32 outdoor_count;
} VisQuery;

u32 visarea_visible(const VisQuery *query, u32 *out_ids, u32 cap, u32 *dropped);
