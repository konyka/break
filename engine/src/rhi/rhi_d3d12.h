#ifndef RHI_D3D12_NATIVE_H
#define RHI_D3D12_NATIVE_H

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <rhi/rhi.h>

typedef enum RHI_D3D12CreateFailure {
    RHI_D3D12_FAIL_NONE = 0,
    RHI_D3D12_FAIL_ADAPTER,
    RHI_D3D12_FAIL_DEVICE,
    RHI_D3D12_FAIL_QUEUE,
    RHI_D3D12_FAIL_ALLOCATOR,
    RHI_D3D12_FAIL_COMMAND_LIST,
    RHI_D3D12_FAIL_DESCRIPTOR,
    RHI_D3D12_FAIL_FENCE,
    RHI_D3D12_FAIL_EVENT,
} RHI_D3D12CreateFailure;

/* Task 4 decision record: 3 back buffers. Under flip model
 * (DXGI_SWAP_EFFECT_FLIP_DISCARD) the present engine and the GPU may each
 * hold a frame; 3 buffers keep the CPU off the frame_fence wait. The
 * rhi_frame_index double-slot semantics are independent: they index the
 * per-frame command allocator ring (2 slots), decoupled from the swapchain
 * buffer count. */
#define RHI_D3D12_BACKBUFFER_COUNT 3u

/* Task 5 decision record: descriptor heap capacities. The shader-visible
 * CBV/SRV/UAV heap aligns with the RHI slot-table model (RHI_MAX_RESOURCES
 * 4096, rhi_backend_internal.h:8) so any live resource can hold a view;
 * RTV/DSV/sampler heaps track the FBO budget. The sampler heap stays far
 * below the D3D12 shader-visible sampler hard cap (2048).
 *
 * R638: DSV was 16 and RTV 64. Every offscreen FBO takes one of each (the
 * colour target an RTV, its depth a DSV), and the demo creates well over 16
 * -- post passes, the 1x1 luminance pair, TAA history, shadow atlas, point
 * shadow faces -- so the 17th and every later FBO failed and roughly a dozen
 * post subsystems disabled themselves ("FBO/sampler creation failed"). RTV
 * and DSV heaps are CPU-only (never shader-visible), a descriptor is a few
 * tens of bytes, and D3D12 has no practical cap on them, so both now match
 * the resource table: one per live resource can always get a view. */
#define RHI_D3D12_CBV_SRV_UAV_CAPACITY 4096u
#define RHI_D3D12_RTV_CAPACITY 1024u
#define RHI_D3D12_DSV_CAPACITY 1024u
#define RHI_D3D12_SAMPLER_CAPACITY 64u

/* Free-list descriptor allocator over one heap; slots retire through the
 * context fence (the descriptor_retire_fence pattern generalised per slot).
 * Task 7 (DXR) reuses this for SBT / AS-view descriptors. The heap object
 * is owned by the context; the allocator owns only the slot bookkeeping. */
typedef struct RHI_D3D12DescriptorAlloc {
    ID3D12DescriptorHeap *heap;
    UINT increment;
    UINT capacity;
    UINT *free_slots;      /* stack of slot indices */
    UINT free_count;
    UINT64 *slot_fence;    /* per-slot retire fence; 0 = not in flight */
} RHI_D3D12DescriptorAlloc;

typedef struct RHI_D3D12Swapchain {
    IDXGISwapChain4 *swapchain;
    ID3D12Resource *backbuffers[RHI_D3D12_BACKBUFFER_COUNT];
    UINT rtv_slots[RHI_D3D12_BACKBUFFER_COUNT]; /* rtv_alloc slots, owned
                                                 * for the swapchain lifetime */
    HWND hwnd;
    UINT width;
    UINT height;
    UINT current_index;
    UINT vsync;                 /* SyncInterval 0/1 */
    DXGI_FORMAT format;         /* DXGI_FORMAT_B8G8R8A8_UNORM */
    UINT flags;                 /* creation-time DXGI_SWAP_CHAIN_FLAG_*;
                                 * ResizeBuffers must restate them */
    HWND owned_hwnd;            /* fallback window owned by the device when the
                                 * caller's HWND is not a real window; only
                                 * reachable with BREAK_D3D12_TEST_FALLBACK_HWND=1
                                 * (contract tests); NULL in production */
} RHI_D3D12Swapchain;

