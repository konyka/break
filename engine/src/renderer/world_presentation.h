#pragma once
#include <renderer/lod.h>
#include <renderer/mesh_gpu.h>
#include <renderer/vegetation.h>
#include <renderer/visarea.h>
#include <renderer/world_stream_world.h>

#define WORLD_PRESENT_MAX_OBJECTS 512u
#define WORLD_PRESENT_MAX_INSTANCES 1024u
#define WORLD_PRESENT_MAX_PROTOTYPES 8u
#define WORLD_PRESENT_MAX_LODS 4u
#define WORLD_PRESENT_MAX_BATCHES (WORLD_PRESENT_MAX_PROTOTYPES * WORLD_PRESENT_MAX_LODS)

typedef enum WorldPresentationStatus {
    WORLD_PRESENTATION_OK = 0,
    WORLD_PRESENTATION_INVALID,
    WORLD_PRESENTATION_OVERLOAD
} WorldPresentationStatus;

typedef struct WorldObject {
    u32 id;
    MeshGpu gpu;
    MeshDrawDesc draw;
    MeshMaterial material;
    bool stream;
} WorldObject;

typedef struct WorldVegetationPrototype {
    MeshGpu gpu[WORLD_PRESENT_MAX_LODS];
    MeshDrawDesc draws[WORLD_PRESENT_MAX_LODS];
    f32 errors[WORLD_PRESENT_MAX_LODS];
    u32 lod_count;
    f32 bounding_radius;
    MeshMaterial material;
} WorldVegetationPrototype;

typedef struct WorldPresentationInput {
    u64 frame_id;
    Mat4 view;
    Mat4 projection;
    Vec3 camera;
    f32 fov;
    f32 screen_height;
    f32 pixel_error;
    TimeOfDayLighting lighting;
    const WorldObject *objects;
    u32 object_count;
    const VisQuery *visibility;
    const VegetationBuild *vegetation;
    const WorldVegetationPrototype *prototypes;
    u32 prototype_count;
    LodInstanceState *lod_state;
} WorldPresentationInput;

typedef struct WorldDrawSnapshot {
    u32 object_id;
    MeshGpu gpu;
    MeshDrawDesc draw;
    MeshMaterial material;
    bool stream;
} WorldDrawSnapshot;

typedef struct WorldInstanceSnapshot {
    Mat4 model;
} WorldInstanceSnapshot;

typedef struct WorldInstanceBatch {
    u32 prototype;
    u32 lod;
    u32 first;
    u32 count;
} WorldInstanceBatch;

typedef struct WorldFrameSnapshot {
    u64 frame_id;
    Mat4 view;
    Mat4 projection;
    Vec3 camera;
    TimeOfDayLighting lighting;
    WorldVegetationPrototype prototypes[WORLD_PRESENT_MAX_PROTOTYPES];
    u32 prototype_count;
    WorldDrawSnapshot draws[WORLD_PRESENT_MAX_OBJECTS];
    u32 draw_count;
    WorldInstanceSnapshot instances[WORLD_PRESENT_MAX_INSTANCES];
    u32 instance_count;
    WorldInstanceBatch batches[WORLD_PRESENT_MAX_BATCHES];
    u32 batch_count;
} WorldFrameSnapshot;

typedef struct WorldPresenter {
    MeshPipeline object_pipeline;
    MeshPipeline vegetation_pipeline;
    RHITexture white;
    RHISampler sampler;
    RHIBuffer instances;
    bool ready;
} WorldPresenter;

typedef struct WorldSubmitStats {
    u32 object_draws;
    u32 stream_draws;
    u32 instance_batches;
    u32 instance_count;
} WorldSubmitStats;

/* RenderThread only. Creation is transactional; submitted snapshots and their
 * referenced GPU resources must remain alive for the whole submission. */
bool world_presenter_create(RHIDevice *dev, WorldPresenter *out);
void world_presenter_destroy(RHIDevice *dev, WorldPresenter *presenter);
WorldPresentationStatus world_presenter_submit(RHICmdBuffer *cmd,
                                                WorldPresenter *presenter,
                                                const WorldFrameSnapshot *snapshot,
                                                WorldSubmitStats *out_stats);

/* GameThread only. The output and LOD state are unchanged on failure. A
 * successful snapshot owns its POD storage and contains no input pointers. */
WorldPresentationStatus world_presentation_snapshot(const WorldPresentationInput *input,
                                                     WorldFrameSnapshot *out);

/* Migrate a V1 stream tile and bake its world translation before upload. */
bool world_presentation_stream_mesh(const StreamTileData *tile, Vec3 translation,
                                    MeshBuffer *out);
