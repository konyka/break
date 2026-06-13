#ifndef IBL_H
#define IBL_H

/*
 * Image Based Lighting (IBL) precomputation system.
 *
 * Generates the three split-sum approximation resources required by the
 * Cook-Torrance ambient term in pbr_clustered shaders:
 *   1. brdf_lut       - 512x512 RG (stored in RGBA16F) lookup of (NdotV, roughness)
 *                       integrated against GGX importance sampling.  Channel R holds
 *                       the Fresnel scale, channel G the bias.
 *   2. irradiance_map - 64x64 cubemap, hemisphere-cosine convolution of the
 *                       source environment cubemap (diffuse irradiance).
 *   3. prefilter_map  - 256x256 cubemap with 5 mip levels, importance-sampled
 *                       GGX pre-integration whose mip index encodes roughness.
 *
 * The system depends only on the public RHI surface declared in <rhi/rhi.h>.
 */

#include <core/types.h>
#include <rhi/rhi.h>

#define IBL_BRDF_LUT_SIZE       512u
#define IBL_IRRADIANCE_SIZE     64u
#define IBL_PREFILTER_SIZE      256u
#define IBL_PREFILTER_MIP_COUNT 5u
#define IBL_ENV_SIZE            128u

typedef struct {
    RHIDevice  *device;

    RHITexture  brdf_lut;       /* 512x512 RG16F (in RGBA16F) BRDF lookup table */
    RHICubemap  env_map;        /* 128x128 RGBA16F captured environment radiance */
    RHICubemap  irradiance_map; /* 64x64 diffuse irradiance cubemap            */
    RHICubemap  prefilter_map;  /* 256x256 prefiltered specular, 5 mip levels  */
    RHISampler  cubemap_sampler; /* sampler for reading env_map during convolution */

    RHIPipeline sky_capture_pipeline;
    RHIPipeline brdf_lut_pipeline;
    RHIPipeline irradiance_pipeline;
    RHIPipeline prefilter_pipeline;

    bool ready;
} IBLSystem;

/* Allocates GPU resources and (optionally) loads compute pipelines.
 * Returns true if all required resources were created successfully. */
void ibl_init(IBLSystem *sys, RHIDevice *dev);

/* Releases every GPU resource owned by the system. Safe to call multiple times. */
void ibl_destroy(IBLSystem *sys, RHIDevice *dev);

/* Renders the analytic atmospheric sky into sys->env_map (RGBA16F cubemap) via
 * the sky_to_cube compute pass, then leaves it in a shader-readable layout.
 * Call before ibl_generate to convolve a real environment instead of relying on
 * the procedural per-pixel fallback.  sun_dir/sun_color are 3-float arrays. */
void ibl_capture_env_sky(IBLSystem *sys, RHIDevice *dev,
                         const f32 sun_dir[3], const f32 sun_color[3]);

/* Runs the three precomputation passes against the supplied environment cubemap.
 * Marks sys->ready = true on success.  env_map may be RHI_HANDLE_NULL when only
 * the BRDF LUT (which is purely analytical) is required; pass sys->env_map after
 * ibl_capture_env_sky to convolve the captured environment. */
void ibl_generate(IBLSystem *sys, RHIDevice *dev, RHICubemap env_map);

#endif /* IBL_H */