typedef struct RHI_D3D12Context {
    IDXGIFactory6 *factory;
    IDXGIAdapter1 *adapter;
    ID3D12Device *device;
    ID3D12CommandQueue *direct_queue;   /* renamed from `queue` */
    ID3D12CommandQueue *compute_queue;
    ID3D12CommandQueue *copy_queue;
    ID3D12CommandAllocator *allocators[2];
    ID3D12GraphicsCommandList *command_lists[2];
    ID3D12DescriptorHeap *rtv_heap;
    ID3D12DescriptorHeap *dsv_heap;
    ID3D12DescriptorHeap *cbv_srv_uav_heap;
    ID3D12DescriptorHeap *sampler_heap;         /* shader-visible, Task 5 */
    ID3D12CommandAllocator *upload_allocator;   /* one-shot staging uploads */
    ID3D12GraphicsCommandList *upload_list;     /* (rhi.h:394-397 semantics) */
    ID3D12CommandSignature *draw_signature;     /* ExecuteIndirect, stride 16 */
    ID3D12CommandSignature *draw_indexed_signature; /* stride 20, gated by
                                                     * rhi_indirect_abi_valid */
    RHI_D3D12DescriptorAlloc rtv_alloc;
    RHI_D3D12DescriptorAlloc dsv_alloc;
    RHI_D3D12DescriptorAlloc cbv_srv_uav_alloc;
    RHI_D3D12DescriptorAlloc sampler_alloc;
    ID3D12Fence *fence;
    HANDLE fence_event;
    UINT64 frame_fence[2];              /* last submitted fence per slot */
    UINT frame_parity;                  /* rhi_frame_index slot source */
    UINT acquire_in_flight;             /* spec §4.3: one in-flight pair max */
    UINT frame_started;                 /* begin recorded, not yet submitted */
    UINT frame_submitted;               /* submitted, present allowed */
    UINT render_pass_active;            /* explicit begin/end nesting guard */
    UINT rtv_increment;
    UINT dsv_increment;
    UINT cbv_srv_uav_increment;
    UINT sampler_increment;
    D3D12_CPU_DESCRIPTOR_HANDLE bound_rtvs[5]; /* RHI_MRT_MAX_ATTACHMENTS */
    DXGI_FORMAT bound_rtv_formats[5];  /* R643: per-draw PSO variant key */
    ID3D12PipelineState *bound_pso;    /* R643: PSO last set on the list */
    /* R643: the graphics CBV last bound per register (bN) this frame, so a
     * pipeline change can re-apply it -- see rhi_cmd_bind_pipeline. A slot
     * counts only while cbv_frame equals debug_frame. */
    D3D12_GPU_DESCRIPTOR_HANDLE cbv_gpu[16];
    UINT64 cbv_frame[16];
    UINT bound_rtv_count;
    D3D12_CPU_DESCRIPTOR_HANDLE bound_dsv;
    UINT bound_dsv_valid;
    void *bound_pipeline;       /* RHI_D3D12Pipeline*, .c-internal */
    UINT bound_pipeline_compute;
    UINT frame_srv_slots[RHI_D3D12_CBV_SRV_UAV_CAPACITY];
    UINT frame_srv_count;
    /* Bumped once per frame in rhi_frame_begin; per-frame stamps (buffer
     * write aliases, cbv_frame) compare against it. */
    UINT64 debug_frame;
    /* R643: textures currently bound as shader resources of the bound
     * graphics pipeline, by unit (RHI_D3D12Texture*). The FBO bind paths warn
     * when one of them is about to become a render target. Cleared on every
     * pipeline bind (the root signature change drops the tables). */
    void *live_srv[16];
    UINT64 next_fence;
    UINT64 completed_fence;
    UINT64 descriptor_retire_fence;
    UINT descriptor_live;
    UINT device_lost;                   /* sticky latch */
    HRESULT removed_reason;
    UINT dred_enabled;
    /* R643: debug-layer messages drained into the log (debug builds only). */
    UINT64 debug_layer_errors;
    UINT64 debug_layer_warnings;
    UINT64 rt_srv_alias_count;   /* rhi_d3d12_warn_rt_srv_alias hits, all builds */
    RHI_D3D12CreateFailure injected_failure;
    RHI_D3D12Swapchain swapchain;       /* Task 4; valid iff swapchain_ready */
    UINT swapchain_ready;
    /* Task 6: legacy rhi_cmd_set_uniform_* staging — push-constant scratch
     * flushed as root constants before the next draw/dispatch (VK parity,
     * rhi.h:586-595). Byte range [lo, hi) is dirty; lo>hi = clean. */
    UINT8 uniform_staging[256];
    UINT uniform_dirty_lo;
    UINT uniform_dirty_hi;
    /* Material binder fallback: one shared 1x1 RGBA8 white texture, created
     * on first use and released by rhi_device_destroy with the rest of the
     * context. A D3D12 root descriptor table has no "unset" state the way a
     * GL texture unit does, so a material slot with an invalid handle binds
     * this instead of leaving the shader sampling an unwritten descriptor. */
    RHITexture white_fallback;
    /* R647: the cube twin of white_fallback — a 1x1 depth cube cleared to
     * 1.0 (unshadowed) that fills a declared TextureCube register no live
     * point-shadow cube was supplied for. Released with white_fallback. */
    RHICubemapDepthFBO cube_fallback;
    /* rhi_cmd_update_buffer / rhi_cmd_fill_buffer staging: each recorded
     * write gets its own UPLOAD buffer, copied in the frame's command list
     * so it is ordered against the commands around it (C-BUF-3). Released
     * when the slot's frame fence is reached. */
    ID3D12Resource **frame_staging[2];
    UINT frame_staging_count[2];
    UINT frame_staging_cap[2];
} RHI_D3D12Context;

