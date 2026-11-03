#include <ai/break_nav_internal.h>
#include <stdlib.h>

struct BreakNavWorkspacePool {
    BreakNavWorkspace *slots[BREAK_NAV_QUERY_POOL_CAPACITY];
    atomic_uint claims[BREAK_NAV_QUERY_POOL_CAPACITY];
};

BreakNavWorkspace *break_nav_workspace_create(u32 poly_count) {
    BreakNavWorkspace *workspace = (BreakNavWorkspace *)calloc(1, sizeof(BreakNavWorkspace));
    if (!workspace) {
        return NULL;
    }
    workspace->poly_count = poly_count;
    if (poly_count == 0) {
        return workspace;
    }
    workspace->gscore = (f32 *)malloc(sizeof(f32) * poly_count);
    workspace->fscore = (f32 *)malloc(sizeof(f32) * poly_count);
    workspace->came = (u32 *)malloc(sizeof(u32) * poly_count);
    workspace->closed = (u8 *)malloc(poly_count);
    workspace->heap = (u32 *)malloc(sizeof(u32) * poly_count);
    workspace->chain = (u32 *)malloc(sizeof(u32) * poly_count);
    if (!workspace->gscore || !workspace->fscore || !workspace->came ||
        !workspace->closed || !workspace->heap || !workspace->chain) {
        break_nav_workspace_destroy(workspace);
        return NULL;
    }
    return workspace;
}

void break_nav_workspace_destroy(BreakNavWorkspace *workspace) {
    if (!workspace) {
        return;
    }
    free(workspace->gscore);
    free(workspace->fscore);
    free(workspace->came);
    free(workspace->closed);
    free(workspace->heap);
    free(workspace->chain);
    free(workspace);
}

BreakNavWorkspacePool *break_nav_workspace_pool_create(u32 poly_count) {
    BreakNavWorkspacePool *pool = (BreakNavWorkspacePool *)calloc(1, sizeof(BreakNavWorkspacePool));
    if (!pool) {
        return NULL;
    }
    for (u32 i = 0; i < BREAK_NAV_QUERY_POOL_CAPACITY; i++) {
        atomic_init(&pool->claims[i], 0u);
        pool->slots[i] = break_nav_workspace_create(poly_count);
        if (!pool->slots[i]) {
            break_nav_workspace_pool_destroy(pool);
            return NULL;
        }
    }
    return pool;
}

void break_nav_workspace_pool_destroy(BreakNavWorkspacePool *pool) {
    if (!pool) {
        return;
    }
    for (u32 i = 0; i < BREAK_NAV_QUERY_POOL_CAPACITY; i++) {
        break_nav_workspace_destroy(pool->slots[i]);
    }
    free(pool);
}

BreakNavWorkspace *break_nav_workspace_pool_acquire(const BreakNavMesh *mesh, u32 *out_slot) {
    if (!mesh || !out_slot || !mesh->workspace_pool) {
        return NULL;
    }
    BreakNavWorkspacePool *pool = mesh->workspace_pool;
    for (u32 i = 0; i < BREAK_NAV_QUERY_POOL_CAPACITY; i++) {
        if (atomic_exchange_explicit(&pool->claims[i], 1u, memory_order_acquire) == 0u) {
            *out_slot = i;
            return pool->slots[i];
        }
    }
    return NULL;
}

void break_nav_workspace_pool_release(const BreakNavMesh *mesh, u32 slot) {
    if (!mesh || !mesh->workspace_pool || slot >= BREAK_NAV_QUERY_POOL_CAPACITY) {
        return;
    }
    atomic_store_explicit(&mesh->workspace_pool->claims[slot], 0u, memory_order_release);
}
