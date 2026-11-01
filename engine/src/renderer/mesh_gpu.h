#pragma once
#include <renderer/mesh_buffer.h>

typedef struct MeshGpu {
    RHIBuffer vertex;
    RHIBuffer index;
} MeshGpu;

/* Create the vertex buffer and, when the mesh has indices, the index buffer.
 * A null device or a rejected create leaves both handles null and returns false. */
bool mesh_gpu_upload(RHIDevice *dev, const MeshBuffer *mesh, MeshGpu *out);
void mesh_gpu_destroy(RHIDevice *dev, MeshGpu *gpu);
/* Bind and draw. Indexed when both the mesh and the gpu index buffer are live. */
bool mesh_gpu_draw(RHICmdBuffer *cmd, const MeshBuffer *mesh, const MeshGpu *gpu);