typedef struct RHI_D3D12Resource {
    ID3D12Resource *resource;
    D3D12_RESOURCE_STATES state;
    UINT64 retire_fence;
} RHI_D3D12Resource;

/* Task 5: slot-table payloads for the public RHI handle API. Every buffer
 * is a committed resource (decision record: RHI resources are small and the
 * driver/OS own heap placement; placed resources wait for a real memory
 * pressure receipt). DEFAULT-heap buffers carry upload staging;
 * UPLOAD-heap buffers are persistently mappable. */
typedef struct RHI_D3D12Buffer {
    ID3D12Resource *resource;
    UINT64 size;
    UINT usage;                 /* RHIBufferUsage bits */
    D3D12_RESOURCE_STATES state;
    UINT device_local;          /* DEFAULT heap; 0 = UPLOAD heap */
    UINT allow_uav;             /* created with ALLOW_UNORDERED_ACCESS */
    void *mapped;               /* non-NULL while rhi_buffer_map is open */
    /* UPLOAD-heap buffers only: the frame-staging snapshot that a recorded
     * write (rhi_cmd_update_buffer / _fill_buffer) produced, valid while
     * alias_frame == the context's debug_frame. Binds read it instead of
     * resource so they see the write at its place in the frame. Not owned:
     * the frame staging list releases it. */
    ID3D12Resource *alias_resource;
    UINT64 alias_frame;
    /* R652: UPLOAD-heap buffers only: a READBACK-heap twin that a recorded
     * rhi_cmd_copy_buffer lands in (an UPLOAD heap can never be a copy
     * destination), created on the first such copy. Once it exists
     * rhi_buffer_map / rhi_buffer_read return its bytes -- the GPU-written
     * staging contract the VK/GL backends give a host-visible buffer. */
    ID3D12Resource *readback;
} RHI_D3D12Buffer;

