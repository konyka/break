#include <ai/break_nav_internal.h>
#include <math.h>
#include <string.h>

static f32 dist_xz(Vec3 a, Vec3 b) {
    f32 dx = a.e[0] - b.e[0];
    f32 dz = a.e[2] - b.e[2];
    return sqrtf(dx * dx + dz * dz);
}

static void heap_push(u32 *heap, f32 *fscore, u32 *heap_n, u32 poly) {
    u32 i = (*heap_n)++;
    heap[i] = poly;
    while (i > 0) {
        u32 parent = (i - 1u) / 2u;
        if (fscore[heap[parent]] <= fscore[heap[i]]) {
            break;
        }
        u32 tmp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = tmp;
        i = parent;
    }
}

static u32 heap_pop(u32 *heap, f32 *fscore, u32 *heap_n) {
    u32 root = heap[0];
    u32 n = --(*heap_n);
    if (n == 0) {
        return root;
    }
    heap[0] = heap[n];
    u32 i = 0;
    for (;;) {
        u32 left = i * 2u + 1u;
        if (left >= n) {
            break;
        }
        u32 best = left;
        u32 right = left + 1u;
        if (right < n && fscore[heap[right]] < fscore[heap[left]]) {
            best = right;
        }
        if (fscore[heap[i]] <= fscore[heap[best]]) {
            break;
        }
        u32 tmp = heap[i];
        heap[i] = heap[best];
        heap[best] = tmp;
        i = best;
    }
    return root;
}

BreakNavError break_nav_find_path_workspace(const BreakNavMesh *mesh,
                                            BreakNavWorkspace *workspace,
                                            const u32 *blocked_counts,
                                            Vec3 start, Vec3 end,
                                            BreakNavPath *out) {
    if (!mesh || !workspace || !out || workspace->poly_count != mesh->poly_count) {
        return BREAK_NAV_INVALID;
    }
    u32 start_poly = 0;
    u32 end_poly = 0;
    if (!break_nav_locate(mesh, start, &start_poly) || !break_nav_locate(mesh, end, &end_poly)) {
        return BREAK_NAV_FAILED;
    }
    if (mesh->polys[start_poly].component != mesh->polys[end_poly].component ||
        (blocked_counts && (blocked_counts[start_poly] != 0 || blocked_counts[end_poly] != 0))) {
        return BREAK_NAV_FAILED;
    }
    u32 npoly = mesh->poly_count;
    f32 *gscore = workspace->gscore;
    f32 *fscore = workspace->fscore;
    u32 *came = workspace->came;
    u8 *closed = workspace->closed;
    u32 *heap = workspace->heap;
    u32 *chain = workspace->chain;
    for (u32 i = 0; i < npoly; i++) {
        gscore[i] = 1.0e30f;
        fscore[i] = 1.0e30f;
        came[i] = UINT32_MAX;
        closed[i] = 0;
    }
    gscore[start_poly] = 0.0f;
    fscore[start_poly] = dist_xz(mesh->polys[start_poly].center, mesh->polys[end_poly].center);
    u32 heap_n = 0;
    heap_push(heap, fscore, &heap_n, start_poly);
    bool found = false;
    while (heap_n > 0) {
        u32 cur = heap_pop(heap, fscore, &heap_n);
        if (closed[cur]) {
            continue;
        }
        closed[cur] = 1;
        if (cur == end_poly) {
            found = true;
            break;
        }
        for (u32 i = 0; i < mesh->polys[cur].neighbor_count; i++) {
            u32 nb = mesh->polys[cur].neighbors[i];
            if (closed[nb] || (blocked_counts && blocked_counts[nb] != 0)) {
                continue;
            }
            f32 step = dist_xz(mesh->polys[cur].center, mesh->polys[nb].center);
            f32 tentative = gscore[cur] + step;
            if (tentative < gscore[nb]) {
                came[nb] = cur;
                gscore[nb] = tentative;
                fscore[nb] = tentative + dist_xz(mesh->polys[nb].center, mesh->polys[end_poly].center);
                if (heap_n >= npoly) {
                    return BREAK_NAV_OVERLOAD;
                }
                heap_push(heap, fscore, &heap_n, nb);
            }
        }
    }
    if (!found) {
        return BREAK_NAV_FAILED;
    }
    u32 chain_n = 0;
    for (u32 cur = end_poly; cur != UINT32_MAX; cur = came[cur]) {
        if (chain_n >= npoly) {
            break;
        }
        chain[chain_n++] = cur;
        if (cur == start_poly) {
            break;
        }
    }
    Vec3 points[BREAK_NAV_MAX_POINTS];
    u32 count = 0;
    points[count++] = start;
    for (u32 i = chain_n; i-- > 0;) {
        if (count >= BREAK_NAV_MAX_POINTS) {
            return BREAK_NAV_OVERLOAD;
        }
        Vec3 center = mesh->polys[chain[i]].center;
        bool corner = true;
        if (count >= 2) {
            Vec3 prev = points[count - 2];
            Vec3 last = points[count - 1];
            f32 dx1 = last.e[0] - prev.e[0];
            f32 dz1 = last.e[2] - prev.e[2];
            f32 dx2 = center.e[0] - last.e[0];
            f32 dz2 = center.e[2] - last.e[2];
            f32 cross = dx1 * dz2 - dz1 * dx2;
            if (cross < 1.0e-3f && cross > -1.0e-3f) {
                corner = false;
            }
        }
        if (!corner) {
            points[count - 1] = center;
        } else if (!(count == 1 && chain[i] == start_poly)) {
            points[count++] = center;
        }
    }
    if (count >= BREAK_NAV_MAX_POINTS) {
        return BREAK_NAV_OVERLOAD;
    }
    points[count++] = end;
    memcpy(out->points, points, sizeof(Vec3) * count);
    out->count = count;
    return BREAK_NAV_OK;
}

BreakNavError break_nav_find_path(const BreakNavMesh *mesh, Vec3 start, Vec3 end, BreakNavPath *out) {
    if (!mesh) {
        return BREAK_NAV_INVALID;
    }
    return break_nav_find_path_workspace(mesh, mesh->workspace, NULL, start, end, out);
}
