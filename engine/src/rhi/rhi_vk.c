#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.h>
#include <X11/Xlib.h>
#include <shaderc/shaderc.h>
#include <core/log.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define VK_MAX_FRAMES 2
#define VK_MAX_UNIFORMS 64

/* ---- Internal types ---- */

typedef struct {
    VkShaderModule module;
} VKShaderData;

typedef struct {
    VkPipelineLayout layout;
    VkPipeline        pipeline;
    u32               vertex_stride;
    bool              no_vertex_input;
    u32               push_range_count;
    VkPushConstantRange push_ranges[8];
    u32               uniform_offsets[VK_MAX_UNIFORMS];
    u32               uniform_sizes[VK_MAX_UNIFORMS];
    u32               uniform_count;
    bool              uses_texel_buffer;
    bool              is_instanced;
    bool              is_compute;
    bool              uses_storage;
} VKPipelineData;

typedef struct {
    VkBuffer       buffer;
    VkDeviceMemory memory;
    VkBufferView   texel_view;
    usize          size;
    bool           is_texel;
    u8            *mapped;
} VKBufferData;

typedef struct {
    VkImage        image;
    VkImageView    view;
    VkDeviceMemory memory;
    u32            width;
    u32            height;
} VKTextureData;

typedef struct {
    VkSampler sampler;
} VKSamplerData;

typedef struct {
    VkFramebuffer fbo;
} VKFramebufferData;

typedef struct {
    VkDeviceMemory memory;
    VkBuffer       buffer;
} VKUniformRing;

typedef struct {
    VkInstance       instance;
    VkPhysicalDevice         physical;
    VkPhysicalDeviceProperties device_props;
    VkDevice                 device;
    VkQueue          graphics_queue;
    VkQueue          present_queue;
    u32              graphics_family;
    u32              present_family;

    VkSurfaceKHR            surface;
    VkSwapchainKHR          swapchain;
    VkFormat                swap_format;
    VkExtent2D              swap_extent;
    VkImage                *swap_images;
    VkImageView            *swap_views;
    VkFramebuffer          *framebuffers;
    u32                     swap_count;

    VkRenderPass  render_pass;
    VkImage       depth_image;
    VkDeviceMemory depth_memory;
    VkImageView   depth_view;

    VkCommandPool   cmd_pool;
    VkCommandBuffer cmd_buffers[VK_MAX_FRAMES];

    VkSemaphore image_semaphores[VK_MAX_FRAMES];
    VkSemaphore *render_semaphores;
    VkFence     fences[VK_MAX_FRAMES];
    u32         current_frame;
    u32         image_index;
    bool        frame_started;

    VKUniformRing uniform_ring[VK_MAX_FRAMES];
    u8           *uniform_mapped[VK_MAX_FRAMES];
    usize         uniform_ring_size;
    usize         uniform_offset[VK_MAX_FRAMES];

    VkDescriptorPool        desc_pools[VK_MAX_FRAMES];
    VkDescriptorSetLayout    desc_layout;
    VkDescriptorSetLayout    texel_layout;
    VkDescriptorSetLayout    storage_layout;
    VkDescriptorSetLayout    storage_vtx_layout;

    Display *display;
    Window   window;

    VkPipeline current_pipeline;
    VKPipelineData *current_pipeline_data;
    bool       depth_lequal;
    bool       render_pass_active;
    VkRenderPass shadow_render_pass;
    VkImageView shadow_tex_view;

    shaderc_compiler_t shaderc_compiler;
} VKBackend;

/* ---- Helpers ---- */

static VKBackend *vk_backend(RHIDevice *dev) {
    return (VKBackend *)dev->backend_data;
}

static void vk_wait_frames(VKBackend *vk) {
    vkWaitForFences(vk->device, VK_MAX_FRAMES, vk->fences, VK_TRUE, UINT64_MAX);
}

