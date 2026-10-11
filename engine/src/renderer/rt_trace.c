#include <renderer/rt_trace.h>
#include <core/types.h>
#include <core/log.h>
#include <string.h>
#include <stdio.h>

#ifdef ENGINE_VULKAN

#include <vulkan/vulkan.h>
#include <shaderc/shaderc.h>

static char g_last_error[96];

static void rt_fail(const char *reason) {
    snprintf(g_last_error, sizeof(g_last_error), "%s", reason);
}

const char *rt_trace_last_error(void) {
    return g_last_error[0] ? g_last_error : "no error recorded";
}

static const char k_raygen_glsl[] =
    "#version 460\n"
    "#extension GL_EXT_ray_tracing : require\n"
    "layout(set = 0, binding = 0) uniform accelerationStructureEXT u_tlas;\n"
    "layout(set = 0, binding = 1, rgba8) uniform image2D u_out;\n"
    "layout(location = 0) rayPayloadEXT vec3 u_payload;\n"
    "void main() {\n"
    "    vec3 origin = vec3(0.0, 0.0, 1.0);\n"
    "    vec3 direction = vec3(0.0, 0.0, -1.0);\n"
    "    traceRayEXT(u_tlas, gl_RayFlagsOpaqueEXT, 0xff, 0, 0, 0,\n"
    "                origin, 0.05, direction, 16.0, 0);\n"
    "    imageStore(u_out, ivec2(0), vec4(u_payload, 1.0));\n"
    "}\n";

static const char k_miss_glsl[] =
    "#version 460\n"
    "#extension GL_EXT_ray_tracing : require\n"
    "layout(location = 0) rayPayloadEXT vec3 u_payload;\n"
    "void main() { u_payload = vec3(0.0, 0.0, 1.0); }\n";

static const char k_closest_hit_glsl[] =
    "#version 460\n"
    "#extension GL_EXT_ray_tracing : require\n"
    "layout(location = 0) rayPayloadEXT vec3 u_payload;\n"
    "void main() { u_payload = vec3(0.0, 1.0, 0.0); }\n";

typedef struct {
    VkShaderModule module;
    VkPipelineShaderStageCreateInfo stage;
} RTShader;

typedef struct {
    VkDevice device;
    VkCommandPool pool;
    VkDescriptorPool desc_pool;
    VkDescriptorSetLayout desc_layout;
    VkDescriptorSet desc_set;
    VkPipelineLayout pipeline_layout;
    VkPipeline pipeline;
    VkBuffer sbt_buffer;
    VkDeviceMemory sbt_memory;
    VkImage image;
    VkDeviceMemory image_memory;
    VkImageView image_view;
    VkBuffer staging;
    VkDeviceMemory staging_memory;
    void *staging_mapped;
} RTTraceObjects;

static u32 rt_find_memory(VkPhysicalDevice physical, u32 type_bits,
                          VkMemoryPropertyFlags props) {
    VkPhysicalDeviceMemoryProperties mem;
    u32 i;
    vkGetPhysicalDeviceMemoryProperties(physical, &mem);
    for (i = 0; i < mem.memoryTypeCount; i++) {
        if ((type_bits & (1u << i)) &&
            (mem.memoryTypes[i].propertyFlags & props) == props) return i;
    }
    return UINT32_MAX;
}

