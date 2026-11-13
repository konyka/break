#pragma once

/* Scene-vertex to render-vertex conversion.
 *
 * The scene contract is 32 bytes (pos3 + normal3 + uv2) while the renderer's
 * MeshVertex is 36 (the same fields plus a material index). The conversion is
 * pure and lives in its own translation unit so it can be unit-tested without
 * a device, and so the stride rule has one owner. */

#include <core/types.h>
#include <renderer/mesh_stage.h>

bool core_app_mesh_convert_vertices(const u8 *vertices, u32 vertex_count,
                                    MeshVertex *out, u32 capacity);
