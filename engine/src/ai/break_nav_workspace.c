#include <ai/break_nav_internal.h>
#include <stdlib.h>

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