/* Create a buffer with `usage`, back it with memory of `props`, bind it. */
static bool rt_create_buffer(VkDevice device, VkPhysicalDevice physical,
                             VkDeviceSize size, VkBufferUsageFlags usage,
                             VkMemoryPropertyFlags props,
                             VkBuffer *out_buf, VkDeviceMemory *out_mem,
                             bool device_address) {
    VkBufferCreateInfo ci;
    VkMemoryRequirements req;
    VkMemoryAllocateInfo ai;
    VkMemoryAllocateFlagsInfo flags;
    memset(&ci, 0, sizeof(ci));
    ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    ci.size = size;
    ci.usage = usage;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(device, &ci, NULL, out_buf) != VK_SUCCESS) return false;
    vkGetBufferMemoryRequirements(device, *out_buf, &req);
    memset(&ai, 0, sizeof(ai));
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = req.size;
    ai.memoryTypeIndex = rt_find_memory(physical, req.memoryTypeBits, props);
    if (ai.memoryTypeIndex == UINT32_MAX) {
        vkDestroyBuffer(device, *out_buf, NULL);
        *out_buf = VK_NULL_HANDLE;
        return false;
    }
    memset(&flags, 0, sizeof(flags));
    if (device_address) {
        flags.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
        flags.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT;
        ai.pNext = &flags;
    }
    if (vkAllocateMemory(device, &ai, NULL, out_mem) != VK_SUCCESS ||
        vkBindBufferMemory(device, *out_buf, *out_mem, 0) != VK_SUCCESS) {
        vkDestroyBuffer(device, *out_buf, NULL);
        *out_buf = VK_NULL_HANDLE;
        if (*out_mem != VK_NULL_HANDLE) {
            vkFreeMemory(device, *out_mem, NULL);
            *out_mem = VK_NULL_HANDLE;
        }
        return false;
    }
    return true;
}