static u32 vk_find_memory(VKBackend *vk, u32 type_filter, VkMemoryPropertyFlags props) {
    VkPhysicalDeviceMemoryProperties mem_props;
    vkGetPhysicalDeviceMemoryProperties(vk->physical, &mem_props);
    for (u32 i = 0; i < mem_props.memoryTypeCount; i++) {
        if ((type_filter & (1u << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props)
            return i;
    }
    return UINT32_MAX;
}


static VkShaderModule vk_compile_glsl(VKBackend *vk, const char *source, usize len, bool is_fragment) {
    shaderc_compile_options_t opts = shaderc_compile_options_initialize();
    shaderc_compile_options_set_target_env(opts, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
    shaderc_compile_options_set_target_spirv(opts, shaderc_spirv_version_1_5);

    shaderc_shader_kind kind = is_fragment ? shaderc_fragment_shader : shaderc_vertex_shader;
    shaderc_compilation_result_t result = shaderc_compile_into_spv(
        vk->shaderc_compiler, source, len, kind, "shader.glsl", "main", opts);

    shaderc_compilation_status status = shaderc_result_get_compilation_status(result);
    if (status != shaderc_compilation_status_success) {
        LOG_FATAL("Vulkan shader compile error: %s", shaderc_result_get_error_message(result));
        shaderc_result_release(result);
        shaderc_compile_options_release(opts);
        return VK_NULL_HANDLE;
    }

    usize spv_size = shaderc_result_get_length(result);
    const u32 *spv_data = (const u32 *)shaderc_result_get_bytes(result);

    VkShaderModuleCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    ci.codeSize = spv_size;
    ci.pCode = spv_data;

    VkShaderModule module;
    VkResult res = vkCreateShaderModule(vk->device, &ci, NULL, &module);

    shaderc_result_release(result);
    shaderc_compile_options_release(opts);

    if (res != VK_SUCCESS) {
        LOG_FATAL("Failed to create shader module");
        return VK_NULL_HANDLE;
    }
    return module;
}

/* ---- Swapchain ---- */

static void vk_create_swapchain(VKBackend *vk, u32 w, u32 h) {
    VkSurfaceCapabilitiesKHR caps;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vk->physical, vk->surface, &caps);

    VkExtent2D extent;
    if (caps.currentExtent.width != UINT32_MAX) {
        extent = caps.currentExtent;
    } else {
        extent.width = w < caps.minImageExtent.width ? caps.minImageExtent.width : (w > caps.maxImageExtent.width ? caps.maxImageExtent.width : w);
        extent.height = h < caps.minImageExtent.height ? caps.minImageExtent.height : (h > caps.maxImageExtent.height ? caps.maxImageExtent.height : h);
    }
    vk->swap_extent = extent;

    u32 img_count = caps.minImageCount + 1;
    if (caps.maxImageCount > 0 && img_count > caps.maxImageCount) img_count = caps.maxImageCount;

    VkSwapchainCreateInfoKHR sci = {0};
    sci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    sci.surface = vk->surface;
    sci.minImageCount = img_count;
    sci.imageFormat = vk->swap_format;
    sci.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    sci.imageExtent = extent;
    sci.imageArrayLayers = 1;
    sci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    sci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    sci.preTransform = caps.currentTransform;
    sci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
    {
        u32 mode_count = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(vk->physical, vk->surface, &mode_count, NULL);
        VkPresentModeKHR *modes = calloc(mode_count, sizeof(VkPresentModeKHR));
        vkGetPhysicalDeviceSurfacePresentModesKHR(vk->physical, vk->surface, &mode_count, modes);
        for (u32 i = 0; i < mode_count; i++) {
            if (modes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                present_mode = VK_PRESENT_MODE_IMMEDIATE_KHR;
                break;
            }
        }
        free(modes);
    }
    sci.presentMode = present_mode;
    sci.clipped = VK_TRUE;
    sci.oldSwapchain = VK_NULL_HANDLE;

    VkResult res = vkCreateSwapchainKHR(vk->device, &sci, NULL, &vk->swapchain);
    if (res != VK_SUCCESS) {
        LOG_FATAL("Failed to create swapchain: %d", res);
        return;
    }

    vkGetSwapchainImagesKHR(vk->device, vk->swapchain, &vk->swap_count, NULL);
    vk->swap_images = calloc(vk->swap_count, sizeof(VkImage));
    vk->swap_views = calloc(vk->swap_count, sizeof(VkImageView));
    vkGetSwapchainImagesKHR(vk->device, vk->swapchain, &vk->swap_count, vk->swap_images);

    for (u32 i = 0; i < vk->swap_count; i++) {
        VkImageViewCreateInfo vci = {0};
        vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vci.image = vk->swap_images[i];
        vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        vci.format = vk->swap_format;
        vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        vci.subresourceRange.levelCount = 1;
        vci.subresourceRange.layerCount = 1;
        vkCreateImageView(vk->device, &vci, NULL, &vk->swap_views[i]);
    }

    vk->render_semaphores = calloc(vk->swap_count, sizeof(VkSemaphore));
    for (u32 i = 0; i < vk->swap_count; i++) {
        VkSemaphoreCreateInfo sci2 = {0};
        sci2.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        vkCreateSemaphore(vk->device, &sci2, NULL, &vk->render_semaphores[i]);
    }
}

static void vk_create_depth(VKBackend *vk) {
    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = VK_FORMAT_D32_SFLOAT;
    ci.extent.width = vk->swap_extent.width;
    ci.extent.height = vk->swap_extent.height;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    vkCreateImage(vk->device, &ci, NULL, &vk->depth_image);

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(vk->device, vk->depth_image, &mem_req);

    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mem_req.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits,
                                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(vk->device, &ai, NULL, &vk->depth_memory);
    vkBindImageMemory(vk->device, vk->depth_image, vk->depth_memory, 0);

    VkImageViewCreateInfo vci = {0};
    vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image = vk->depth_image;
    vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    vci.format = VK_FORMAT_D32_SFLOAT;
    vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    vci.subresourceRange.levelCount = 1;
    vci.subresourceRange.layerCount = 1;
    vkCreateImageView(vk->device, &vci, NULL, &vk->depth_view);
}

static void vk_create_framebuffers(VKBackend *vk) {
    vk->framebuffers = calloc(vk->swap_count, sizeof(VkFramebuffer));
    for (u32 i = 0; i < vk->swap_count; i++) {
        VkImageView attachments[2] = { vk->swap_views[i], vk->depth_view };
        VkFramebufferCreateInfo ci = {0};
        ci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        ci.renderPass = vk->render_pass;
        ci.attachmentCount = 2;
        ci.pAttachments = attachments;
        ci.width = vk->swap_extent.width;
        ci.height = vk->swap_extent.height;
        ci.layers = 1;
        vkCreateFramebuffer(vk->device, &ci, NULL, &vk->framebuffers[i]);
    }
}

static void vk_create_render_pass(VKBackend *vk) {
    VkAttachmentDescription attachments[2] = {0};

    attachments[0].format = vk->swap_format;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    attachments[1].format = VK_FORMAT_D32_SFLOAT;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference color_ref = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkAttachmentReference depth_ref = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

    VkSubpassDescription subpass = {0};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_ref;
    subpass.pDepthStencilAttachment = &depth_ref;

    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.srcAccessMask = 0;
    dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    ci.attachmentCount = 2;
    ci.pAttachments = attachments;
    ci.subpassCount = 1;
    ci.pSubpasses = &subpass;
    ci.dependencyCount = 1;
    ci.pDependencies = &dep;

    vkCreateRenderPass(vk->device, &ci, NULL, &vk->render_pass);
}

static void vk_cleanup_swapchain(VKBackend *vk) {
    if (vk->framebuffers) {
        for (u32 i = 0; i < vk->swap_count; i++)
            vkDestroyFramebuffer(vk->device, vk->framebuffers[i], NULL);
        free(vk->framebuffers);
        vk->framebuffers = NULL;
    }
    if (vk->depth_view) { vkDestroyImageView(vk->device, vk->depth_view, NULL); vk->depth_view = VK_NULL_HANDLE; }
    if (vk->depth_image) { vkDestroyImage(vk->device, vk->depth_image, NULL); vk->depth_image = VK_NULL_HANDLE; }
    if (vk->depth_memory) { vkFreeMemory(vk->device, vk->depth_memory, NULL); vk->depth_memory = VK_NULL_HANDLE; }
    if (vk->swap_views) {
        for (u32 i = 0; i < vk->swap_count; i++) vkDestroyImageView(vk->device, vk->swap_views[i], NULL);
        free(vk->swap_views);
        vk->swap_views = NULL;
    }
    if (vk->swap_images) { free(vk->swap_images); vk->swap_images = NULL; }
    if (vk->render_semaphores) {
        for (u32 i = 0; i < vk->swap_count; i++) vkDestroySemaphore(vk->device, vk->render_semaphores[i], NULL);
        free(vk->render_semaphores);
        vk->render_semaphores = NULL;
    }
    if (vk->swapchain) { vkDestroySwapchainKHR(vk->device, vk->swapchain, NULL); vk->swapchain = VK_NULL_HANDLE; }
}

static void vk_recreate_swapchain(VKBackend *vk, u32 w, u32 h) {
    vkDeviceWaitIdle(vk->device);
    vk_cleanup_swapchain(vk);
    vk_create_swapchain(vk, w, h);
    vk_create_depth(vk);
    vk_create_framebuffers(vk);
}

/* ---- Init/Shutdown ---- */

static bool vk_init(RHIDevice *dev, void *window_native, void *display_native, u32 w, u32 h) {
    VKBackend *vk = calloc(1, sizeof(VKBackend));
    if (!vk) return false;

    vk->display = (Display *)display_native;
    vk->window = (Window)(uintptr_t)window_native;
    vk->swap_format = VK_FORMAT_B8G8R8A8_SRGB;

    VkApplicationInfo app = {0};
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pApplicationName = "PureCEngine";
    app.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app.pEngineName = "PureCEngine";
    app.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app.apiVersion = VK_API_VERSION_1_2;

    const char *layers[] = { "VK_LAYER_KHRONOS_validation" };
    const char *extensions[] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
    };

    VkInstanceCreateInfo ici = {0};
    ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ici.pApplicationInfo = &app;
    ici.enabledExtensionCount = 2;
    ici.ppEnabledExtensionNames = extensions;
#ifdef NDEBUG
    ici.enabledLayerCount = 0;
#else
    {
        u32 layer_count = 0;
        vkEnumerateInstanceLayerProperties(&layer_count, NULL);
        VkLayerProperties *props = calloc(layer_count, sizeof(VkLayerProperties));
        vkEnumerateInstanceLayerProperties(&layer_count, props);
        bool found = false;
        for (u32 i = 0; i < layer_count; i++) {
            if (strcmp(props[i].layerName, "VK_LAYER_KHRONOS_validation") == 0) { found = true; break; }
        }
        free(props);
        if (found) {
            ici.enabledLayerCount = 1;
            ici.ppEnabledLayerNames = layers;
        }
    }
#endif

    if (vkCreateInstance(&ici, NULL, &vk->instance) != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create instance");
        free(vk);
        return false;
    }

    VkXlibSurfaceCreateInfoKHR sci = {0};
    sci.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    sci.dpy = vk->display;
    sci.window = vk->window;
    if (vkCreateXlibSurfaceKHR(vk->instance, &sci, NULL, &vk->surface) != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create surface");
        free(vk);
        return false;
    }

    u32 gpu_count = 0;
    vkEnumeratePhysicalDevices(vk->instance, &gpu_count, NULL);
    if (gpu_count == 0) { LOG_FATAL("Vulkan: no GPUs"); free(vk); return false; }
    VkPhysicalDevice *gpus = calloc(gpu_count, sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(vk->instance, &gpu_count, gpus);
    vk->physical = gpus[0];
    free(gpus);
    vkGetPhysicalDeviceProperties(vk->physical, &vk->device_props);
    LOG_INFO("Vulkan GPU: %s (push constants: %u bytes, UBO alignment: %lu)",
             vk->device_props.deviceName,
             vk->device_props.limits.maxPushConstantsSize,
             (unsigned long)vk->device_props.limits.minUniformBufferOffsetAlignment);

    u32 queue_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vk->physical, &queue_count, NULL);
    VkQueueFamilyProperties *queues = calloc(queue_count, sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(vk->physical, &queue_count, queues);
    vk->graphics_family = UINT32_MAX;
    vk->present_family = UINT32_MAX;
    for (u32 i = 0; i < queue_count; i++) {
        if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && vk->graphics_family == UINT32_MAX)
            vk->graphics_family = i;
        VkBool32 present = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(vk->physical, i, vk->surface, &present);
        if (present && vk->present_family == UINT32_MAX)
            vk->present_family = i;
    }
    free(queues);
    if (vk->graphics_family == UINT32_MAX || vk->present_family == UINT32_MAX) {
        LOG_FATAL("Vulkan: no suitable queue family");
        free(vk);
        return false;
    }

    f32 queue_priority = 1.0f;
    VkDeviceQueueCreateInfo qci = {0};
    qci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    qci.queueFamilyIndex = vk->graphics_family;
    qci.queueCount = 1;
    qci.pQueuePriorities = &queue_priority;

    const char *dev_extensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    VkDeviceCreateInfo dci = {0};
    dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    dci.queueCreateInfoCount = 1;
    dci.pQueueCreateInfos = &qci;
    dci.enabledExtensionCount = 1;
    dci.ppEnabledExtensionNames = dev_extensions;

    if (vkCreateDevice(vk->physical, &dci, NULL, &vk->device) != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create device");
        free(vk);
        return false;
    }

    vkGetDeviceQueue(vk->device, vk->graphics_family, 0, &vk->graphics_queue);
    vkGetDeviceQueue(vk->device, vk->present_family, 0, &vk->present_queue);

    vk_create_swapchain(vk, w, h);
    vk_create_render_pass(vk);
    vk_create_depth(vk);
    vk_create_framebuffers(vk);

    VkCommandPoolCreateInfo cpci = {0};
    cpci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cpci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    cpci.queueFamilyIndex = vk->graphics_family;
    vkCreateCommandPool(vk->device, &cpci, NULL, &vk->cmd_pool);

    VkCommandBufferAllocateInfo cbai = {0};
    cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cbai.commandPool = vk->cmd_pool;
    cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cbai.commandBufferCount = VK_MAX_FRAMES;
    vkAllocateCommandBuffers(vk->device, &cbai, vk->cmd_buffers);

    vk->uniform_ring_size = 4 * 1024 * 1024;
    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        VkBufferCreateInfo bci = {0};
        bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bci.size = vk->uniform_ring_size;
        bci.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        vkCreateBuffer(vk->device, &bci, NULL, &vk->uniform_ring[i].buffer);

        VkMemoryRequirements mem_req;
        vkGetBufferMemoryRequirements(vk->device, vk->uniform_ring[i].buffer, &mem_req);

        VkMemoryAllocateInfo mai = {0};
        mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mai.allocationSize = mem_req.size;
        mai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        vkAllocateMemory(vk->device, &mai, NULL, &vk->uniform_ring[i].memory);
        vkBindBufferMemory(vk->device, vk->uniform_ring[i].buffer, vk->uniform_ring[i].memory, 0);
        vkMapMemory(vk->device, vk->uniform_ring[i].memory, 0, vk->uniform_ring_size, 0, (void **)&vk->uniform_mapped[i]);
        vk->uniform_offset[i] = 0;
    }

    {
        VkDescriptorSetLayoutBinding binds[6];
        memset(binds, 0, sizeof(binds));
        for (int i = 0; i < 6; i++) {
            binds[i].binding = i;
            binds[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            binds[i].descriptorCount = 1;
            binds[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
        }

        VkDescriptorSetLayoutCreateInfo dli = {0};
        dli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        dli.bindingCount = 6;
        dli.pBindings = binds;
        vkCreateDescriptorSetLayout(vk->device, &dli, NULL, &vk->desc_layout);
    }

    {
        VkDescriptorSetLayoutBinding texel_binds[2] = {0};
        texel_binds[0].binding = 0;
        texel_binds[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        texel_binds[0].descriptorCount = 1;
        texel_binds[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        texel_binds[1].binding = 1;
        texel_binds[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        texel_binds[1].descriptorCount = 1;
        texel_binds[1].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

        VkDescriptorSetLayoutCreateInfo tli = {0};
        tli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        tli.bindingCount = 2;
        tli.pBindings = texel_binds;
        vkCreateDescriptorSetLayout(vk->device, &tli, NULL, &vk->texel_layout);
    }

    {
        VkDescriptorSetLayoutBinding storage_binds[4];
        memset(storage_binds, 0, sizeof(storage_binds));
        for (int i = 0; i < 4; i++) {
            storage_binds[i].binding = i;
            storage_binds[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            storage_binds[i].descriptorCount = 1;
            storage_binds[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
        }

        VkDescriptorSetLayoutCreateInfo sli = {0};
        sli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        sli.bindingCount = 4;
        sli.pBindings = storage_binds;
        vkCreateDescriptorSetLayout(vk->device, &sli, NULL, &vk->storage_layout);
    }

    {
        VkDescriptorSetLayoutBinding svb[4];
        memset(svb, 0, sizeof(svb));
        for (int i = 0; i < 4; i++) {
            svb[i].binding = i;
            svb[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            svb[i].descriptorCount = 1;
            svb[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT | VK_SHADER_STAGE_VERTEX_BIT;
        }
        VkDescriptorSetLayoutCreateInfo svli = {0};
        svli.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        svli.bindingCount = 4;
        svli.pBindings = svb;
        vkCreateDescriptorSetLayout(vk->device, &svli, NULL, &vk->storage_vtx_layout);
    }

    {
        VkDescriptorPoolSize pool_sizes[3] = {0};
        pool_sizes[0].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        pool_sizes[0].descriptorCount = 1024;
        pool_sizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        pool_sizes[1].descriptorCount = 1024;
        pool_sizes[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        pool_sizes[2].descriptorCount = 256;

        VkDescriptorPoolCreateInfo dpi = {0};
        dpi.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        dpi.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        dpi.maxSets = 2048;
        dpi.poolSizeCount = 3;
        dpi.pPoolSizes = pool_sizes;
        for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
            vkCreateDescriptorPool(vk->device, &dpi, NULL, &vk->desc_pools[i]);
        }
    }

    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        VkSemaphoreCreateInfo sci2 = {0};
        sci2.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        vkCreateSemaphore(vk->device, &sci2, NULL, &vk->image_semaphores[i]);
        VkFenceCreateInfo fci = {0};
        fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fci.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        vkCreateFence(vk->device, &fci, NULL, &vk->fences[i]);
    }

    dev->backend_data = vk;
    dev->width = w;
    dev->height = h;

    vk->shaderc_compiler = shaderc_compiler_initialize();

    LOG_INFO("Vulkan initialized");
    return true;
}

static void vk_shutdown(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    if (!vk) return;
    vkDeviceWaitIdle(vk->device);

    if (vk->shaderc_compiler) {
        shaderc_compiler_release(vk->shaderc_compiler);
        vk->shaderc_compiler = NULL;
    }

    for (u32 i = 0; i < VK_MAX_FRAMES; i++) {
        vkDestroySemaphore(vk->device, vk->image_semaphores[i], NULL);
        vkDestroyFence(vk->device, vk->fences[i], NULL);
        vkUnmapMemory(vk->device, vk->uniform_ring[i].memory);
        vkDestroyBuffer(vk->device, vk->uniform_ring[i].buffer, NULL);
        vkFreeMemory(vk->device, vk->uniform_ring[i].memory, NULL);
    }

    vkFreeCommandBuffers(vk->device, vk->cmd_pool, VK_MAX_FRAMES, vk->cmd_buffers);
    vkDestroyCommandPool(vk->device, vk->cmd_pool, NULL);
    for (u32 i = 0; i < VK_MAX_FRAMES; i++)
        vkDestroyDescriptorPool(vk->device, vk->desc_pools[i], NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->desc_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->texel_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->storage_layout, NULL);
    vkDestroyDescriptorSetLayout(vk->device, vk->storage_vtx_layout, NULL);
    vk_cleanup_swapchain(vk);
    if (vk->render_pass) vkDestroyRenderPass(vk->device, vk->render_pass, NULL);
    vkDestroyDevice(vk->device, NULL);
    vkDestroySurfaceKHR(vk->instance, vk->surface, NULL);
    vkDestroyInstance(vk->instance, NULL);
    free(vk);
    dev->backend_data = NULL;
}

/* ---- RHI Implementation (overrides GL versions via conditional compilation) ---- */

static VkFormat vk_format_from_rhi(RHIFormat fmt) {
    switch (fmt) {
    case RHI_FORMAT_R8G8B8A8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM;
    case RHI_FORMAT_B8G8R8A8_UNORM: return VK_FORMAT_B8G8R8A8_UNORM;
    case RHI_FORMAT_R16G16B16A16_SFLOAT: return VK_FORMAT_R16G16B16A16_SFLOAT;
    case RHI_FORMAT_D32_FLOAT:      return VK_FORMAT_D32_SFLOAT;
    default: return VK_FORMAT_R8G8B8A8_UNORM;
    }
}

RHIDevice *rhi_device_create(RHIBackend backend, void *window_native, void *display_native, u32 w, u32 h) {
    (void)backend;
    RHIDevice *dev = calloc(1, sizeof(RHIDevice));
    if (!dev) return NULL;
    if (!vk_init(dev, window_native, display_native, w, h)) {
        free(dev);
        return NULL;
    }
    g_current_device = dev;
    return dev;
}

void rhi_device_destroy(RHIDevice *dev) {
    if (!dev) return;
    VKBackend *vk = vk_backend(dev);
    vkDeviceWaitIdle(vk->device);

    for (u32 i = 0; i < RHI_MAX_RESOURCES; i++) {
        if (!dev->slots[i].alive) continue;
        switch (dev->slots[i].type) {
        case RHI_RES_SHADER: {
            VKShaderData *sd = (VKShaderData *)dev->slots[i].ptr;
            if (sd) { vkDestroyShaderModule(vk->device, sd->module, NULL); free(sd); }
            break;
        }
        case RHI_RES_PIPELINE: {
            VKPipelineData *pd = (VKPipelineData *)dev->slots[i].ptr;
            if (pd) {
                vkDestroyPipeline(vk->device, pd->pipeline, NULL);
                vkDestroyPipelineLayout(vk->device, pd->layout, NULL);
                free(pd);
            }
            break;
        }
        case RHI_RES_BUFFER: {
            VKBufferData *bd = (VKBufferData *)dev->slots[i].ptr;
            if (bd) { vkDestroyBuffer(vk->device, bd->buffer, NULL); vkFreeMemory(vk->device, bd->memory, NULL); free(bd); }
            break;
        }
        case RHI_RES_TEXTURE: {
            VKTextureData *td = (VKTextureData *)dev->slots[i].ptr;
            if (td) {
                vkDestroyImageView(vk->device, td->view, NULL);
                vkDestroyImage(vk->device, td->image, NULL);
                vkFreeMemory(vk->device, td->memory, NULL);
                free(td);
            }
            break;
        }
        case RHI_RES_SAMPLER: {
            VKSamplerData *sd = (VKSamplerData *)dev->slots[i].ptr;
            if (sd) { vkDestroySampler(vk->device, sd->sampler, NULL); free(sd); }
            break;
        }
        default:
            free(dev->slots[i].ptr);
            break;
        }
    }

    vk_shutdown(dev);
    if (g_current_device == dev) g_current_device = NULL;
    free(dev);
}

void rhi_device_resize(RHIDevice *dev, u32 w, u32 h) {
    VKBackend *vk = vk_backend(dev);
    vk_recreate_swapchain(vk, w, h);
    dev->width = w;
    dev->height = h;
}

RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    g_current_device = dev;

    vkWaitForFences(vk->device, 1, &vk->fences[vk->current_frame], VK_TRUE, UINT64_MAX);
    vkResetFences(vk->device, 1, &vk->fences[vk->current_frame]);
    vkResetDescriptorPool(vk->device, vk->desc_pools[vk->current_frame], 0);

    VkResult res = vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
        vk->image_semaphores[vk->current_frame], VK_NULL_HANDLE, &vk->image_index);
    if (res == VK_ERROR_OUT_OF_DATE_KHR) {
        vk_recreate_swapchain(vk, dev->width, dev->height);
        res = vkAcquireNextImageKHR(vk->device, vk->swapchain, UINT64_MAX,
            vk->image_semaphores[vk->current_frame], VK_NULL_HANDLE, &vk->image_index);
        if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
            vk->frame_started = false;
            return (RHICmdBuffer *)vk;
        }
    }
    /* VK_SUBOPTIMAL_KHR is a success — swapchain rebuild deferred to rhi_present */

    vkResetCommandBuffer(vk->cmd_buffers[vk->current_frame], 0);

    VkCommandBufferBeginInfo bi = {0};
    bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(vk->cmd_buffers[vk->current_frame], &bi);

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->render_pass;
    rpi.framebuffer = vk->framebuffers[vk->image_index];
    rpi.renderArea.offset = (VkOffset2D){0, 0};
    rpi.renderArea.extent = vk->swap_extent;

    VkClearValue clears[2] = {0};
    clears[0].color = (VkClearColorValue){{0.2f, 0.25f, 0.35f, 1.0f}};
    clears[1].depthStencil = (VkClearDepthStencilValue){1.0f, 0};
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;

    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;

    VkViewport vp = {0, 0, (f32)vk->swap_extent.width, (f32)vk->swap_extent.height, 0.0f, 1.0f};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, vk->swap_extent};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);

    vk->frame_started = true;
    vk->current_pipeline = VK_NULL_HANDLE;
    vk->depth_lequal = false;

    vk->uniform_offset[vk->current_frame] = 0;

    return (RHICmdBuffer *)vk;
}

void rhi_frame_end(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);
    if (!vk->frame_started) return;

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }
    vkEndCommandBuffer(vk->cmd_buffers[vk->current_frame]);

    VkSubmitInfo si = {0};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    si.waitSemaphoreCount = 1;
    si.pWaitSemaphores = &vk->image_semaphores[vk->current_frame];
    si.pWaitDstStageMask = &wait_stage;
    si.commandBufferCount = 1;
    si.pCommandBuffers = &vk->cmd_buffers[vk->current_frame];
    si.signalSemaphoreCount = 1;
    si.pSignalSemaphores = &vk->render_semaphores[vk->image_index];

    vkQueueSubmit(vk->graphics_queue, 1, &si, vk->fences[vk->current_frame]);
    vk->frame_started = false;
}

void rhi_present(RHIDevice *dev) {
    VKBackend *vk = vk_backend(dev);

    VkPresentInfoKHR pi = {0};
    pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pi.waitSemaphoreCount = 1;
    pi.pWaitSemaphores = &vk->render_semaphores[vk->image_index];
    pi.swapchainCount = 1;
    pi.pSwapchains = &vk->swapchain;
    pi.pImageIndices = &vk->image_index;

    VkResult res = vkQueuePresentKHR(vk->present_queue, &pi);
    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR) {
        vk_recreate_swapchain(vk, dev->width, dev->height);
    }

    vk->current_frame = (vk->current_frame + 1) % VK_MAX_FRAMES;
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment) {
    VKBackend *vk = vk_backend(dev);
    VkShaderModule mod = vk_compile_glsl(vk, source, len, is_fragment);
    if (mod == VK_NULL_HANDLE) return RHI_HANDLE_NULL;

    u32 idx = rhi_alloc_slot(dev);
    VKShaderData *sd = calloc(1, sizeof(VKShaderData));
    sd->module = mod;
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    VKBackend *vk = vk_backend(dev);
    VKShaderData *sd = (VKShaderData *)rhi_get_resource(dev, shader);
    if (!sd) return;
    vkDestroyShaderModule(vk->device, sd->module, NULL);
    free(sd);
    rhi_free_slot(dev, shader);
}

RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len) {
    VKBackend *vk = vk_backend(dev);
    shaderc_compile_options_t opts = shaderc_compile_options_initialize();
    shaderc_compile_options_set_target_env(opts, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
    shaderc_compile_options_set_target_spirv(opts, shaderc_spirv_version_1_5);
    shaderc_compilation_result_t result = shaderc_compile_into_spv(
        vk->shaderc_compiler, source, len, shaderc_compute_shader, "compute.glsl", "main", opts);
    shaderc_compilation_status status = shaderc_result_get_compilation_status(result);
    if (status != shaderc_compilation_status_success) {
        LOG_FATAL("Vulkan compute shader compile error: %s", shaderc_result_get_error_message(result));
        shaderc_result_release(result);
        shaderc_compile_options_release(opts);
        return RHI_HANDLE_NULL;
    }
    usize spv_size = shaderc_result_get_length(result);
    const u32 *spv_data = (const u32 *)shaderc_result_get_bytes(result);
    VkShaderModuleCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    ci.codeSize = spv_size;
    ci.pCode = spv_data;
    VkShaderModule mod;
    if (vkCreateShaderModule(vk->device, &ci, NULL, &mod) != VK_SUCCESS) {
        shaderc_result_release(result);
        shaderc_compile_options_release(opts);
        return RHI_HANDLE_NULL;
    }
    shaderc_result_release(result);
    shaderc_compile_options_release(opts);
    u32 idx = rhi_alloc_slot(dev);
    VKShaderData *sd = calloc(1, sizeof(VKShaderData));
    sd->module = mod;
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

static VkVertexInputBindingDescription vk_binding(u32 stride) {
    VkVertexInputBindingDescription d = {0};
    d.binding = 0;
    d.stride = stride;
    d.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return d;
}

static VkVertexInputAttributeDescription vk_attr(u32 location, u32 offset, VkFormat fmt) {
    VkVertexInputAttributeDescription d = {0};
    d.location = location;
    d.binding = 0;
    d.format = fmt;
    d.offset = offset;
    return d;
}

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    VKBackend *vk = vk_backend(dev);

    if (desc->is_compute) {
        VKShaderData *cs_data = (VKShaderData *)rhi_get_resource(dev, desc->frag);
        if (!cs_data) return RHI_HANDLE_NULL;

        VkPipelineShaderStageCreateInfo stage = {0};
        stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        stage.module = cs_data->module;
        stage.pName = "main";

        VkDescriptorSetLayout set_layouts[1];
        set_layouts[0] = vk->storage_layout;

        VkPushConstantRange push_range = {0};
        push_range.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
        push_range.offset = 0;
        push_range.size = 128;

        VkPipelineLayoutCreateInfo lci = {0};
        lci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        lci.setLayoutCount = 1;
        lci.pSetLayouts = set_layouts;
        lci.pushConstantRangeCount = 1;
        lci.pPushConstantRanges = &push_range;

        VkPipelineLayout layout;
        vkCreatePipelineLayout(vk->device, &lci, NULL, &layout);

        VkComputePipelineCreateInfo cpci = {0};
        cpci.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        cpci.stage = stage;
        cpci.layout = layout;

        VkPipeline pipeline;
        VkResult res = vkCreateComputePipelines(vk->device, VK_NULL_HANDLE, 1, &cpci, NULL, &pipeline);
        if (res != VK_SUCCESS) {
            LOG_FATAL("Vulkan: failed to create compute pipeline: %d", res);
            vkDestroyPipelineLayout(vk->device, layout, NULL);
            return RHI_HANDLE_NULL;
        }

        u32 idx = rhi_alloc_slot(dev);
        VKPipelineData *pd = calloc(1, sizeof(VKPipelineData));
        pd->layout = layout;
        pd->pipeline = pipeline;
        pd->no_vertex_input = true;
        pd->uses_texel_buffer = false;
        pd->is_compute = true;
        dev->slots[idx].ptr = pd;
        dev->slots[idx].type = RHI_RES_PIPELINE;
        return rhi_make_handle(idx, dev->slots[idx].generation);
    }

    VKShaderData *vs_data = (VKShaderData *)rhi_get_resource(dev, desc->vert);
    VKShaderData *fs_data = (VKShaderData *)rhi_get_resource(dev, desc->frag);
    if (!vs_data || !fs_data) return RHI_HANDLE_NULL;

    VkPipelineShaderStageCreateInfo stages[2] = {0};
    stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    stages[0].module = vs_data->module;
    stages[0].pName = "main";
    stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    stages[1].module = fs_data->module;
    stages[1].pName = "main";

    VkPipelineVertexInputStateCreateInfo vertex_input = {0};
    vertex_input.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    VkVertexInputBindingDescription binding;
    VkVertexInputAttributeDescription attrs[5];
    u32 stride = desc->vertex_stride;

    if (desc->no_vertex_input) {
        stride = 0;
    } else if (desc->font_vertex) {
        stride = 32;
        binding = vk_binding(32);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32_SFLOAT);
        attrs[1] = vk_attr(1, 2 * sizeof(f32), VK_FORMAT_R32G32_SFLOAT);
        attrs[2] = vk_attr(2, 4 * sizeof(f32), VK_FORMAT_R32G32B32A32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 3;
        vertex_input.pVertexAttributeDescriptions = attrs;
    } else if (desc->skinned_vertex) {
        stride = 64;
        binding = vk_binding(64);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32B32_SFLOAT);
        attrs[1] = vk_attr(1, 3 * sizeof(f32), VK_FORMAT_R32G32B32_SFLOAT);
        attrs[2] = vk_attr(2, 6 * sizeof(f32), VK_FORMAT_R32G32_SFLOAT);
        attrs[3] = vk_attr(3, 8 * sizeof(f32), VK_FORMAT_R32G32B32A32_UINT);
        attrs[4] = vk_attr(4, 8 * sizeof(f32) + 4 * sizeof(u32), VK_FORMAT_R32G32B32A32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 5;
        vertex_input.pVertexAttributeDescriptions = attrs;
    } else if (stride == 12) {
        binding = vk_binding(12);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32B32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 1;
        vertex_input.pVertexAttributeDescriptions = attrs;
    } else {
        stride = stride > 0 ? stride : 32;
        binding = vk_binding(stride);
        attrs[0] = vk_attr(0, 0, VK_FORMAT_R32G32B32_SFLOAT);
        attrs[1] = vk_attr(1, 3 * sizeof(f32), VK_FORMAT_R32G32B32_SFLOAT);
        attrs[2] = vk_attr(2, 6 * sizeof(f32), VK_FORMAT_R32G32_SFLOAT);
        vertex_input.vertexBindingDescriptionCount = 1;
        vertex_input.pVertexBindingDescriptions = &binding;
        vertex_input.vertexAttributeDescriptionCount = 3;
        vertex_input.pVertexAttributeDescriptions = attrs;
    }

    VkPipelineInputAssemblyStateCreateInfo assembly = {0};
    assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    assembly.primitiveRestartEnable = VK_FALSE;

    VkPipelineViewportStateCreateInfo viewport = {0};
    viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport.viewportCount = 1;
    viewport.scissorCount = 1;

    VkPipelineRasterizationStateCreateInfo raster = {0};
    raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster.depthClampEnable = VK_FALSE;
    raster.rasterizerDiscardEnable = VK_FALSE;
    raster.polygonMode = VK_POLYGON_MODE_FILL;
    raster.lineWidth = 1.0f;
    raster.cullMode = (desc->no_vertex_input || desc->disable_culling) ? VK_CULL_MODE_NONE : VK_CULL_MODE_BACK_BIT;
    raster.frontFace = VK_FRONT_FACE_CLOCKWISE;
    raster.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo msaa = {0};
    msaa.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    msaa.sampleShadingEnable = VK_FALSE;
    msaa.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState blend_att = {0};
    blend_att.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                               VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    if (desc->alpha_blend) {
        blend_att.blendEnable = VK_TRUE;
        blend_att.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        blend_att.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        blend_att.colorBlendOp = VK_BLEND_OP_ADD;
        blend_att.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
        blend_att.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        blend_att.alphaBlendOp = VK_BLEND_OP_ADD;
    } else {
        blend_att.blendEnable = VK_FALSE;
    }

    VkPipelineColorBlendStateCreateInfo blend = {0};
    blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blend.logicOpEnable = VK_FALSE;
    blend.attachmentCount = 1;
    blend.pAttachments = &blend_att;

    VkPipelineDepthStencilStateCreateInfo depth = {0};
    depth.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depth.depthTestEnable = VK_TRUE;
    depth.depthWriteEnable = desc->depth_write_disable ? VK_FALSE : VK_TRUE;
    depth.depthCompareOp = desc->depth_compare_lequal ? VK_COMPARE_OP_LESS_OR_EQUAL : VK_COMPARE_OP_LESS;
    depth.depthBoundsTestEnable = VK_FALSE;
    depth.stencilTestEnable = VK_FALSE;

    VkDynamicState dynamic_states[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
    };
    VkPipelineDynamicStateCreateInfo dynamic = {0};
    dynamic.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic.dynamicStateCount = 2;
    dynamic.pDynamicStates = dynamic_states;

    VkPushConstantRange push_range = {0};
    push_range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    push_range.offset = 0;
    push_range.size = 256;
    if (push_range.size > vk->device_props.limits.maxPushConstantsSize) {
        LOG_ERROR("Push constant range %u exceeds device max %u",
                  push_range.size, vk->device_props.limits.maxPushConstantsSize);
        push_range.size = vk->device_props.limits.maxPushConstantsSize;
    }

    VkPipelineLayoutCreateInfo lci = {0};
    lci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    VkDescriptorSetLayout set_layouts[2];
    u32 set_count = 0;
    if (desc->uses_textures) {
        set_layouts[set_count++] = vk->desc_layout;
    }
    if (desc->uses_texel_buffer) {
        set_layouts[set_count++] = vk->texel_layout;
    }
    if (desc->uses_storage) {
        set_layouts[set_count++] = vk->storage_vtx_layout;
    }
    if (set_count > 0) {
        lci.setLayoutCount = set_count;
        lci.pSetLayouts = set_layouts;
    }
    lci.pushConstantRangeCount = 1;
    lci.pPushConstantRanges = &push_range;

    VkPipelineLayout layout;
    vkCreatePipelineLayout(vk->device, &lci, NULL, &layout);

    VkGraphicsPipelineCreateInfo pci = {0};
    pci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pci.stageCount = 2;
    pci.pStages = stages;
    pci.pVertexInputState = &vertex_input;
    pci.pInputAssemblyState = &assembly;
    pci.pViewportState = &viewport;
    pci.pRasterizationState = &raster;
    pci.pMultisampleState = &msaa;
    pci.pDepthStencilState = &depth;
    pci.pColorBlendState = &blend;
    pci.pDynamicState = &dynamic;
    pci.layout = layout;
    pci.renderPass = desc->is_shadow_depth ? vk->shadow_render_pass : vk->render_pass;
    pci.subpass = 0;

    VkPipeline pipeline;
    VkResult res = vkCreateGraphicsPipelines(vk->device, VK_NULL_HANDLE, 1, &pci, NULL, &pipeline);
    if (res != VK_SUCCESS) {
        LOG_FATAL("Vulkan: failed to create pipeline: %d", res);
        vkDestroyPipelineLayout(vk->device, layout, NULL);
        return RHI_HANDLE_NULL;
    }

    u32 idx = rhi_alloc_slot(dev);
    VKPipelineData *pd = calloc(1, sizeof(VKPipelineData));
    pd->layout = layout;
    pd->pipeline = pipeline;
    pd->vertex_stride = stride;
    pd->no_vertex_input = desc->no_vertex_input;
    pd->uses_texel_buffer = desc->uses_texel_buffer;
    pd->is_instanced = desc->is_instanced;
    pd->uses_storage = desc->uses_storage;
    dev->slots[idx].ptr = pd;
    dev->slots[idx].type = RHI_RES_PIPELINE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    VKBackend *vk = vk_backend(dev);
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource(dev, pipe);
    if (!pd) return;
    vk_wait_frames(vk);
    vkDestroyPipeline(vk->device, pd->pipeline, NULL);
    vkDestroyPipelineLayout(vk->device, pd->layout, NULL);
    free(pd);
    rhi_free_slot(dev, pipe);
}

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    VKBackend *vk = vk_backend(dev);

    VkBufferCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    ci.size = desc->size;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    bool is_texel = (desc->usage & RHI_BUFFER_USAGE_TEXEL) != 0;
    if (desc->usage & RHI_BUFFER_USAGE_VERTEX)      ci.usage |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    if (desc->usage & RHI_BUFFER_USAGE_INDEX)        ci.usage |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    if (desc->usage & RHI_BUFFER_USAGE_UNIFORM)      ci.usage |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    if (desc->usage & RHI_BUFFER_USAGE_STORAGE)      ci.usage |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    if (is_texel)                                     ci.usage |= VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;

    VkBuffer buf;
    vkCreateBuffer(vk->device, &ci, NULL, &buf);

    VkMemoryRequirements mem_req;
    vkGetBufferMemoryRequirements(vk->device, buf, &mem_req);

    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mem_req.size;

    VkMemoryPropertyFlags props = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits, props);

    VkDeviceMemory mem;
    vkAllocateMemory(vk->device, &ai, NULL, &mem);
    vkBindBufferMemory(vk->device, buf, mem, 0);

    if (desc->initial_data) {
        void *mapped;
        vkMapMemory(vk->device, mem, 0, desc->size, 0, &mapped);
        memcpy(mapped, desc->initial_data, desc->size);
        vkUnmapMemory(vk->device, mem);
    }

    VkBufferView texel_view = VK_NULL_HANDLE;
    if (is_texel) {
        VkBufferViewCreateInfo bvci = {0};
        bvci.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
        bvci.buffer = buf;
        bvci.format = VK_FORMAT_R32G32B32A32_SFLOAT;
        bvci.range = desc->size;
        vkCreateBufferView(vk->device, &bvci, NULL, &texel_view);
    }

    u32 idx = rhi_alloc_slot(dev);
    VKBufferData *bd = calloc(1, sizeof(VKBufferData));
    bd->buffer = buf;
    bd->memory = mem;
    bd->size = desc->size;
    bd->texel_view = texel_view;
    bd->is_texel = is_texel;
    dev->slots[idx].ptr = bd;
    dev->slots[idx].type = RHI_RES_BUFFER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    vk_wait_frames(vk);
    if (bd->mapped) vkUnmapMemory(vk->device, bd->memory);
    if (bd->texel_view != VK_NULL_HANDLE) vkDestroyBufferView(vk->device, bd->texel_view, NULL);
    vkDestroyBuffer(vk->device, bd->buffer, NULL);
    vkFreeMemory(vk->device, bd->memory, NULL);
    free(bd);
    rhi_free_slot(dev, buf);
}

RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    VKBackend *vk = vk_backend(dev);
    VkFormat fmt = vk_format_from_rhi(desc->format);

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = fmt;
    ci.extent.width = desc->width;
    ci.extent.height = desc->height;
    ci.extent.depth = 1;
    ci.mipLevels = desc->mip_levels > 0 ? desc->mip_levels : 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    VkImage image;
    vkCreateImage(vk->device, &ci, NULL, &image);

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(vk->device, image, &mem_req);

    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mem_req.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mem_req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    VkDeviceMemory mem;
    vkAllocateMemory(vk->device, &ai, NULL, &mem);
    vkBindImageMemory(vk->device, image, mem, 0);

    VkImageViewCreateInfo vci = {0};
    vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image = image;
    vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    vci.format = fmt;
    vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    vci.subresourceRange.levelCount = 1;
    vci.subresourceRange.layerCount = 1;
    VkImageView view;
    vkCreateImageView(vk->device, &vci, NULL, &view);

    if (desc->data) {
        VkBuffer staging;
        VkDeviceMemory staging_mem;
        VkDeviceSize data_size = desc->width * desc->height * 4;

        VkBufferCreateInfo bci = {0};
        bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bci.size = data_size;
        bci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        vkCreateBuffer(vk->device, &bci, NULL, &staging);

        VkMemoryRequirements smr;
        vkGetBufferMemoryRequirements(vk->device, staging, &smr);
        VkMemoryAllocateInfo smi = {0};
        smi.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        smi.allocationSize = smr.size;
        smi.memoryTypeIndex = vk_find_memory(vk, smr.memoryTypeBits,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        vkAllocateMemory(vk->device, &smi, NULL, &staging_mem);
        vkBindBufferMemory(vk->device, staging, staging_mem, 0);

        void *mapped;
        vkMapMemory(vk->device, staging_mem, 0, data_size, 0, &mapped);
        memcpy(mapped, desc->data, data_size);
        vkUnmapMemory(vk->device, staging_mem);

        VkCommandBufferAllocateInfo cbai = {0};
        cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cbai.commandPool = vk->cmd_pool;
        cbai.commandBufferCount = 1;
        VkCommandBuffer tmp_cb;
        vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb);
        VkCommandBufferBeginInfo cbi = {0};
        cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer(tmp_cb, &cbi);

        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.layerCount = 1;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);

        VkBufferImageCopy region = {0};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageExtent = (VkExtent3D){desc->width, desc->height, 1};
        vkCmdCopyBufferToImage(tmp_cb, staging, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        VkImageMemoryBarrier barrier2 = {0};
        barrier2.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier2.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier2.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier2.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier2.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier2.image = image;
        barrier2.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier2.subresourceRange.levelCount = 1;
        barrier2.subresourceRange.layerCount = 1;
        barrier2.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier2.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_TRANSFER_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier2);

        vkEndCommandBuffer(tmp_cb);

        VkFence upload_fence;
        VkFenceCreateInfo fci = {0};
        fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        vkCreateFence(vk->device, &fci, NULL, &upload_fence);

        VkSubmitInfo si = {0};
        si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        si.commandBufferCount = 1;
        si.pCommandBuffers = &tmp_cb;
        vkQueueSubmit(vk->graphics_queue, 1, &si, upload_fence);
        vkWaitForFences(vk->device, 1, &upload_fence, VK_TRUE, UINT64_MAX);

        vkDestroyFence(vk->device, upload_fence, NULL);
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
        vkDestroyBuffer(vk->device, staging, NULL);
        vkFreeMemory(vk->device, staging_mem, NULL);
    } else {
        VkCommandBufferAllocateInfo cbai = {0};
        cbai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cbai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cbai.commandPool = vk->cmd_pool;
        cbai.commandBufferCount = 1;
        VkCommandBuffer tmp_cb;
        vkAllocateCommandBuffers(vk->device, &cbai, &tmp_cb);
        VkCommandBufferBeginInfo cbi = {0};
        cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        cbi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer(tmp_cb, &cbi);

        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.layerCount = 1;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(tmp_cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);
        vkEndCommandBuffer(tmp_cb);

        VkFence layout_fence;
        VkFenceCreateInfo fci2 = {0};
        fci2.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        vkCreateFence(vk->device, &fci2, NULL, &layout_fence);

        VkSubmitInfo si = {0};
        si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        si.commandBufferCount = 1;
        si.pCommandBuffers = &tmp_cb;
        vkQueueSubmit(vk->graphics_queue, 1, &si, layout_fence);
        vkWaitForFences(vk->device, 1, &layout_fence, VK_TRUE, UINT64_MAX);

        vkDestroyFence(vk->device, layout_fence, NULL);
        vkFreeCommandBuffers(vk->device, vk->cmd_pool, 1, &tmp_cb);
    }

    u32 idx = rhi_alloc_slot(dev);
    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    td->image = image;
    td->view = view;
    td->memory = mem;
    td->width = desc->width;
    td->height = desc->height;
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    VKBackend *vk = vk_backend(dev);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(dev, tex);
    if (!td) return;
    vk_wait_frames(vk);
    vkDestroyImageView(vk->device, td->view, NULL);
    vkDestroyImage(vk->device, td->image, NULL);
    vkFreeMemory(vk->device, td->memory, NULL);
    free(td);
    rhi_free_slot(dev, tex);
}