typedef struct RHI_D3D12Texture {
    ID3D12Resource *resource;
    DXGI_FORMAT dxgi_format;
    /* The format a shader resource view over this texture must declare.
     * DXGI_FORMAT_UNKNOWN (calloc default) means "same as dxgi_format", which
     * is every colour texture and every ordinary D32_FLOAT depth target.
     * A shadow-atlas depth texture instead allocates the typeless
     * R32_TYPELESS and sets this to R32_FLOAT, because D32_FLOAT
     * cannot back an SRV at all and the lighting pass has to read the depth
     * the shadow pass wrote. */
    DXGI_FORMAT srv_format;
    UINT rhi_format;            /* RHIFormat */
    UINT width;
    UINT height;
    UINT mip_levels;
    /* R441: array slices in the resource (D3D12_RESOURCE_DESC.DepthOrArraySize).
     * 1 = an ordinary 2D texture, which is every target the backend allocated
     * before rhi_texture_array_create existed. >1 means a 2D array, and then
     * rhi_cmd_bind_texture must emit a D3D12_SRV_DIMENSION_TEXTURE2DARRAY view
     * covering every layer — a TEXTURE2D descriptor over a multi-slice resource
     * is a dimension mismatch the shader cannot sample through. */
    UINT array_size;
    /* R647: six slices that a shader samples as a TextureCube (the point-
     * shadow depth cubes). rhi_cmd_bind_texture then emits a TEXTURECUBE view
     * instead of a 2D-array one, and rhi_d3d12_live_cube accepts the handle. */
    UINT is_cube;
    D3D12_RESOURCE_STATES state;
    /* R653: per-mip states while a compute pass works mip by mip (the Hi-Z
     * pyramid: one mip read as an SRV while the next ones are written as
     * UAVs). mip_split == 0 means every mip is in `state`; otherwise
     * mip_state[m] is authoritative and any whole-resource use first brings
     * every mip back to one state (rhi_d3d12_tex_unify). */
    UINT mip_split;
    D3D12_RESOURCE_STATES mip_state[16];
} RHI_D3D12Texture;

typedef struct RHI_D3D12Sampler {
    UINT slot;                  /* sampler_alloc slot */
} RHI_D3D12Sampler;

/* Offscreen FBO: the color/depth textures are ordinary RHI_RES_TEXTURE
 * resources (rhi_texture_create already adds ALLOW_RENDER_TARGET /
 * ALLOW_DEPTH_STENCIL); the descriptor slots stay owned for the FBO
 * lifetime and are returned through the fence-retire path on destroy. */
typedef struct RHI_D3D12FBO {
    UINT rtv_slot;              /* rtv_alloc slot */
    UINT dsv_slot;              /* dsv_alloc slot */
    UINT width, height;
    UINT sample_count;
    float clear_color[4];       /* caller-owned bind clear (R619) */
} RHI_D3D12FBO;

typedef struct RHI_D3D12MRTFBO {
    UINT rtv_slots[RHI_MRT_MAX_ATTACHMENTS];
    UINT dsv_slot;
    UINT width, height, attachment_count, sample_count;
    float clear_color[RHI_MRT_MAX_ATTACHMENTS][4];
} RHI_D3D12MRTFBO;

/* Shadow atlas: depth-only, no colour attachment, so only the DSV slot is
 * held. The depth texture is an ordinary RHI_RES_TEXTURE created with the
 * typeless alias (see RHI_D3D12Texture.srv_format) because the lighting pass
 * samples back what the shadow pass writes. */
typedef struct RHI_D3D12ShadowAtlas {
    UINT dsv_slot;              /* dsv_alloc slot */
    UINT width, height;
} RHI_D3D12ShadowAtlas;

/* R647: point-light depth cube. The depth texture is an ordinary
 * RHI_RES_TEXTURE (typeless alias, six slices, is_cube); this holds one DSV
 * per face, each a single-slice TEXTURE2DARRAY view. */
typedef struct RHI_D3D12CubeDepthFBO {
    UINT dsv_slots[6];          /* dsv_alloc slots, UINT_MAX = none */
    UINT size;
} RHI_D3D12CubeDepthFBO;

