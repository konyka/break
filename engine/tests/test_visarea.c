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

static void make_room(VisRoom *room, Vec3 center, u32 *ids, u32 count) {
    memset(room, 0, sizeof(*room));
    room->center = center;
    room->half_extent = vec3(2, 2, 2);
    room->object_ids = ids;
    room->object_count = count;
}

static void add_portal(VisRoom *room, Vec3 center, u32 neighbor) {
    VisPortal *p = &room->portals[room->portal_count++];
    p->center = center;
    p->half_extent = vec3(1, 1, 0.5f);
    p->neighbor_room = neighbor;
}

/* A camera outside every room sees only the outdoor objects. */
TEST(visarea_outside_rooms_sees_outdoor_only) {
    u32 a[] = {1, 2};
    u32 outdoor[] = {9, 10};
    VisRoom room;
    make_room(&room, vec3(0, 0, 0), a, 2);
    VisQuery q;
    memset(&q, 0, sizeof(q));
    q.rooms = &room;
    q.room_count = 1;
    q.camera = vec3(10, 0, 0);
    q.camera_forward = vec3(-1, 0, 0);
    q.outdoor_ids = outdoor;
    q.outdoor_count = 2;
    u32 ids[8];
    u32 dropped = 1;
    ASSERT_EQ(visarea_visible(&q, ids, 8, &dropped), 2u);
    ASSERT_EQ(dropped, 0u);
    ASSERT_EQ(ids[0], 9u);
    ASSERT_EQ(ids[1], 10u);
}

/* Visibility goes through one portal only: a room behind the neighbour is
 * not visible, and a portal to a room listed twice adds it once. Portals
 * to invalid rooms are skipped. */
TEST(visarea_one_hop_dedup_and_bad_neighbours) {
    u32 a[] = {1}, b[] = {2}, c[] = {3};
    VisRoom rooms[3];
    make_room(&rooms[0], vec3(0, 0, 0), a, 1);
    make_room(&rooms[1], vec3(0, 0, 6), b, 1);
    make_room(&rooms[2], vec3(0, 0, 12), c, 1);
    add_portal(&rooms[0], vec3(0, 0, 1.5f), 1);
    add_portal(&rooms[0], vec3(0, 0, 1.6f), 1);
    add_portal(&rooms[0], vec3(0, 0, 1.7f), UINT32_MAX);
    add_portal(&rooms[0], vec3(0, 0, 1.8f), 7);
    add_portal(&rooms[1], vec3(0, 0, 7.5f), 2);
    VisQuery q;
    memset(&q, 0, sizeof(q));
    q.rooms = rooms;
    q.room_count = 3;
    q.camera = vec3(0, 0, 0);
    q.camera_forward = vec3(0, 0, 1);
    u32 ids[8];
    u32 dropped = 0;
    ASSERT_EQ(visarea_visible(&q, ids, 8, &dropped), 2u);
    ASSERT_EQ(ids[0], 1u);
    ASSERT_EQ(ids[1], 2u);
    ASSERT_EQ(dropped, 0u);
}

/* A portal behind the camera is culled; turning around shows it. */
TEST(visarea_culls_portals_behind_the_camera) {
    u32 a[] = {1}, b[] = {2};
    VisRoom rooms[2];
    make_room(&rooms[0], vec3(0, 0, 0), a, 1);
    make_room(&rooms[1], vec3(0, 0, -6), b, 1);
    add_portal(&rooms[0], vec3(0, 0, -1.5f), 1);
    VisQuery q;
    memset(&q, 0, sizeof(q));
    q.rooms = rooms;
    q.room_count = 2;
    q.camera = vec3(0, 0, 0);
    q.camera_forward = vec3(0, 0, 1);
    u32 ids[4];
    u32 dropped = 0;
    ASSERT_EQ(visarea_visible(&q, ids, 4, &dropped), 1u);
    q.camera_forward = vec3(0, 0, -1);
    ASSERT_EQ(visarea_visible(&q, ids, 4, &dropped), 2u);
    ASSERT_EQ(ids[1], 2u);
}

/* Too many rooms or objects reject the query and count every object as
 * dropped; a NULL room array with a non-zero count is rejected without
 * reading it (it used to be read while summing the drop count); a NULL
 * drop counter returns nothing. */
TEST(visarea_rejects_oversized_queries) {
    u32 a[] = {1};
    u32 outdoor[] = {9};
    VisRoom room;
    make_room(&room, vec3(0, 0, 0), a, 1);
    VisQuery q;
    memset(&q, 0, sizeof(q));
    q.rooms = &room;
    q.room_count = 1;
    q.outdoor_ids = outdoor;
    q.outdoor_count = 1;
    u32 ids[4];
    u32 dropped = 0;
    room.object_count = VISAREA_MAX_OBJECTS + 1u;
    ASSERT_EQ(visarea_visible(&q, ids, 4, &dropped), 0u);
    ASSERT_EQ(dropped, VISAREA_MAX_OBJECTS + 2u);
    room.object_count = 1;
    q.rooms = NULL;
    ASSERT_EQ(visarea_visible(&q, ids, 4, &dropped), 0u);
    ASSERT_EQ(dropped, 1u);
    q.rooms = &room;
    ASSERT_EQ(visarea_visible(&q, ids, 4, NULL), 0u);
    ASSERT_EQ(visarea_visible(NULL, ids, 4, &dropped), 0u);
    ASSERT_EQ(dropped, 0u);
    ASSERT_EQ(visarea_visible(&q, NULL, 0, &dropped), 0u);
    ASSERT_EQ(dropped, 2u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(visarea_portals_and_cap);
    RUN_TEST(visarea_outside_rooms_sees_outdoor_only);
    RUN_TEST(visarea_one_hop_dedup_and_bad_neighbours);
    RUN_TEST(visarea_culls_portals_behind_the_camera);
    RUN_TEST(visarea_rejects_oversized_queries);
TEST_MAIN_END()