static VkFilter vk_filter(RHIFilter f) {
    return f == RHI_FILTER_LINEAR ? VK_FILTER_LINEAR : VK_FILTER_NEAREST;
}

static VkSamplerAddressMode vk_wrap(RHIWrapMode w) {
    return w == RHI_WRAP_CLAMP_TO_EDGE ? VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE : VK_SAMPLER_ADDRESS_MODE_REPEAT;
}

RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    VKBackend *vk = vk_backend(dev);

    VkSamplerCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    ci.magFilter = vk_filter(desc->mag_filter);
    ci.minFilter = vk_filter(desc->min_filter);
    ci.addressModeU = vk_wrap(desc->wrap_u);
    ci.addressModeV = vk_wrap(desc->wrap_v);
    ci.addressModeW = vk_wrap(desc->wrap_w);
    ci.anisotropyEnable = VK_FALSE;
    ci.maxAnisotropy = 1.0f;
    ci.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    ci.unnormalizedCoordinates = VK_FALSE;
    ci.compareEnable = VK_FALSE;
    ci.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    ci.mipLodBias = 0.0f;
    ci.minLod = 0.0f;
    ci.maxLod = 0.0f;

    VkSampler sampler;
    vkCreateSampler(vk->device, &ci, NULL, &sampler);

    u32 idx = rhi_alloc_slot(dev);
    VKSamplerData *sd = calloc(1, sizeof(VKSamplerData));
    sd->sampler = sampler;
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SAMPLER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    VKBackend *vk = vk_backend(dev);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(dev, sampler);
    if (!sd) return;
    vkDestroySampler(vk->device, sd->sampler, NULL);
    free(sd);
    rhi_free_slot(dev, sampler);
}

/* ---- Command recording ---- */

void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (vk->render_pass_active) return;

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->render_pass;
    rpi.framebuffer = vk->framebuffers[vk->image_index];
    rpi.renderArea.offset = (VkOffset2D){0, 0};
    rpi.renderArea.extent = vk->swap_extent;

    VkClearValue clears[2] = {0};
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;

    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;

    VkViewport vp = {0, 0, (f32)vk->swap_extent.width, (f32)vk->swap_extent.height, 0.0f, 1.0f};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, vk->swap_extent};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->current_pipeline = VK_NULL_HANDLE;
}

void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }
}

void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource(g_current_device, pipe);
    if (!pd) return;
    VkPipelineBindPoint bind_point = pd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkCmdBindPipeline(vk->cmd_buffers[vk->current_frame], bind_point, pd->pipeline);
    vk->current_pipeline = pd->pipeline;
    vk->current_pipeline_data = pd;
}

void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;
    VkDeviceSize off = (VkDeviceSize)offset;
    vkCmdBindVertexBuffers(vk->cmd_buffers[vk->current_frame], 0, 1, &bd->buffer, &off);
}

void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;
    vkCmdBindIndexBuffer(vk->cmd_buffers[vk->current_frame], bd->buffer, (VkDeviceSize)offset, VK_INDEX_TYPE_UINT32);
}

void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VkViewport vp = {x, y + h, w, -h, 0.0f, 1.0f};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
}

void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VkRect2D sc = {{x, y}, {w, h}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
}

void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vkCmdDraw(vk->cmd_buffers[vk->current_frame], vertex_count, instance_count, 0, 0);
}

void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vkCmdDrawIndexed(vk->cmd_buffers[vk->current_frame], index_count, instance_count, 0, 0, 0);
}

void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vkCmdDispatch(vk->cmd_buffers[vk->current_frame], x, y, z);
}

void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    VKPipelineData *cpd = vk->current_pipeline_data;
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;

    VkDescriptorSetLayout layout_to_use = cpd->is_compute ?
        vk->storage_layout : vk->storage_vtx_layout;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &layout_to_use;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorBufferInfo buf_info = {0};
    buf_info.buffer = bd->buffer;
    buf_info.offset = 0;
    buf_info.range = VK_WHOLE_SIZE;

    VkWriteDescriptorSet write = {0};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = ds;
    write.dstBinding = binding;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    write.pBufferInfo = &buf_info;

    vkUpdateDescriptorSets(vk->device, 1, &write, 0, NULL);
    VkPipelineBindPoint bp = cpd->is_compute ?
        VK_PIPELINE_BIND_POINT_COMPUTE : VK_PIPELINE_BIND_POINT_GRAPHICS;
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        bp, cpd->layout,
        0, 1, &ds, 0, NULL);
}

void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VkMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_HOST_READ_BIT;
    vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
        VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_HOST_BIT,
        0, 1, &barrier, 0, NULL, 0, NULL);
}

void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, depth_tex);
    if (!td) return;

    VkImageMemoryBarrier barrier = {0};
    barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.image = td->image;
    barrier.oldLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.layerCount = 1;
    vkCmdPipelineBarrier(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
        VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
        0, 0, NULL, 0, NULL, 1, &barrier);
}

void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VkClearAttachment att = {0};
    att.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    att.clearValue.color.float32[0] = r;
    att.clearValue.color.float32[1] = g;
    att.clearValue.color.float32[2] = b;
    att.clearValue.color.float32[3] = a;
    VkClearRect rect = {{{0, 0}, vk->swap_extent}, 0, 1};
    vkCmdClearAttachments(vk->cmd_buffers[vk->current_frame], 1, &att, 1, &rect);
}