/* Root signature builder: one pass over reflected ShaderIOBindings
 * (core/shader_io.h) plus the pipeline's push-constant contract.
 * PUSH_CONSTANT folds into a single 32BIT_CONSTANTS param (index 0 when
 * present, 128B compute / 256B graphics, matching the VK declared ranges);
 * UNIFORM -> CBV table, STORAGE -> UAV table, SAMPLER -> SRV table + static
 * sampler, IMAGE -> SRV table; descriptor registers follow the binding. */
typedef struct RHI_D3D12RootSigBuilder {
    D3D12_ROOT_PARAMETER1 params[16];
    D3D12_DESCRIPTOR_RANGE1 ranges[16];
    D3D12_STATIC_SAMPLER_DESC samplers[8];
    UINT param_count;
    UINT range_count;
    UINT sampler_count;
    UINT image_root_params[16]; /* register(tN) -> root parameter */
    UINT uniform_root_params[16]; /* register(bN) -> root parameter */
    UINT storage_root_params[16]; /* register(uN) -> root parameter */
    /* register(uN) view shape: 0 = raw (RWByteAddressBuffer), N > 0 =
     * structured with an N byte element, UINT_MAX = not a buffer view this
     * backend can describe (RWTexture*, or an element type it cannot size). */
    UINT storage_strides[16];
    /* register(tN) declared as a read-only buffer (ByteAddressBuffer /
     * StructuredBuffer<T>): same encoding as storage_strides; UINT_MAX = not
     * a buffer (a texture, or nothing). The root parameter is
     * image_root_params[N]. */
    UINT srv_buffer_strides[16];
    UINT push_constant_size;   /* bytes; 0 = none */
} RHI_D3D12RootSigBuilder;

HRESULT rhi_d3d12_context_create(RHI_D3D12Context *context,
                                 RHI_D3D12CreateFailure injected_failure);
void rhi_d3d12_context_destroy(RHI_D3D12Context *context);
HRESULT rhi_d3d12_context_retire(RHI_D3D12Context *context, UINT64 value);
HRESULT rhi_d3d12_descriptor_acquire(RHI_D3D12Context *context);
HRESULT rhi_d3d12_descriptor_retire(RHI_D3D12Context *context);
HRESULT rhi_d3d12_buffer_create(RHI_D3D12Context *context, UINT64 size,
                                RHI_D3D12Resource *out_resource);
void rhi_d3d12_resource_destroy(RHI_D3D12Resource *resource);
HRESULT rhi_d3d12_resource_transition(RHI_D3D12Context *context,
                                      ID3D12GraphicsCommandList *command_list,
                                      RHI_D3D12Resource *resource,
                                      D3D12_RESOURCE_STATES next_state);
HRESULT rhi_d3d12_submit(RHI_D3D12Context *context, UINT allocator_index,
                         UINT64 *out_fence);

/* Task 5 descriptor allocator API (Task 7 DXR reuses these). init fills the
 * free-list over an already-created heap (non-owning); take pops the
 * youngest free slot unless its retire fence is still GPU-busy; give_back
 * pushes a slot with the fence value after which reuse is safe. */
HRESULT rhi_d3d12_descriptor_alloc_init(RHI_D3D12DescriptorAlloc *alloc,
                                        ID3D12DescriptorHeap *heap,
                                        UINT increment, UINT capacity);
void rhi_d3d12_descriptor_alloc_destroy(RHI_D3D12DescriptorAlloc *alloc);
UINT rhi_d3d12_descriptor_take(RHI_D3D12Context *context,
                               RHI_D3D12DescriptorAlloc *alloc);
void rhi_d3d12_descriptor_give_back(RHI_D3D12DescriptorAlloc *alloc,
                                    UINT slot, UINT64 retire_fence);
D3D12_CPU_DESCRIPTOR_HANDLE rhi_d3d12_descriptor_cpu(
    const RHI_D3D12DescriptorAlloc *alloc, UINT slot);
D3D12_GPU_DESCRIPTOR_HANDLE rhi_d3d12_descriptor_gpu(
    const RHI_D3D12DescriptorAlloc *alloc, UINT slot);
/* Last fence value submitted on the direct queue; 0 when nothing is in
 * flight. Used as the retire fence for descriptor/resource give-back. */
