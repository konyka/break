#pragma once
#include <renderer/mesh_buffer.h>

typedef struct MeshGpu {
    RHIBuffer vertex;
    RHIBuffer index;
} MeshGpu;

typedef struct MeshPipeline {
    RHIShader vert;
    RHIShader frag;
    RHIPipeline pipeline;
} MeshPipeline;

/* Create the vertex buffer and, when the mesh has indices, the index buffer.
 * A null device or a rejected create leaves both handles null and returns false. */
bool mesh_gpu_upload(RHIDevice *dev, const MeshBuffer *mesh, MeshGpu *out);
void mesh_gpu_destroy(RHIDevice *dev, MeshGpu *gpu);
/* Position, normal, and material shader for a 28-byte mesh vertex. */
bool mesh_pipeline_create(RHIDevice *dev, MeshPipeline *out);
void mesh_pipeline_destroy(RHIDevice *dev, MeshPipeline *pipe);
/* Bind and draw. Indexed when both the mesh and the gpu index buffer are live. */
bool mesh_gpu_draw(RHICmdBuffer *cmd, const MeshBuffer *mesh, const MeshGpu *gpu);
/* Bind `pipe` first, then draw. A null pipeline is refused. */
bool mesh_gpu_draw_with_pipeline(RHICmdBuffer *cmd, const MeshPipeline *pipe,
                                 const MeshBuffer *mesh, const MeshGpu *gpu);