/* Push constants map to rhi_cmd_set_uniform_*. Location is used as byte offset. */
void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    VkShaderStageFlags stages = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    if (vk->current_pipeline_data->is_compute) stages = VK_SHADER_STAGE_COMPUTE_BIT;
    vkCmdPushConstants(vk->cmd_buffers[vk->current_frame], vk->current_pipeline_data->layout,
        stages, (u32)location, 64, m);
}

void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    f32 v[3] = {x, y, z};
    VkShaderStageFlags stages = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    if (vk->current_pipeline_data->is_compute) stages = VK_SHADER_STAGE_COMPUTE_BIT;
    vkCmdPushConstants(vk->cmd_buffers[vk->current_frame], vk->current_pipeline_data->layout,
        stages, (u32)location, 12, v);
}

void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    f32 v[2] = {x, y};
    VkShaderStageFlags stages = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    if (vk->current_pipeline_data->is_compute) stages = VK_SHADER_STAGE_COMPUTE_BIT;
    vkCmdPushConstants(vk->cmd_buffers[vk->current_frame], vk->current_pipeline_data->layout,
        stages, (u32)location, 8, v);
}

void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    f32 v[4] = {x, y, z, w};
    VkShaderStageFlags stages = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    if (vk->current_pipeline_data->is_compute) stages = VK_SHADER_STAGE_COMPUTE_BIT;
    vkCmdPushConstants(vk->cmd_buffers[vk->current_frame], vk->current_pipeline_data->layout,
        stages, (u32)location, 16, v);
}

void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    VkShaderStageFlags stages = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    if (vk->current_pipeline_data->is_compute) stages = VK_SHADER_STAGE_COMPUTE_BIT;
    vkCmdPushConstants(vk->cmd_buffers[vk->current_frame], vk->current_pipeline_data->layout,
        stages, (u32)location, 4, &v);
}

void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;
    VkShaderStageFlags stages = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    if (vk->current_pipeline_data->is_compute) stages = VK_SHADER_STAGE_COMPUTE_BIT;
    vkCmdPushConstants(vk->cmd_buffers[vk->current_frame], vk->current_pipeline_data->layout,
        stages, (u32)location, 4, &v);
}

i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name) {
    (void)dev;
    VKPipelineData *pd = (VKPipelineData *)rhi_get_resource(dev, pipe);
    bool clustered = pd && pd->uses_texel_buffer && !pd->is_instanced;
    bool non_clustered_tbo = pd && pd->uses_texel_buffer && pd->is_instanced;

    if (non_clustered_tbo) {
        if (strcmp(name, "u_view") == 0)        return 0;
        if (strcmp(name, "u_proj") == 0)        return 64;
        if (strcmp(name, "u_light_dir") == 0)   return 128;
        if (strcmp(name, "u_light_color") == 0) return 144;
        if (strcmp(name, "u_ambient") == 0)     return 160;
        if (strcmp(name, "u_camera_pos") == 0)  return 176;
        return -1;
    }
    if (pd && pd->is_compute) {
        if (strcmp(name, "push.dt") == 0)           return 0;
        if (strcmp(name, "push.view") == 0)         return 0;
        if (strcmp(name, "push.proj") == 0)         return 64;
        return -1;
    }
    if (pd && pd->uses_storage) {
        if (strcmp(name, "push.view") == 0)         return 0;
        if (strcmp(name, "push.proj") == 0)         return 64;
        return -1;
    }
    if (strcmp(name, "u_model") == 0)       return 0;
    if (strcmp(name, "u_view") == 0)        return 64;
    if (strcmp(name, "u_proj") == 0)        return 128;
    if (strcmp(name, "u_light_vp") == 0)    return 64;
    if (strcmp(name, "u_vol_inv_proj") == 0)     return 0;
    if (strcmp(name, "u_vol_view") == 0)         return 64;
    if (strcmp(name, "u_vol_ldx") == 0)          return 128;
    if (strcmp(name, "u_vol_ldy") == 0)          return 132;
    if (strcmp(name, "u_vol_ldz") == 0)          return 136;
    if (strcmp(name, "u_vol_lcx") == 0)          return 140;
    if (strcmp(name, "u_vol_lcy") == 0)          return 144;
    if (strcmp(name, "u_vol_lcz") == 0)          return 148;
    if (strcmp(name, "u_vol_density") == 0)      return 152;
    if (strcmp(name, "u_vol_fog_r") == 0)        return 156;
    if (strcmp(name, "u_vol_fog_g") == 0)        return 160;
    if (strcmp(name, "u_vol_fog_b") == 0)        return 164;
    if (strcmp(name, "u_vol_sw") == 0)           return 168;
    if (strcmp(name, "u_vol_sh") == 0)           return 172;
    if (strcmp(name, "u_lf_light_x") == 0)          return 0;
    if (strcmp(name, "u_lf_light_y") == 0)          return 4;
    if (strcmp(name, "u_lf_intensity") == 0)        return 8;
    if (strcmp(name, "u_lf_sw") == 0)               return 12;
    if (strcmp(name, "u_lf_sh") == 0)               return 16;
    if (strcmp(name, "u_lf_lc_r") == 0)             return 20;
    if (strcmp(name, "u_lf_lc_g") == 0)             return 24;
    if (strcmp(name, "u_lf_lc_b") == 0)             return 28;
    if (strcmp(name, "u_ssgi_inv_proj") == 0)       return 0;
    if (strcmp(name, "u_ssgi_proj") == 0)           return 64;
    if (strcmp(name, "u_ssgi_radius") == 0)         return 128;
    if (strcmp(name, "u_ssgi_intensity") == 0)      return 132;
    if (strcmp(name, "u_ssgi_sw") == 0)             return 136;
    if (strcmp(name, "u_ssgi_sh") == 0)             return 140;
    if (strcmp(name, "u_fxaa_sw") == 0)            return 0;
    if (strcmp(name, "u_fxaa_sh") == 0)            return 4;
    if (strcmp(name, "u_tm_exposure") == 0)       return 0;
    if (strcmp(name, "u_tm_gamma") == 0)           return 4;
    if (strcmp(name, "u_tm_aberration") == 0)      return 8;
    if (strcmp(name, "u_tm_vignette") == 0)        return 12;
    if (strcmp(name, "u_tm_grain") == 0)            return 16;
    if (strcmp(name, "u_tm_time") == 0)             return 20;
    if (strcmp(name, "u_tm_screen_w") == 0)         return 24;
    if (strcmp(name, "u_tm_screen_h") == 0)         return 28;
    if (strcmp(name, "u_tm_saturation") == 0)       return 32;
    if (strcmp(name, "u_tm_contrast") == 0)         return 36;
    if (strcmp(name, "u_tm_brightness") == 0)       return 40;
    if (strcmp(name, "u_tm_temperature") == 0)      return 44;
    if (strcmp(name, "u_tm_tint") == 0)             return 48;
    if (strcmp(name, "u_cine_aberration") == 0)    return 0;
    if (strcmp(name, "u_cine_vignette") == 0)    return 4;
    if (strcmp(name, "u_cine_grain") == 0)       return 8;
    if (strcmp(name, "u_cine_time") == 0)        return 12;
    if (strcmp(name, "u_cine_sw") == 0)          return 16;
    if (strcmp(name, "u_cine_sh") == 0)          return 20;
    if (strcmp(name, "u_dof_focus") == 0)       return 0;
    if (strcmp(name, "u_dof_range") == 0)       return 4;
    if (strcmp(name, "u_dof_near") == 0)        return 8;
    if (strcmp(name, "u_dof_far") == 0)         return 12;
    if (strcmp(name, "u_dof_sw") == 0)          return 16;
    if (strcmp(name, "u_dof_sh") == 0)          return 20;
    if (strcmp(name, "u_ssr_proj") == 0)        return 0;
    if (strcmp(name, "u_ssr_inv_proj") == 0)    return 64;
    if (strcmp(name, "u_ssr_view") == 0)        return 128;
    if (strcmp(name, "u_ssr_sw") == 0)          return 192;
    if (strcmp(name, "u_ssr_sh") == 0)          return 196;
    if (strcmp(name, "u_ssr_max_steps") == 0)   return 200;
    if (strcmp(name, "u_ssr_stride") == 0)      return 204;
    if (strcmp(name, "u_ssr_thickness") == 0)   return 208;
    if (strcmp(name, "u_taa_curr_vp") == 0)     return 0;
    if (strcmp(name, "u_taa_prev_vp") == 0)     return 64;
    if (strcmp(name, "u_taa_inv_proj") == 0)    return 128;
    if (strcmp(name, "u_taa_sw") == 0)          return 192;
    if (strcmp(name, "u_taa_sh") == 0)          return 196;
    if (strcmp(name, "u_taa_blend") == 0)       return 200;
    if (strcmp(name, "u_taa_first_frame") == 0) return 204;
    if (strcmp(name, "u_ssao_proj") == 0)       return 0;
    if (strcmp(name, "u_ssao_inv_proj") == 0)   return 64;
    if (strcmp(name, "u_ssao_sw") == 0)         return 128;
    if (strcmp(name, "u_ssao_sh") == 0)         return 132;
    if (strcmp(name, "u_ssao_radius") == 0)     return 136;
    if (strcmp(name, "u_ssao_bias") == 0)       return 140;
    if (strcmp(name, "u_view") == 0)        return 64;
    if (strcmp(name, "u_proj") == 0)        return 128;
    if (clustered) {
        if (strcmp(name, "u_camera_pos") == 0)  return 192;
        if (strcmp(name, "u_ambient") == 0)     return 208;
        if (strcmp(name, "u_screen_w") == 0)    return 224;
        if (strcmp(name, "u_screen_h") == 0)    return 228;
        if (strcmp(name, "u_near") == 0)        return 232;
        if (strcmp(name, "u_far") == 0)         return 236;
        if (strcmp(name, "u_point_count") == 0) return 240;
        if (strcmp(name, "u_dir_count") == 0)   return 244;
    } else {
        if (strcmp(name, "u_light_dir") == 0)   return 192;
        if (strcmp(name, "u_light_color") == 0) return 208;
        if (strcmp(name, "u_ambient") == 0)     return 224;
        if (strcmp(name, "u_camera_pos") == 0)  return 240;
    }
    if (strcmp(name, "u_albedo") == 0)      return -1;
    if (strcmp(name, "u_inv_proj") == 0)    return 0;
    return -1;
}

