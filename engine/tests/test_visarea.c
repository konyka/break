#include "test_framework.h"
#include <renderer/visarea.h>

TEST(visarea_portals_and_cap) {
    u32 room_a[] = {1};
    u32 room_b[] = {2};
    u32 room_c[] = {3};
    u32 outdoor[] = {9};
    VisRoom rooms[3];
    memset(rooms, 0, sizeof(rooms));
    rooms[0].center = vec3(0, 0, 0);
    rooms[0].half_extent = vec3(2, 2, 2);
    rooms[0].object_ids = room_a;
    rooms[0].object_count = 1;
    rooms[1].center = vec3(0, 0, 6);
    rooms[1].half_extent = vec3(2, 2, 2);
    rooms[1].object_ids = room_b;
    rooms[1].object_count = 1;
    rooms[2].center = vec3(0, 0, -6);
    rooms[2].half_extent = vec3(2, 2, 2);
    rooms[2].object_ids = room_c;
    rooms[2].object_count = 1;

    VisQuery query;
    memset(&query, 0, sizeof(query));
    query.rooms = rooms;
    query.room_count = 1;
    query.camera = vec3(0, 0, 0);
    query.camera_forward = vec3(0, 0, 1);
    query.outdoor_ids = outdoor;
    query.outdoor_count = 1;
    u32 ids[8];
    u32 dropped = 0;
    memset(ids, 0xFF, sizeof(ids));
    u32 n = visarea_visible(&query, ids, 8, &dropped);
    ASSERT_EQ(n, 2u);
    ASSERT_EQ(dropped, 0u);
    ASSERT_TRUE((ids[0] == 9 && ids[1] == 1) || (ids[0] == 1 && ids[1] == 9));

    rooms[0].portal_count = 2;
    rooms[0].portals[0].center = vec3(0, 0, 1.5f);
    rooms[0].portals[0].half_extent = vec3(1, 1, 0.5f);
    rooms[0].portals[0].neighbor_room = 1;
    rooms[0].portals[1].center = vec3(0, 0, -1.5f);
    rooms[0].portals[1].half_extent = vec3(1, 1, 0.5f);
    rooms[0].portals[1].neighbor_room = 2;
    query.room_count = 3;
    n = visarea_visible(&query, ids, 8, &dropped);
    bool saw_b = false, saw_c = false, saw_out = false;
    for (u32 i = 0; i < n; i++) {
        if (ids[i] == 2) saw_b = true;
        if (ids[i] == 3) saw_c = true;
        if (ids[i] == 9) saw_out = true;
    }
    ASSERT_TRUE(saw_b);
    ASSERT_FALSE(saw_c);
    ASSERT_TRUE(saw_out);

    ids[1] = 77;
    n = visarea_visible(&query, ids, 1, &dropped);
    ASSERT_EQ(n, 1u);
    ASSERT_TRUE(dropped > 0u);
    ASSERT_EQ(ids[1], 77u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(visarea_portals_and_cap);
TEST_MAIN_END()