static bool rt_compile_stage(VkDevice device, const char *source,
                             shaderc_shader_kind kind, const char *name,
                             RTShader *out) {
    shaderc_compiler_t compiler = shaderc_compiler_initialize();
    shaderc_compile_options_t options = shaderc_compile_options_initialize();
    shaderc_compilation_result_t result;
    const char *spirv;
    size_t spirv_len;
    VkShaderModuleCreateInfo mi;
    VkShaderStageFlagBits stage;
    bool ok = false;

    memset(out, 0, sizeof(*out));
    if (compiler == NULL) {
        rt_fail("shaderc compiler init failed");
        return false;
    }
    shaderc_compile_options_set_target_env(
        options, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
    result = shaderc_compile_into_spv(compiler, source, strlen(source), kind,
                                      name, "main", options);
    if (shaderc_result_get_compilation_status(result) !=
        shaderc_compilation_status_success) {
        rt_fail("rt shader compile failed");
    } else {
        spirv = shaderc_result_get_bytes(result);
        spirv_len = shaderc_result_get_length(result);
        memset(&mi, 0, sizeof(mi));
        mi.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        mi.codeSize = spirv_len;
        mi.pCode = (const u32 *)(const void *)spirv;
        if (vkCreateShaderModule(device, &mi, NULL, &out->module) ==
            VK_SUCCESS) {
            stage = (kind == shaderc_raygen_shader)
                ? VK_SHADER_STAGE_RAYGEN_BIT_KHR
                : (kind == shaderc_miss_shader)
                    ? VK_SHADER_STAGE_MISS_BIT_KHR
                    : VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
            out->stage.sType =
                VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            out->stage.stage = stage;
            out->stage.module = out->module;
            out->stage.pName = "main";
            ok = true;
        } else {
            rt_fail("shader module creation failed");
        }
    }
    shaderc_result_release(result);
    shaderc_compile_options_release(options);
    shaderc_compiler_release(compiler);
    return ok;
}

static bool rt_trace_probe_impl(RHIDevice *dev, RHIAccelerationStructure as,
                                u8 out_pixel[4]) {
    RHINativeDevice native;
    RHICapabilities caps;
    RTTraceObjects o;
    RTShader raygen, miss, hit;
    VkPhysicalDevice physical;
    VkQueue queue;
    VkPhysicalDeviceRayTracingPipelinePropertiesKHR rt_props;
    VkPhysicalDeviceProperties2 props2;
    PFN_vkGetRayTracingShaderGroupHandlesKHR get_handles;
    PFN_vkCreateRayTracingPipelinesKHR create_rt_pipelines;
    PFN_vkCmdTraceRaysKHR trace_rays;
    PFN_vkGetBufferDeviceAddress get_addr;
    void *as_handle = NULL;
    VkCommandBuffer cmd = VK_NULL_HANDLE;
    VkDeviceSize handle_size, group_stride, slot, sbt_size, sbt_address = 0;
    bool result = false;

    g_last_error[0] = '\0';
    if (out_pixel != NULL) memset(out_pixel, 0, 4);
    if (dev == NULL || out_pixel == NULL) {
        rt_fail("invalid arguments");
        return false;
    }
    memset(&caps, 0, sizeof(caps));
    if (!rhi_device_get_capabilities(dev, &caps) ||
        (caps.feature_bits & RHI_FEATURE_RAY_TRACING_PIPELINE) == 0u ||
        (caps.feature_bits & RHI_FEATURE_ACCELERATION_STRUCTURE) == 0u) {
        rt_fail("ray tracing pipeline unsupported on this device");
        return false;
    }
    memset(&native, 0, sizeof(native));
    if (!rhi_device_get_native_device(dev, &native) ||
        native.type != RHI_NATIVE_HANDLE_VULKAN) {
        rt_fail("native vulkan device unavailable");
        return false;
    }
    if (!rhi_acceleration_structure_get_vk_handle(dev, as, &as_handle) ||
        as_handle == NULL) {
        rt_fail("native acceleration structure handle unavailable");
        return false;
    }

    memset(&o, 0, sizeof(o));
    memset(&raygen, 0, sizeof(raygen));
    memset(&miss, 0, sizeof(miss));
    memset(&hit, 0, sizeof(hit));
    o.device = (VkDevice)(uintptr_t)native.device;
    physical = (VkPhysicalDevice)(uintptr_t)native.physical_device;
    queue = (VkQueue)(uintptr_t)native.graphics_queue;

    memset(&rt_props, 0, sizeof(rt_props));
    rt_props.sType =
        VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR;
    memset(&props2, 0, sizeof(props2));
    props2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    props2.pNext = &rt_props;
    vkGetPhysicalDeviceProperties2(physical, &props2);
    get_handles = (PFN_vkGetRayTracingShaderGroupHandlesKHR)vkGetDeviceProcAddr(
        o.device, "vkGetRayTracingShaderGroupHandlesKHR");
    create_rt_pipelines = (PFN_vkCreateRayTracingPipelinesKHR)
        vkGetDeviceProcAddr(o.device, "vkCreateRayTracingPipelinesKHR");
    trace_rays =
        (PFN_vkCmdTraceRaysKHR)vkGetDeviceProcAddr(o.device, "vkCmdTraceRaysKHR");
    get_addr = (PFN_vkGetBufferDeviceAddress)vkGetDeviceProcAddr(
        o.device, "vkGetBufferDeviceAddress");
    if (get_handles == NULL || create_rt_pipelines == NULL ||
        trace_rays == NULL || get_addr == NULL ||
        rt_props.shaderGroupHandleSize == 0) {
        rt_fail("ray tracing entry points unavailable");
        return false;
    }

    if (!rt_compile_stage(o.device, k_raygen_glsl, shaderc_raygen_shader,
                          "raygen.glsl", &raygen) ||
        !rt_compile_stage(o.device, k_miss_glsl, shaderc_miss_shader,
                          "miss.glsl", &miss) ||
        !rt_compile_stage(o.device, k_closest_hit_glsl,
                          shaderc_closesthit_shader, "chit.glsl", &hit)) {
        goto cleanup;
    }

    {
        VkCommandPoolCreateInfo ci;
        memset(&ci, 0, sizeof(ci));
        ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        ci.queueFamilyIndex = native.graphics_queue_family;
        if (vkCreateCommandPool(o.device, &ci, NULL, &o.pool) != VK_SUCCESS) {
            rt_fail("command pool creation failed");
            goto cleanup;
        }
    }

    {
        VkDescriptorSetLayoutBinding bindings[2];
        VkDescriptorSetLayoutCreateInfo ci;
        memset(bindings, 0, sizeof(bindings));
        bindings[0].binding = 0u;
        bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
        bindings[0].descriptorCount = 1u;
        bindings[0].stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR;
        bindings[1].binding = 1u;
        bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        bindings[1].descriptorCount = 1u;
        bindings[1].stageFlags = VK_SHADER_STAGE_RAYGEN_BIT_KHR;
        memset(&ci, 0, sizeof(ci));
        ci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        ci.bindingCount = 2u;
        ci.pBindings = bindings;
        if (vkCreateDescriptorSetLayout(o.device, &ci, NULL, &o.desc_layout) !=
            VK_SUCCESS) {
            rt_fail("descriptor layout creation failed");
            goto cleanup;
        }
    }
    {
        VkDescriptorPoolSize sizes[2];
        VkDescriptorPoolCreateInfo pi;
        VkDescriptorSetAllocateInfo ai;
        memset(sizes, 0, sizeof(sizes));
        sizes[0].type = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
        sizes[0].descriptorCount = 1u;
        sizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        sizes[1].descriptorCount = 1u;
        memset(&pi, 0, sizeof(pi));
        pi.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pi.maxSets = 1u;
        pi.poolSizeCount = 2u;
        pi.pPoolSizes = sizes;
        if (vkCreateDescriptorPool(o.device, &pi, NULL, &o.desc_pool) !=
            VK_SUCCESS) {
            rt_fail("descriptor pool creation failed");
            goto cleanup;
        }
        memset(&ai, 0, sizeof(ai));
        ai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        ai.descriptorPool = o.desc_pool;
        ai.descriptorSetCount = 1u;
        ai.pSetLayouts = &o.desc_layout;
        if (vkAllocateDescriptorSets(o.device, &ai, &o.desc_set) !=
            VK_SUCCESS) {
            rt_fail("descriptor set allocation failed");
            goto cleanup;
        }
    }
    {
        VkPipelineLayoutCreateInfo ci;
        memset(&ci, 0, sizeof(ci));
        ci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        ci.setLayoutCount = 1u;
        ci.pSetLayouts = &o.desc_layout;
        if (vkCreatePipelineLayout(o.device, &ci, NULL, &o.pipeline_layout) !=
            VK_SUCCESS) {
            rt_fail("pipeline layout creation failed");
            goto cleanup;
        }
    }
    {
        VkImageCreateInfo ci;
        VkMemoryRequirements req;
        VkMemoryAllocateInfo ai;
        VkImageViewCreateInfo vi;
        memset(&ci, 0, sizeof(ci));
        ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ci.imageType = VK_IMAGE_TYPE_2D;
        ci.format = VK_FORMAT_R8G8B8A8_UNORM;
        ci.extent.width = 1u;
        ci.extent.height = 1u;
        ci.extent.depth = 1u;
        ci.mipLevels = 1u;
        ci.arrayLayers = 1u;
        ci.samples = VK_SAMPLE_COUNT_1_BIT;
        ci.tiling = VK_IMAGE_TILING_OPTIMAL;
        ci.usage = VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        if (vkCreateImage(o.device, &ci, NULL, &o.image) != VK_SUCCESS) {
            rt_fail("output image creation failed");
            goto cleanup;
        }
        vkGetImageMemoryRequirements(o.device, o.image, &req);
        memset(&ai, 0, sizeof(ai));
        ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        ai.allocationSize = req.size;
        ai.memoryTypeIndex = rt_find_memory(physical, req.memoryTypeBits,
                                            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        if (ai.memoryTypeIndex == UINT32_MAX ||
            vkAllocateMemory(o.device, &ai, NULL, &o.image_memory) !=
                VK_SUCCESS ||
            vkBindImageMemory(o.device, o.image, o.image_memory, 0) !=
                VK_SUCCESS) {
            rt_fail("output image memory failed");
            goto cleanup;
        }
        memset(&vi, 0, sizeof(vi));
        vi.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vi.image = o.image;
        vi.viewType = VK_IMAGE_VIEW_TYPE_2D;
        vi.format = VK_FORMAT_R8G8B8A8_UNORM;
        vi.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        vi.subresourceRange.levelCount = 1u;
        vi.subresourceRange.layerCount = 1u;
        if (vkCreateImageView(o.device, &vi, NULL, &o.image_view) !=
            VK_SUCCESS) {
            rt_fail("image view creation failed");
            goto cleanup;
        }
    }

    {
        VkAccelerationStructureKHR as_vk =
            (VkAccelerationStructureKHR)(uintptr_t)as_handle;
        VkWriteDescriptorSetAccelerationStructureKHR accel_write;
        VkDescriptorImageInfo image_info;
        VkWriteDescriptorSet writes[2];
        memset(&accel_write, 0, sizeof(accel_write));
        accel_write.sType =
            VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR;
        accel_write.accelerationStructureCount = 1u;
        accel_write.pAccelerationStructures = &as_vk;
        memset(&image_info, 0, sizeof(image_info));
        image_info.imageView = o.image_view;
        image_info.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
        memset(writes, 0, sizeof(writes));
        writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[0].dstSet = o.desc_set;
        writes[0].dstBinding = 0u;
        writes[0].descriptorCount = 1u;
        writes[0].descriptorType =
            VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
        writes[0].pNext = &accel_write;
        writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[1].dstSet = o.desc_set;
        writes[1].dstBinding = 1u;
        writes[1].descriptorCount = 1u;
        writes[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        writes[1].pImageInfo = &image_info;
        vkUpdateDescriptorSets(o.device, 2u, writes, 0u, NULL);
    }

    {
        VkRayTracingShaderGroupCreateInfoKHR groups[3];
        VkPipelineShaderStageCreateInfo stages[3];
        VkRayTracingPipelineCreateInfoKHR ci;
        VkResult r;
        memset(groups, 0, sizeof(groups));
        groups[0].sType =
            VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
        groups[0].type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR;
        groups[0].generalShader = 0u;
        groups[1].sType =
            VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
        groups[1].type = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR;
        groups[1].generalShader = 1u;
        groups[2].sType =
            VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
        groups[2].type =
            VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR;
        groups[2].closestHitShader = 2u;
        /* Unused stage slots must be VK_SHADER_UNUSED_KHR, not zero. */
        groups[0].closestHitShader = VK_SHADER_UNUSED_KHR;
        groups[0].anyHitShader = VK_SHADER_UNUSED_KHR;
        groups[0].intersectionShader = VK_SHADER_UNUSED_KHR;
        groups[1].closestHitShader = VK_SHADER_UNUSED_KHR;
        groups[1].anyHitShader = VK_SHADER_UNUSED_KHR;
        groups[1].intersectionShader = VK_SHADER_UNUSED_KHR;
        groups[2].generalShader = VK_SHADER_UNUSED_KHR;
        groups[2].anyHitShader = VK_SHADER_UNUSED_KHR;
        groups[2].intersectionShader = VK_SHADER_UNUSED_KHR;
        stages[0] = raygen.stage;
        stages[1] = miss.stage;
        stages[2] = hit.stage;
        memset(&ci, 0, sizeof(ci));
        ci.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
        ci.stageCount = 3u;
        ci.pStages = stages;
        ci.groupCount = 3u;
        ci.pGroups = groups;
        ci.maxPipelineRayRecursionDepth = 1u;
        ci.layout = o.pipeline_layout;
        r = create_rt_pipelines(o.device, VK_NULL_HANDLE, VK_NULL_HANDLE, 1u,
                                &ci, NULL, &o.pipeline);
        if (r != VK_SUCCESS) {
            rt_fail("ray tracing pipeline creation failed");
            goto cleanup;
        }
    }

    /* SBT: three slots, each aligned to the stricter of handle-alignment and
     * base-alignment, so every region start satisfies both rules. */
    handle_size = (VkDeviceSize)rt_props.shaderGroupHandleSize;
    group_stride = (VkDeviceSize)rt_props.shaderGroupHandleAlignment;
    slot = group_stride;
    if ((VkDeviceSize)rt_props.shaderGroupBaseAlignment > slot)
        slot = (VkDeviceSize)rt_props.shaderGroupBaseAlignment;
    sbt_size = slot * 3;
    if (!rt_create_buffer(o.device, physical, sbt_size,
                          VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR |
                              VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                              VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                          &o.sbt_buffer, &o.sbt_memory, true)) {
        rt_fail("sbt buffer allocation failed");
        goto cleanup;
    }
    {
        u8 *mapped = NULL;
        u8 handles[256];
        VkBufferDeviceAddressInfo addr_info;
        if (vkMapMemory(o.device, o.sbt_memory, 0, VK_WHOLE_SIZE, 0,
                        (void **)&mapped) != VK_SUCCESS) {
            rt_fail("sbt map failed");
            goto cleanup;
        }
        memset(handles, 0, sizeof(handles));
        if (get_handles(o.device, o.pipeline, 0u, 3u, sizeof(handles),
                        handles) != VK_SUCCESS) {
            vkUnmapMemory(o.device, o.sbt_memory);
            rt_fail("shader group handles query failed");
            goto cleanup;
        }
        memset(mapped, 0, (size_t)sbt_size);
        for (u32 i = 0; i < 3u; i++) {
            memcpy(mapped + (size_t)(slot * (VkDeviceSize)i),
                   handles + (size_t)(handle_size * (VkDeviceSize)i),
                   (size_t)handle_size);
        }
        vkUnmapMemory(o.device, o.sbt_memory);
        memset(&addr_info, 0, sizeof(addr_info));
        addr_info.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
        addr_info.buffer = o.sbt_buffer;
        sbt_address = get_addr(o.device, &addr_info);
        if (sbt_address == 0) {
            rt_fail("sbt device address is zero");
            goto cleanup;
        }
    }

    if (!rt_create_buffer(o.device, physical, 4,
                          VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                              VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                          &o.staging, &o.staging_memory, false)) {
        rt_fail("staging buffer allocation failed");
        goto cleanup;
    }
    if (vkMapMemory(o.device, o.staging_memory, 0, VK_WHOLE_SIZE, 0,
                    &o.staging_mapped) != VK_SUCCESS) {
        rt_fail("staging map failed");
        goto cleanup;
    }

    {
        VkCommandBufferAllocateInfo alloc;
        VkCommandBufferBeginInfo begin;
        VkImageMemoryBarrier to_general;
        VkImageMemoryBarrier to_src;
        VkBufferImageCopy region;
        VkSubmitInfo submit;
        VkStridedDeviceAddressRegionKHR raygen_region;
        VkStridedDeviceAddressRegionKHR miss_region;
        VkStridedDeviceAddressRegionKHR hit_region;
        VkStridedDeviceAddressRegionKHR callable_region;

        memset(&alloc, 0, sizeof(alloc));
        alloc.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc.commandPool = o.pool;
        alloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc.commandBufferCount = 1u;
        if (vkAllocateCommandBuffers(o.device, &alloc, &cmd) != VK_SUCCESS) {
            rt_fail("command buffer allocation failed");
            goto cleanup;
        }
        memset(&begin, 0, sizeof(begin));
        begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        if (vkBeginCommandBuffer(cmd, &begin) != VK_SUCCESS) {
            rt_fail("command buffer begin failed");
            goto cleanup;
        }

        memset(&to_general, 0, sizeof(to_general));
        to_general.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        to_general.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
        to_general.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        to_general.newLayout = VK_IMAGE_LAYOUT_GENERAL;
        to_general.image = o.image;
        to_general.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        to_general.subresourceRange.levelCount = 1u;
        to_general.subresourceRange.layerCount = 1u;
        to_general.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        to_general.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                             VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR, 0,
                             0, NULL, 0, NULL, 1, &to_general);

        vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR,
                          o.pipeline);
        vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR,
                                o.pipeline_layout, 0u, 1u, &o.desc_set, 0u,
                                NULL);

        raygen_region.deviceAddress = sbt_address;
        raygen_region.stride = slot;
        raygen_region.size = slot;
        miss_region.deviceAddress = sbt_address + slot;
        miss_region.stride = slot;
        miss_region.size = slot;
        hit_region.deviceAddress = sbt_address + slot * 2;
        hit_region.stride = slot;
        hit_region.size = slot;
        memset(&callable_region, 0, sizeof(callable_region));
        trace_rays(cmd, &raygen_region, &miss_region, &hit_region,
                   &callable_region, 1u, 1u, 1u);

        memset(&to_src, 0, sizeof(to_src));
        to_src.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        to_src.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
        to_src.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        to_src.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
        to_src.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        to_src.image = o.image;
        to_src.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        to_src.subresourceRange.levelCount = 1u;
        to_src.subresourceRange.layerCount = 1u;
        to_src.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        to_src.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR,
                             VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0,
                             NULL, 1, &to_src);

        memset(&region, 0, sizeof(region));
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.layerCount = 1u;
        region.imageExtent.width = 1u;
        region.imageExtent.height = 1u;
        region.imageExtent.depth = 1u;
        vkCmdCopyImageToBuffer(cmd, o.image,
                               VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                               o.staging, 1u, &region);

        if (vkEndCommandBuffer(cmd) != VK_SUCCESS) {
            rt_fail("command buffer end failed");
            goto cleanup;
        }
        memset(&submit, 0, sizeof(submit));
        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit.commandBufferCount = 1u;
        submit.pCommandBuffers = &cmd;
        {
            VkResult rs = vkQueueSubmit(queue, 1u, &submit, VK_NULL_HANDLE);
            VkResult rw = (rs == VK_SUCCESS)
                ? vkQueueWaitIdle(queue) : VK_SUCCESS;
            if (rs != VK_SUCCESS) {
                rt_fail("trace queue submit failed");
                goto cleanup;
            }
            if (rw != VK_SUCCESS) {
                rt_fail("trace queue wait failed");
                goto cleanup;
            }
        }
    }

    memcpy(out_pixel, o.staging_mapped, 4);
    result = true;

