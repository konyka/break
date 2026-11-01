#include <renderer/mesh_gpu.h>

bool mesh_gpu_upload(RHIDevice *dev, const MeshBuffer *mesh, MeshGpu *out) {
    if (out) {
        out->vertex = RHI_HANDLE_NULL;
        out->index = RHI_HANDLE_NULL;
    }
    if (!dev || !mesh || !out || mesh->count == 0u) return false;
    RHIBufferDesc vertex_desc;
    if (!mesh_buffer_upload_desc(mesh, &vertex_desc)) return false;
    if (!rhi_buffer_desc_validate(&vertex_desc)) return false;
    out->vertex = rhi_buffer_create(dev, &vertex_desc);
    if (!rhi_handle_valid(out->vertex)) {
        out->vertex = RHI_HANDLE_NULL;
        return false;
    }
    if (mesh->index_count == 0u) return true;
    RHIBufferDesc index_desc;
    if (!mesh_buffer_index_desc(mesh, &index_desc) || !rhi_buffer_desc_validate(&index_desc)) {
        rhi_buffer_destroy(dev, out->vertex);
        out->vertex = RHI_HANDLE_NULL;
        return false;
    }
    out->index = rhi_buffer_create(dev, &index_desc);
    if (!rhi_handle_valid(out->index)) {
        rhi_buffer_destroy(dev, out->vertex);
        out->vertex = RHI_HANDLE_NULL;
        out->index = RHI_HANDLE_NULL;
        return false;
    }
    return true;
}

void mesh_gpu_destroy(RHIDevice *dev, MeshGpu *gpu) {
    if (!dev || !gpu) return;
    if (rhi_handle_valid(gpu->index)) rhi_buffer_destroy(dev, gpu->index);
    if (rhi_handle_valid(gpu->vertex)) rhi_buffer_destroy(dev, gpu->vertex);
    gpu->vertex = RHI_HANDLE_NULL;
    gpu->index = RHI_HANDLE_NULL;
}

bool mesh_gpu_draw(RHICmdBuffer *cmd, const MeshBuffer *mesh, const MeshGpu *gpu) {
    if (!cmd || !mesh || !gpu || mesh->count == 0u || !rhi_handle_valid(gpu->vertex)) return false;
    rhi_cmd_bind_vertex_buffer(cmd, gpu->vertex, 0);
    if (mesh->index_count > 0u && rhi_handle_valid(gpu->index)) {
        rhi_cmd_bind_index_buffer(cmd, gpu->index, 0, true);
        rhi_cmd_draw_indexed(cmd, mesh->index_count, 1u);
    } else {
        rhi_cmd_draw(cmd, mesh->count, 1u);
    }
    return true;
}
