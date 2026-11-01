#include <animation/skeleton.h>
#include <string.h>

static bool copy_socket_name(const char *src, char *dst) {
    if (!src || src[0] == '\0') {
        return false;
    }
    u32 n = 0;
    while (src[n] != '\0') {
        if (n >= 31u) {
            return false;
        }
        n++;
    }
    memcpy(dst, src, n);
    dst[n] = '\0';
    return true;
}

static Vec3 transform_point(const Mat4 *m, Vec3 p) {
    return vec3(m->e[0][0] * p.e[0] + m->e[1][0] * p.e[1] + m->e[2][0] * p.e[2] + m->e[3][0],
                m->e[0][1] * p.e[0] + m->e[1][1] * p.e[1] + m->e[2][1] * p.e[2] + m->e[3][1],
                m->e[0][2] * p.e[0] + m->e[1][2] * p.e[1] + m->e[2][2] * p.e[2] + m->e[3][2]);
}

bool skeleton_socket_set(Skeleton *sk, const char *name, u32 joint, Vec3 local_offset) {
    if (!sk || joint >= sk->joint_count || joint >= SKELETON_MAX_JOINTS) {
        return false;
    }
    char stored[32];
    if (!copy_socket_name(name, stored)) {
        return false;
    }
    for (u32 i = 0; i < sk->socket_count; i++) {
        if (sk->sockets[i].used && strcmp(sk->sockets[i].name, stored) == 0) {
            sk->sockets[i].joint = joint;
            sk->sockets[i].local_offset = local_offset;
            return true;
        }
    }
    if (sk->socket_count >= SKELETON_MAX_SOCKETS) {
        return false;
    }
    SkeletonSocket *socket = &sk->sockets[sk->socket_count++];
    memset(socket, 0, sizeof(*socket));
    memcpy(socket->name, stored, sizeof(stored));
    socket->joint = joint;
    socket->local_offset = local_offset;
    socket->used = true;
    return true;
}

bool skeleton_socket_get(const Skeleton *sk, const char *name, Vec3 *out_world) {
    if (!sk || !name || !out_world) {
        return false;
    }
    for (u32 i = 0; i < sk->socket_count; i++) {
        if (!sk->sockets[i].used || strcmp(sk->sockets[i].name, name) != 0) {
            continue;
        }
        if (sk->sockets[i].joint >= SKELETON_MAX_JOINTS) {
            return false;
        }
        *out_world = transform_point(&sk->current_pose[sk->sockets[i].joint], sk->sockets[i].local_offset);
        return true;
    }
    return false;
}
