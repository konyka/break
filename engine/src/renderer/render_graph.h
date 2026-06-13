#pragma once
#include "../core/types.h"
#include "../rhi/rhi.h"

/* ---- Forward declarations ---- */
typedef struct RenderGraph RenderGraph;
typedef struct RGPass      RGPass;
typedef u32                RGResource; /* opaque resource handle (index) */

#define RG_INVALID_RESOURCE 0xFFFFFFFFu
#define RG_MAX_PASSES       64u
#define RG_MAX_RESOURCES    128u
#define RG_MAX_PASS_DEPS    16u

/* ---- Pass type ---- */
typedef enum {
    RG_PASS_GRAPHICS,
    RG_PASS_COMPUTE,
    RG_PASS_TRANSFER
} RGPassType;

/* ---- Resource usage / access intent ---- */
typedef enum {
    RG_USAGE_COLOR_ATTACHMENT,
    RG_USAGE_DEPTH_ATTACHMENT,
    RG_USAGE_SHADER_READ,
    RG_USAGE_SHADER_WRITE,
    RG_USAGE_TRANSFER_SRC,
    RG_USAGE_TRANSFER_DST,
    RG_USAGE_PRESENT
} RGResourceUsage;

/* ---- Resource descriptors ---- */
typedef struct {
    u32         width;
    u32         height;
    u32         format;     /* RHIFormat enum value (cast at allocation) */
    u32         mip_levels;
    bool        is_depth;
    const char *name;
} RGTextureDesc;

typedef struct {
    u32         size;
    const char *name;
} RGBufferDesc;

/* ---- Internal resource record ---- */
typedef struct {
    char            name[64];
    bool            is_imported;       /* true: external, lifetime owned by caller */
    bool            is_buffer;         /* true: buffer, false: texture */
    RGTextureDesc   tex_desc;
    RGBufferDesc    buf_desc;
    RHITexture      physical_texture;  /* populated after compile */
    RHIBuffer       physical_buffer;
    u32             first_write_pass;  /* RG_INVALID_RESOURCE if never written */
    u32             last_read_pass;    /* RG_INVALID_RESOURCE if never read */
    u32             ref_count;         /* total accesses (read+write) */
    bool            allocated;         /* whether physical resource is owned by RG */
} RGResourceInfo;

/* ---- Per-pass resource access record ---- */
typedef struct {
    RGResource      resource;
    RGResourceUsage usage;
    bool            is_write;
} RGPassAccess;

/* ---- Pass record ---- */
struct RGPass {
    char         name[64];
    RGPassType   type;

    /* Resource access lists */
    RGPassAccess reads[RG_MAX_PASS_DEPS];
    u32          read_count;
    RGPassAccess writes[RG_MAX_PASS_DEPS];
    u32          write_count;

    /* User execute callback */
    void        (*execute)(void *ctx, RGPass *pass);
    void         *ctx;

    /* Compiled dependency list (pass indices) */
    u32          dependencies[RG_MAX_PASS_DEPS];
    u32          dep_count;

    /* Schedule */
    u32          execution_order;
    bool         culled;

    /* Owning graph (back-pointer for accessor convenience) */
    RenderGraph *owner;
    u32          index;
};

/* ---- Pooled texture entry ---- */
typedef struct {
    RHITexture tex;
    u32        width;
    u32        height;
    u32        format;
    u32        mip_levels;
    bool       in_use;
} RGTexturePoolEntry;

/* ---- Render Graph state ---- */
struct RenderGraph {
    RGPass             passes[RG_MAX_PASSES];
    u32                pass_count;

    RGResourceInfo     resources[RG_MAX_RESOURCES];
    u32                resource_count;

    /* Compiled execution schedule */
    u32                execution_order[RG_MAX_PASSES];
    u32                execution_count;

    bool               compiled;

    /* Backing RHI device (set by rg_set_device); NULL means resources cannot
       be allocated automatically — only imported handles will be valid. */
    RHIDevice         *device;

    /* Lifetime-aliasing texture pool */
    RGTexturePoolEntry texture_pool[RG_MAX_RESOURCES];
    u32                pool_count;

    /* Stats */
    u32                culled_count;
};

/* ===================== API ===================== */

/* Lifetime */
RenderGraph *rg_create(void);
void         rg_destroy(RenderGraph *rg);
void         rg_reset(RenderGraph *rg);
void         rg_set_device(RenderGraph *rg, RHIDevice *dev);

/* Pass declaration */
RGPass    *rg_add_pass(RenderGraph *rg, const char *name, RGPassType type);
void       rg_pass_read(RGPass *pass, RGResource res, RGResourceUsage usage);
RGResource rg_pass_write(RGPass *pass, RGResource res, RGResourceUsage usage);
void       rg_pass_set_execute(RGPass *pass,
                               void (*fn)(void *ctx, RGPass *pass),
                               void *ctx);

/* Resource declaration */
RGResource rg_create_texture(RenderGraph *rg, const char *name,
                             const RGTextureDesc *desc);
RGResource rg_create_buffer(RenderGraph *rg, const char *name,
                            const RGBufferDesc *desc);
RGResource rg_import_texture(RenderGraph *rg, const char *name,
                             RHITexture external);
RGResource rg_import_buffer(RenderGraph *rg, const char *name,
                            RHIBuffer external);

/* Compile / execute */
bool rg_compile(RenderGraph *rg);
void rg_execute(RenderGraph *rg);

/* Resource lookup (for use inside execute callbacks) */
RHITexture rg_get_texture(RenderGraph *rg, RGResource handle);
RHIBuffer  rg_get_buffer(RenderGraph *rg, RGResource handle);

/* Stats */
u32 rg_pass_count(RenderGraph *rg);
u32 rg_resource_count(RenderGraph *rg);
u32 rg_culled_pass_count(RenderGraph *rg);