void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler) {
    (void)cmd; (void)shadow;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;

    VKTextureData *td_alb = (VKTextureData *)rhi_get_resource(g_current_device, albedo);
    VKTextureData *td_mr  = (VKTextureData *)rhi_get_resource(g_current_device, mr);
    VKTextureData *td_nrm = (VKTextureData *)rhi_get_resource(g_current_device, normal);
    VKTextureData *td_em  = (VKTextureData *)rhi_get_resource(g_current_device, emissive);
    VKTextureData *td_ssao = (VKTextureData *)rhi_get_resource(g_current_device, ssao);
    VKSamplerData *sd     = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!sd) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkImageView views[6];
    VkImageView alb_view = td_alb ? td_alb->view : VK_NULL_HANDLE;
    VkImageView shadow_view = vk->shadow_tex_view ? vk->shadow_tex_view : alb_view;
    views[0] = alb_view;
    views[1] = shadow_view;
    views[2] = td_mr  ? td_mr->view  : alb_view;
    views[3] = td_nrm ? td_nrm->view : alb_view;
    views[4] = td_em  ? td_em->view  : alb_view;
    views[5] = td_ssao ? td_ssao->view : alb_view;

    VkDescriptorImageInfo img_infos[6];
    VkWriteDescriptorSet writes[6];
    memset(img_infos, 0, sizeof(img_infos));
    memset(writes, 0, sizeof(writes));

    for (int i = 0; i < 6; i++) {
        img_infos[i].sampler = sd->sampler;
        img_infos[i].imageView = views[i];
        img_infos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        writes[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[i].dstSet = ds;
        writes[i].dstBinding = i;
        writes[i].descriptorCount = 1;
        writes[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        writes[i].pImageInfo = &img_infos[i];
    }

    vkUpdateDescriptorSets(vk->device, 6, writes, 0, NULL);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd,
    RHITexture *textures, int count, RHISampler sampler) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data || count <= 0 || count > 6) return;

    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!sd) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo img_infos[6];
    VkWriteDescriptorSet writes[6];
    memset(img_infos, 0, sizeof(img_infos));
    memset(writes, 0, sizeof(writes));

    for (int i = 0; i < count; i++) {
        VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, textures[i]);
        img_infos[i].sampler = sd->sampler;
        img_infos[i].imageView = td ? td->view : VK_NULL_HANDLE;
        img_infos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        writes[i].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[i].dstSet = ds;
        writes[i].dstBinding = i;
        writes[i].descriptorCount = 1;
        writes[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        writes[i].pImageInfo = &img_infos[i];
    }

    vkUpdateDescriptorSets(vk->device, count, writes, 0, NULL);
    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    rhi_cmd_bind_material_textures(cmd, tex, tex, tex, tex, tex, tex, sampler);
    (void)unit;
}

void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex, RHISampler sampler) {
    (void)cmd; (void)sampler;
    VKBackend *vk = vk_backend(g_current_device);
    VKTextureData *td = (VKTextureData *)rhi_get_resource(g_current_device, shadow_tex);
    vk->shadow_tex_view = td ? td->view : VK_NULL_HANDLE;
}

void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd; (void)buf; (void)binding;
}

/* ---- Shadow map stubs ---- */

typedef struct {
    VkImage        depth_image;
    VkDeviceMemory depth_memory;
    VkImageView    depth_view;
    VkFramebuffer  framebuffer;
    VkRenderPass   render_pass;
} VKShadowData;

RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    VKBackend *vk = vk_backend(dev);
    RHIShadowMap sm = {0};
    sm.width = width;
    sm.height = height;

    VKShadowData *sd = calloc(1, sizeof(VKShadowData));

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = VK_FORMAT_D32_SFLOAT;
    ci.extent.width = width;
    ci.extent.height = height;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    vkCreateImage(vk->device, &ci, NULL, &sd->depth_image);

    VkMemoryRequirements mr;
    vkGetImageMemoryRequirements(vk->device, sd->depth_image, &mr);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(vk->device, &ai, NULL, &sd->depth_memory);
    vkBindImageMemory(vk->device, sd->depth_image, sd->depth_memory, 0);

    VkImageViewCreateInfo ivci = {0};
    ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivci.image = sd->depth_image;
    ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    ivci.format = VK_FORMAT_D32_SFLOAT;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    ivci.subresourceRange.levelCount = 1;
    ivci.subresourceRange.layerCount = 1;
    vkCreateImageView(vk->device, &ivci, NULL, &sd->depth_view);

    VkAttachmentDescription depth_att = {0};
    depth_att.format = VK_FORMAT_D32_SFLOAT;
    depth_att.samples = VK_SAMPLE_COUNT_1_BIT;
    depth_att.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depth_att.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    depth_att.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depth_att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depth_att.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depth_att.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkAttachmentReference depth_ref = {0, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.pDepthStencilAttachment = &depth_ref;

    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dep.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dep.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo rpci = {0};
    rpci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = 1;
    rpci.pAttachments = &depth_att;
    rpci.subpassCount = 1;
    rpci.pSubpasses = &sp;
    rpci.dependencyCount = 1;
    rpci.pDependencies = &dep;
    vkCreateRenderPass(vk->device, &rpci, NULL, &sd->render_pass);

    VkFramebufferCreateInfo fbci = {0};
    fbci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbci.renderPass = sd->render_pass;
    fbci.attachmentCount = 1;
    fbci.pAttachments = &sd->depth_view;
    fbci.width = width;
    fbci.height = height;
    fbci.layers = 1;
    vkCreateFramebuffer(vk->device, &fbci, NULL, &sd->framebuffer);

    if (vk->shadow_render_pass == VK_NULL_HANDLE) {
        vk->shadow_render_pass = sd->render_pass;
    }

    u32 tidx = rhi_alloc_slot(dev);
    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    td->image = sd->depth_image;
    td->view = sd->depth_view;
    td->memory = sd->depth_memory;
    td->width = width;
    td->height = height;
    dev->slots[tidx].ptr = td;
    dev->slots[tidx].type = RHI_RES_TEXTURE;
    sm.depth_tex = rhi_make_handle(tidx, dev->slots[tidx].generation);

    u32 fidx = rhi_alloc_slot(dev);
    dev->slots[fidx].ptr = sd;
    dev->slots[fidx].type = RHI_RES_FRAMEBUFFER;
    sm.fbo = rhi_make_handle(fidx, dev->slots[fidx].generation);

    return sm;
}

void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    if (!dev || !sm) return;
    VKBackend *vk = vk_backend(dev);
    VKShadowData *sd = rhi_get_resource(dev, sm->fbo);
    if (!sd) return;
    vkDeviceWaitIdle(vk->device);
    vkDestroyFramebuffer(vk->device, sd->framebuffer, NULL);
    vkDestroyRenderPass(vk->device, sd->render_pass, NULL);
    vkDestroyImageView(vk->device, sd->depth_view, NULL);
    vkDestroyImage(vk->device, sd->depth_image, NULL);
    vkFreeMemory(vk->device, sd->depth_memory, NULL);
    free(sd);
    rhi_free_slot(dev, sm->fbo);
    rhi_free_slot(dev, sm->depth_tex);
    sm->fbo = RHI_HANDLE_NULL;
    sm->depth_tex = RHI_HANDLE_NULL;
}

void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    (void)cmd;
    if (!sm) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKShadowData *sd = rhi_get_resource(g_current_device, sm->fbo);
    if (!sd) return;

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = sd->render_pass;
    rpi.framebuffer = sd->framebuffer;
    rpi.renderArea.extent.width = sm->width;
    rpi.renderArea.extent.height = sm->height;
    VkClearValue clear;
    memset(&clear, 0, sizeof(clear));
    clear.depthStencil.depth = 1.0f;
    rpi.clearValueCount = 1;
    rpi.pClearValues = &clear;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;

    VkViewport vp = {0, 0, (f32)sm->width, (f32)sm->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {sm->width, sm->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
}

void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->render_pass;
    rpi.framebuffer = vk->framebuffers[vk->image_index];
    rpi.renderArea.extent.width = screen_w;
    rpi.renderArea.extent.height = screen_h;
    VkClearValue clears[2];
    memset(clears, 0, sizeof(clears));
    clears[0].color.float32[0] = 0.2f;
    clears[0].color.float32[1] = 0.25f;
    clears[0].color.float32[2] = 0.35f;
    clears[0].color.float32[3] = 1.0f;
    clears[1].depthStencil.depth = 1.0f;
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi, VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;

    VkViewport vp = {0, 0, (f32)screen_w, (f32)screen_h, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {screen_w, screen_h}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->current_pipeline = VK_NULL_HANDLE;
}

void rhi_cmd_clear_depth(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    VkClearAttachment att = {0};
    att.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    att.clearValue.depthStencil.depth = 1.0f;
    VkClearRect rect = {{{0, 0}, vk->swap_extent}, 0, 1};
    vkCmdClearAttachments(vk->cmd_buffers[vk->current_frame], 1, &att, 1, &rect);
}

/* ---- Cubemap stubs ---- */

typedef struct {
    VkImage        image;
    VkDeviceMemory memory;
    VkImageView    view;
} VKCubemapData;

RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    VKBackend *vk = vk_backend(dev);

    VKCubemapData *cd = calloc(1, sizeof(VKCubemapData));

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = VK_FORMAT_R8G8B8A8_UNORM;
    ci.extent.width = desc->size;
    ci.extent.height = desc->size;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 6;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    ci.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
    vkCreateImage(vk->device, &ci, NULL, &cd->image);

    VkMemoryRequirements mr;
    vkGetImageMemoryRequirements(vk->device, cd->image, &mr);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(vk->device, &ai, NULL, &cd->memory);
    vkBindImageMemory(vk->device, cd->image, cd->memory, 0);

    VkImageViewCreateInfo ivci = {0};
    ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivci.image = cd->image;
    ivci.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
    ivci.format = VK_FORMAT_R8G8B8A8_UNORM;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    ivci.subresourceRange.levelCount = 1;
    ivci.subresourceRange.layerCount = 6;
    vkCreateImageView(vk->device, &ivci, NULL, &cd->view);

    {
        VkCommandBuffer cb = vk->cmd_buffers[vk->current_frame];
        VkImageMemoryBarrier barrier = {0};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.image = cd->image;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.layerCount = 6;
        vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0, NULL, 1, &barrier);
    }

    u32 idx = rhi_alloc_slot(dev);
    dev->slots[idx].ptr = cd;
    dev->slots[idx].type = RHI_RES_CUBEMAP;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    if (!dev || !rhi_handle_valid(cm)) return;
    VKBackend *vk = vk_backend(dev);
    VKCubemapData *cd = rhi_get_resource(dev, cm);
    if (!cd) return;
    vkDeviceWaitIdle(vk->device);
    vkDestroyImageView(vk->device, cd->view, NULL);
    vkDestroyImage(vk->device, cd->image, NULL);
    vkFreeMemory(vk->device, cd->memory, NULL);
    free(cd);
    rhi_free_slot(dev, cm);
}

void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    (void)cmd; (void)unit;
    VKBackend *vk = vk_backend(g_current_device);
    VKCubemapData *cd = (VKCubemapData *)rhi_get_resource(g_current_device, cm);
    VKSamplerData *sd = (VKSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (!cd || !sd || !vk->current_pipeline_data) return;

    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->desc_layout;

    VkDescriptorSet ds;
    if (vkAllocateDescriptorSets(vk->device, &dsai, &ds) != VK_SUCCESS) return;

    VkDescriptorImageInfo img_info = {0};
    img_info.sampler = sd->sampler;
    img_info.imageView = cd->view;
    img_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkDescriptorImageInfo dummy_info = {0};
    dummy_info.sampler = sd->sampler;
    dummy_info.imageView = cd->view;
    dummy_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkWriteDescriptorSet writes[2];
    memset(writes, 0, sizeof(writes));
    writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[0].dstSet = ds;
    writes[0].dstBinding = 0;
    writes[0].descriptorCount = 1;
    writes[0].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[0].pImageInfo = &img_info;
    writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[1].dstSet = ds;
    writes[1].dstBinding = 1;
    writes[1].descriptorCount = 1;
    writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[1].pImageInfo = &dummy_info;
    vkUpdateDescriptorSets(vk->device, 2, writes, 0, NULL);

    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        0, 1, &ds, 0, NULL);
}