UINT64 rhi_d3d12_retire_fence(const RHI_D3D12Context *context);

/* ExecuteIndirect argument gate. Indexed draws follow the shared ABI rule
 * (rhi.h:227-230) AND the command-signature stride (fixed at creation to
 * sizeof(RHIIndexedIndirectCommand)); non-indexed draws use 16-byte
 * D3D12_DRAW_ARGUMENTS strides and must NOT pass through the indexed ABI
 * rule (VK parity: vkCmdDrawIndirect applies no such check). */
UINT rhi_d3d12_indirect_args_valid(UINT indexed, UINT stride, UINT draw_count);

/* ---- Task 1 (D3D12 shader path): GLSL path -> HLSL sidecar name ----
 * The engine hands the RHI GLSL text and drops the file path, so this
 * mapping is the only way D3D12 can find its hand-authored sidecars.
 * Pure string logic with no device dependency, so the contract test locks
 * it down directly. */
typedef enum RHI_D3D12ShaderStage {
    RHI_D3D12_SHADER_STAGE_VERTEX = 0,
    RHI_D3D12_SHADER_STAGE_FRAGMENT = 1,
    RHI_D3D12_SHADER_STAGE_COMPUTE = 2,
} RHI_D3D12ShaderStage;

#define RHI_D3D12_SHADER_SIDECAR_NAME_CAPACITY 256u

/* Map a shader file path onto the bare file name of its sidecar: the final
 * path component with its extension stripped, plus "_hlsl.<stage>".
 *
 * Returns 1 and writes a NUL-terminated name on success; returns 0, writes
 * out[0] = '\0' and warns with the reason otherwise. Fails closed when the
 * path's own extension names a different stage than `stage` (silently
 * resolving the wrong sidecar is worse than refusing), when the path has no
 * usable base name, or when the name would not fit `out_cap` — a truncated
 * name would resolve a different file, never the intended one.
 *
 * Decision record: the "_hlsl" suffix is idempotent — a base that already
 * ends in "_hlsl" resolves to itself instead of growing a second suffix.
 * The plan's wording ("strip directory and extension, append _hlsl") taken
 * literally would map shaders/blit_hlsl.vert to the non-existent
 * blit_hlsl_hlsl.vert, and Task 2 asserts that self-resolution form. */
int rhi_d3d12_shader_sidecar_name(const char *path,
                                  RHI_D3D12ShaderStage stage, char *out,
                                  usize out_cap);

/* Task 4: flip-model swapchain. create binds the swapchain to `hwnd` (or to
 * a device-owned hidden fallback window when `hwnd` is not a real window,
 * which only contract tests do) and creates one RTV per back buffer in
 * context->rtv_heap; resize assumes the caller already drained the device
 * (spec §4.3) and re-creates the RTVs; destroy releases back buffers, the
 * swapchain, and any owned fallback window. */
/* R643: drains the debug layer's info queue and reports how many ERROR /
 * CORRUPTION and WARNING messages it has logged since device creation, plus
 * how many times the backend's own RT/SRV alias diagnostic fired (that one
 * counts in every build). Returns 1 when the debug layer is compiled in
 * (ENGINE_D3D12_DEBUG), 0 otherwise -- errors/warnings then stay 0 and prove
 * nothing. Tests use it to assert that a scenario is clean under
 * validation. Any out pointer may be NULL. */
int rhi_d3d12_debug_layer_counts(RHIDevice *dev, UINT64 *errors,
                                 UINT64 *warnings, UINT64 *rt_srv_aliases);

HRESULT rhi_d3d12_swapchain_create(RHI_D3D12Context *context,
                                   RHI_D3D12Swapchain *out, HWND hwnd,
                                   UINT width, UINT height);
HRESULT rhi_d3d12_swapchain_resize(RHI_D3D12Context *context,
                                   RHI_D3D12Swapchain *swapchain,
                                   UINT width, UINT height);
void    rhi_d3d12_swapchain_destroy(RHI_D3D12Context *context,
                                    RHI_D3D12Swapchain *swapchain);

#endif

#endif