cleanup:
    if (o.staging_mapped) vkUnmapMemory(o.device, o.staging_memory);
    if (o.staging) vkDestroyBuffer(o.device, o.staging, NULL);
    if (o.staging_memory) vkFreeMemory(o.device, o.staging_memory, NULL);
    if (o.image_view) vkDestroyImageView(o.device, o.image_view, NULL);
    if (o.image) vkDestroyImage(o.device, o.image, NULL);
    if (o.image_memory) vkFreeMemory(o.device, o.image_memory, NULL);
    if (o.sbt_buffer) vkDestroyBuffer(o.device, o.sbt_buffer, NULL);
    if (o.sbt_memory) vkFreeMemory(o.device, o.sbt_memory, NULL);
    if (o.pipeline) vkDestroyPipeline(o.device, o.pipeline, NULL);
    if (o.pipeline_layout)
        vkDestroyPipelineLayout(o.device, o.pipeline_layout, NULL);
    if (o.desc_layout)
        vkDestroyDescriptorSetLayout(o.device, o.desc_layout, NULL);
    if (o.desc_pool) vkDestroyDescriptorPool(o.device, o.desc_pool, NULL);
    if (o.pool) vkDestroyCommandPool(o.device, o.pool, NULL);
    if (raygen.module) vkDestroyShaderModule(o.device, raygen.module, NULL);
    if (miss.module) vkDestroyShaderModule(o.device, miss.module, NULL);
    if (hit.module) vkDestroyShaderModule(o.device, hit.module, NULL);
    return result;
}

bool rt_trace_probe(RHIDevice *dev, RHIAccelerationStructure tlas,
                    u8 out_pixel[4]) {
    return rt_trace_probe_impl(dev, tlas, out_pixel);
}

bool rt_trace_probe_blas(RHIDevice *dev, RHIAccelerationStructure blas,
                         u8 out_pixel[4]) {
    return rt_trace_probe_impl(dev, blas, out_pixel);
}

#else /* !ENGINE_VULKAN */

const char *rt_trace_last_error(void) {
    return "ray tracing probe unavailable (non-vulkan build)";
}

bool rt_trace_probe(RHIDevice *dev, RHIAccelerationStructure tlas,
                    u8 out_pixel[4]) {
    (void)dev;
    (void)tlas;
    if (out_pixel != NULL) memset(out_pixel, 0, 4);
    return false;
}

bool rt_trace_probe_blas(RHIDevice *dev, RHIAccelerationStructure blas,
                         u8 out_pixel[4]) {
    (void)dev;
    (void)blas;
    if (out_pixel != NULL) memset(out_pixel, 0, 4);
    return false;
}

#endif