/* ---- Depth state ---- */

void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vkCmdSetDepthCompareOp(vk->cmd_buffers[vk->current_frame], VK_COMPARE_OP_LESS_OR_EQUAL);
}

void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    vkCmdSetDepthCompareOp(vk->cmd_buffers[vk->current_frame], VK_COMPARE_OP_LESS);
}

void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    void *mapped;
    vkMapMemory(vk->device, bd->memory, 0, size, 0, &mapped);
    memcpy(mapped, data, size);
    vkUnmapMemory(vk->device, bd->memory);
}

void* rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return NULL;
    void *mapped = NULL;
    vkMapMemory(vk->device, bd->memory, 0, VK_WHOLE_SIZE, 0, &mapped);
    return mapped;
}

void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) {
    VKBackend *vk = vk_backend(dev);
    VKBufferData *bd = (VKBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    vkUnmapMemory(vk->device, bd->memory);
}

void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);
    if (!vk->current_pipeline_data) return;

    VKBufferData *bd0 = (VKBufferData *)rhi_get_resource(g_current_device, buf0);
    if (!bd0 || bd0->texel_view == VK_NULL_HANDLE) return;

    VkDescriptorSet desc_set;
    VkDescriptorSetAllocateInfo dsai = {0};
    dsai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsai.descriptorPool = vk->desc_pools[vk->current_frame];
    dsai.descriptorSetCount = 1;
    dsai.pSetLayouts = &vk->texel_layout;
    VkResult res = vkAllocateDescriptorSets(vk->device, &dsai, &desc_set);
    if (res != VK_SUCCESS) {
        LOG_ERROR("Failed to allocate texel descriptor set: %d", res);
        return;
    }

    VkWriteDescriptorSet writes[2] = {0};
    u32 write_count = 0;
    writes[write_count].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[write_count].dstSet = desc_set;
    writes[write_count].dstBinding = 0;
    writes[write_count].descriptorCount = 1;
    writes[write_count].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
    writes[write_count].pTexelBufferView = &bd0->texel_view;
    write_count++;

    VKBufferData *bd1 = NULL;
    if (rhi_handle_valid(buf1)) {
        bd1 = (VKBufferData *)rhi_get_resource(g_current_device, buf1);
    }
    if (bd1 && bd1->texel_view != VK_NULL_HANDLE) {
        writes[write_count].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[write_count].dstSet = desc_set;
        writes[write_count].dstBinding = 1;
        writes[write_count].descriptorCount = 1;
        writes[write_count].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        writes[write_count].pTexelBufferView = &bd1->texel_view;
        write_count++;
    }

    vkUpdateDescriptorSets(vk->device, write_count, writes, 0, NULL);

    vkCmdBindDescriptorSets(vk->cmd_buffers[vk->current_frame],
        VK_PIPELINE_BIND_POINT_GRAPHICS, vk->current_pipeline_data->layout,
        1, 1, &desc_set, 0, NULL);
}

/* ---- Offscreen FBO ---- */

typedef struct {
    VkImage        color_image;
    VkDeviceMemory color_memory;
    VkImageView    color_view;
    VkImage        depth_image;
    VkDeviceMemory depth_memory;
    VkImageView    depth_view;
    VkFramebuffer  framebuffer;
    VkRenderPass   render_pass;
} VKFBOData;

RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height, RHIFormat color_fmt) {
    VKBackend *vk = vk_backend(dev);
    RHIOffscreenFBO fbo = {0};
    fbo.width = width;
    fbo.height = height;

    VkFormat vk_color_fmt = vk_format_from_rhi(color_fmt);

    VKFBOData *fd = calloc(1, sizeof(VKFBOData));

    VkImageCreateInfo ci = {0};
    ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ci.imageType = VK_IMAGE_TYPE_2D;
    ci.format = vk_color_fmt;
    ci.extent.width = width;
    ci.extent.height = height;
    ci.extent.depth = 1;
    ci.mipLevels = 1;
    ci.arrayLayers = 1;
    ci.samples = VK_SAMPLE_COUNT_1_BIT;
    ci.tiling = VK_IMAGE_TILING_OPTIMAL;
    ci.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ci.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    vkCreateImage(vk->device, &ci, NULL, &fd->color_image);

    VkMemoryRequirements mr;
    vkGetImageMemoryRequirements(vk->device, fd->color_image, &mr);
    VkMemoryAllocateInfo ai = {0};
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(vk->device, &ai, NULL, &fd->color_memory);
    vkBindImageMemory(vk->device, fd->color_image, fd->color_memory, 0);

    VkImageViewCreateInfo ivci = {0};
    ivci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    ivci.image = fd->color_image;
    ivci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    ivci.format = vk_color_fmt;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    ivci.subresourceRange.levelCount = 1;
    ivci.subresourceRange.layerCount = 1;
    vkCreateImageView(vk->device, &ivci, NULL, &fd->color_view);

    ci.format = VK_FORMAT_D32_SFLOAT;
    ci.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    vkCreateImage(vk->device, &ci, NULL, &fd->depth_image);
    vkGetImageMemoryRequirements(vk->device, fd->depth_image, &mr);
    ai.allocationSize = mr.size;
    ai.memoryTypeIndex = vk_find_memory(vk, mr.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vkAllocateMemory(vk->device, &ai, NULL, &fd->depth_memory);
    vkBindImageMemory(vk->device, fd->depth_image, fd->depth_memory, 0);

    ivci.image = fd->depth_image;
    ivci.format = VK_FORMAT_D32_SFLOAT;
    ivci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    vkCreateImageView(vk->device, &ivci, NULL, &fd->depth_view);

    VkAttachmentDescription attachments[2] = {0};
    attachments[0].format = vk_color_fmt;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    attachments[1].format = VK_FORMAT_D32_SFLOAT;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference color_ref = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkAttachmentReference depth_ref = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp = {0};
    sp.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = 1;
    sp.pColorAttachments = &color_ref;
    sp.pDepthStencilAttachment = &depth_ref;

    VkSubpassDependency dep = {0};
    dep.srcSubpass = VK_SUBPASS_EXTERNAL;
    dep.dstSubpass = 0;
    dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.srcAccessMask = 0;
    dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo rpci = {0};
    rpci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = 2;
    rpci.pAttachments = attachments;
    rpci.subpassCount = 1;
    rpci.pSubpasses = &sp;
    rpci.dependencyCount = 1;
    rpci.pDependencies = &dep;
    vkCreateRenderPass(vk->device, &rpci, NULL, &fd->render_pass);

    VkImageView views[] = {fd->color_view, fd->depth_view};
    VkFramebufferCreateInfo fbci = {0};
    fbci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbci.renderPass = fd->render_pass;
    fbci.attachmentCount = 2;
    fbci.pAttachments = views;
    fbci.width = width;
    fbci.height = height;
    fbci.layers = 1;
    vkCreateFramebuffer(vk->device, &fbci, NULL, &fd->framebuffer);

    u32 idx = rhi_alloc_slot(dev);
    VKTextureData *td = calloc(1, sizeof(VKTextureData));
    td->image = fd->color_image;
    td->view = fd->color_view;
    td->memory = fd->color_memory;
    td->width = width;
    td->height = height;
    dev->slots[idx].ptr = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    fbo.color_tex = rhi_make_handle(idx, dev->slots[idx].generation);

    u32 didx = rhi_alloc_slot(dev);
    VKTextureData *dd = calloc(1, sizeof(VKTextureData));
    dd->image = fd->depth_image;
    dd->view = fd->depth_view;
    dd->memory = fd->depth_memory;
    dd->width = width;
    dd->height = height;
    dev->slots[didx].ptr = dd;
    dev->slots[didx].type = RHI_RES_TEXTURE;
    fbo.depth_tex = rhi_make_handle(didx, dev->slots[didx].generation);

    u32 fidx = rhi_alloc_slot(dev);
    dev->slots[fidx].ptr = fd;
    dev->slots[fidx].type = RHI_RES_FRAMEBUFFER;
    fbo.fb = rhi_make_handle(fidx, dev->slots[fidx].generation);

    return fbo;
}

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height) {
    return rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_B8G8R8A8_UNORM);
}

void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    if (!dev || !fbo) return;
    VKBackend *vk = vk_backend(dev);
    VKFBOData *fd = rhi_get_resource(dev, fbo->fb);
    if (!fd) return;
    vkDeviceWaitIdle(vk->device);
    vkDestroyFramebuffer(vk->device, fd->framebuffer, NULL);
    vkDestroyRenderPass(vk->device, fd->render_pass, NULL);
    vkDestroyImageView(vk->device, fd->color_view, NULL);
    vkDestroyImage(vk->device, fd->color_image, NULL);
    vkFreeMemory(vk->device, fd->color_memory, NULL);
    vkDestroyImageView(vk->device, fd->depth_view, NULL);
    vkDestroyImage(vk->device, fd->depth_image, NULL);
    vkFreeMemory(vk->device, fd->depth_memory, NULL);
    free(fd);
    rhi_free_slot(dev, fbo->fb);
    rhi_free_slot(dev, fbo->color_tex);
    rhi_free_slot(dev, fbo->depth_tex);
    memset(fbo, 0, sizeof(*fbo));
}

void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    VKBackend *vk = vk_backend(g_current_device);
    VKFBOData *fd = rhi_get_resource(g_current_device, fbo->fb);
    if (!fd) return;

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = fd->render_pass;
    rpi.framebuffer = fd->framebuffer;
    rpi.renderArea.extent.width = fbo->width;
    rpi.renderArea.extent.height = fbo->height;
    VkClearValue clears[2];
    memset(clears, 0, sizeof(clears));
    clears[0].color.float32[0] = 0.05f;
    clears[0].color.float32[1] = 0.05f;
    clears[0].color.float32[2] = 0.1f;
    clears[0].color.float32[3] = 1.0f;
    clears[1].depthStencil.depth = 1.0f;
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
        VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;

    VkViewport vp = {0, 0, (f32)fbo->width, (f32)fbo->height, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {fbo->width, fbo->height}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
}

void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    VKBackend *vk = vk_backend(g_current_device);

    if (vk->render_pass_active) {
        vkCmdEndRenderPass(vk->cmd_buffers[vk->current_frame]);
        vk->render_pass_active = false;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass = vk->render_pass;
    rpi.framebuffer = vk->framebuffers[vk->image_index];
    rpi.renderArea.extent.width = screen_w;
    rpi.renderArea.extent.height = screen_h;
    VkClearValue clears[2];
    memset(clears, 0, sizeof(clears));
    clears[0].color.float32[0] = 0.2f;
    clears[0].color.float32[1] = 0.25f;
    clears[0].color.float32[2] = 0.35f;
    clears[0].color.float32[3] = 1.0f;
    clears[1].depthStencil.depth = 1.0f;
    rpi.clearValueCount = 2;
    rpi.pClearValues = clears;
    vkCmdBeginRenderPass(vk->cmd_buffers[vk->current_frame], &rpi,
        VK_SUBPASS_CONTENTS_INLINE);
    vk->render_pass_active = true;

    VkViewport vp = {0, 0, (f32)screen_w, (f32)screen_h, 0, 1};
    vkCmdSetViewport(vk->cmd_buffers[vk->current_frame], 0, 1, &vp);
    VkRect2D sc = {{0, 0}, {screen_w, screen_h}};
    vkCmdSetScissor(vk->cmd_buffers[vk->current_frame], 0, 1, &sc);
    vk->current_pipeline = VK_NULL_HANDLE;
}
