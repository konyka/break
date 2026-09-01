/**
 * @file my_vgcanvas_vulkan.c
 * @brief Vulkan vgcanvas backend (M25b).
 *
 * Structure: a lazily created global (VkInstance + physical device +
 * VkDevice + queue, refcounted by canvases) and per-canvas state
 * (surface/swapchain or offscreen image, renderpass, 3 pipelines, 2
 * frame slots, glyph/image texture caches). Geometry comes from the
 * shared my_vggeometry (identical triangulation to the gles2 backend).
 *
 * Simplifications (documented, correctness-first):
 *  - texture uploads are one-shot submit+wait (cache misses only);
 *  - vertex data goes into one host-coherent buffer, 1 MiB per frame
 *    slot; a frame that overflows drops the draw with an error log;
 *  - no validation layers are enabled (release behavior).
 */
#include "myr/my_vgcanvas_vulkan.h"

#ifdef MYUI_HAS_VULKAN

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myr/my_text_layout.h"
#include "myr/my_vgcanvas_quality_transaction.h"
#include "myr/my_vggeometry.h"

#define VK_USE_PLATFORM_XLIB_KHR
#define VK_USE_PLATFORM_WAYLAND_KHR
#include <vulkan/vulkan.h>

#include "myr/vulkan_shaders/flat.vert.inc"
#include "myr/vulkan_shaders/flat.frag.inc"
#include "myr/vulkan_shaders/tex.vert.inc"
#include "myr/vulkan_shaders/text.frag.inc"
#include "myr/vulkan_shaders/img.frag.inc"

#define VKC_MAX_IMGS 4
#define VKC_FRAMES 2
#define VKC_VBUF_PER_FRAME (1u * 1024u * 1024u) /* bytes per frame slot */
#define VKC_GLYPH_CACHE 64
#define VKC_IMG_CACHE 16
#define VKC_PUSH_SIZE 32 /* std140 push block: vec2 + pad + vec4 */

/* ---------------- global (shared, refcounted) ---------------- */

typedef struct vk_global_t {
  int refs;
  VkInstance inst;
  VkPhysicalDevice pdev;
  VkDevice dev;
  uint32_t qfam;
  VkQueue queue;
  VkCommandPool upload_pool;
} vk_global_t;

static vk_global_t g_vk;

static bool vk_ext_present(const char* name) {
  uint32_t n = 0, i;
  VkExtensionProperties props[64];
  bool found = false;
  if (vkEnumerateInstanceExtensionProperties(NULL, &n, NULL) != VK_SUCCESS) {
    return false;
  }
  if (n > 64) {
    n = 64;
  }
  if (vkEnumerateInstanceExtensionProperties(NULL, &n, props) !=
      VK_SUCCESS) {
    return false;
  }
  for (i = 0; i < n; i++) {
    if (strcmp(props[i].extensionName, name) == 0) {
      found = true;
    }
  }
  return found;
}

static my_ret_t vk_global_init(void) {
  VkApplicationInfo app;
  VkInstanceCreateInfo ici;
  const char* exts[4];
  uint32_t nexts = 0;
  uint32_t ndev = 0, i;
  VkPhysicalDevice devs[8];
  if (g_vk.inst != VK_NULL_HANDLE) {
    return MY_RET_OK;
  }
  memset(&g_vk, 0, sizeof(g_vk));
  exts[nexts++] = VK_KHR_SURFACE_EXTENSION_NAME;
  if (vk_ext_present(VK_KHR_XLIB_SURFACE_EXTENSION_NAME)) {
    exts[nexts++] = VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
  }
  if (vk_ext_present(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME)) {
    exts[nexts++] = VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME;
  }
  memset(&app, 0, sizeof(app));
  app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app.pApplicationName = "myui";
  app.apiVersion = VK_API_VERSION_1_1;
  memset(&ici, 0, sizeof(ici));
  ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  ici.pApplicationInfo = &app;
  ici.enabledExtensionCount = nexts;
  ici.ppEnabledExtensionNames = exts;
  if (vkCreateInstance(&ici, NULL, &g_vk.inst) != VK_SUCCESS) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (vkEnumeratePhysicalDevices(g_vk.inst, &ndev, NULL) != VK_SUCCESS ||
      ndev == 0) {
    vkDestroyInstance(g_vk.inst, NULL);
    return MY_RET_NOT_SUPPORTED;
  }
  if (ndev > 8) {
    ndev = 8;
  }
  if (vkEnumeratePhysicalDevices(g_vk.inst, &ndev, devs) != VK_SUCCESS) {
    vkDestroyInstance(g_vk.inst, NULL);
    return MY_RET_NOT_SUPPORTED;
  }
  for (i = 0; i < ndev && g_vk.pdev == VK_NULL_HANDLE; i++) {
    uint32_t nq = 0, q;
    VkQueueFamilyProperties qprops[16];
    vkGetPhysicalDeviceQueueFamilyProperties(devs[i], &nq, NULL);
    if (nq > 16) {
      nq = 16;
    }
    vkGetPhysicalDeviceQueueFamilyProperties(devs[i], &nq, qprops);
    for (q = 0; q < nq; q++) {
      if (qprops[q].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
        g_vk.pdev = devs[i];
        g_vk.qfam = q;
        break;
      }
    }
  }
  if (g_vk.pdev == VK_NULL_HANDLE) {
    vkDestroyInstance(g_vk.inst, NULL);
    return MY_RET_NOT_SUPPORTED;
  }
  {
    float prio = 1.0f;
    const char* dev_exts[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    VkDeviceQueueCreateInfo qci;
    VkDeviceCreateInfo dci;
    memset(&qci, 0, sizeof(qci));
    qci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    qci.queueFamilyIndex = g_vk.qfam;
    qci.queueCount = 1;
    qci.pQueuePriorities = &prio;
    memset(&dci, 0, sizeof(dci));
    dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    dci.queueCreateInfoCount = 1;
    dci.pQueueCreateInfos = &qci;
    dci.enabledExtensionCount = 1;
    dci.ppEnabledExtensionNames = dev_exts;
    if (vkCreateDevice(g_vk.pdev, &dci, NULL, &g_vk.dev) != VK_SUCCESS) {
      vkDestroyInstance(g_vk.inst, NULL);
      return MY_RET_NOT_SUPPORTED;
    }
  }
  vkGetDeviceQueue(g_vk.dev, g_vk.qfam, 0, &g_vk.queue);
  {
    VkCommandPoolCreateInfo pci;
    memset(&pci, 0, sizeof(pci));
    pci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    pci.queueFamilyIndex = g_vk.qfam;
    if (vkCreateCommandPool(g_vk.dev, &pci, NULL, &g_vk.upload_pool) !=
        VK_SUCCESS) {
      vkDestroyDevice(g_vk.dev, NULL);
      vkDestroyInstance(g_vk.inst, NULL);
      return MY_RET_NOT_SUPPORTED;
    }
  }
  return MY_RET_OK;
}

static my_ret_t vk_global_acquire(void) {
  if (vk_global_init() != MY_RET_OK) {
    return MY_RET_NOT_SUPPORTED;
  }
  g_vk.refs++;
  return MY_RET_OK;
}

static void vk_global_release(void) {
  if (g_vk.refs <= 0) {
    return;
  }
  g_vk.refs--;
  if (g_vk.refs == 0) {
    vkDeviceWaitIdle(g_vk.dev);
    vkDestroyCommandPool(g_vk.dev, g_vk.upload_pool, NULL);
    vkDestroyDevice(g_vk.dev, NULL);
    vkDestroyInstance(g_vk.inst, NULL);
    memset(&g_vk, 0, sizeof(g_vk));
  }
}

void* my_vgcanvas_vulkan_instance(void) {
  /* peek only: canvases own the global lifecycle (no ref taken here) */
  return vk_global_init() == MY_RET_OK ? (void*)g_vk.inst : NULL;
}

void my_vgcanvas_vulkan_destroy_surface(void* vk_surface) {
  if (vk_surface != NULL && g_vk.inst != VK_NULL_HANDLE) {
    vkDestroySurfaceKHR(g_vk.inst, (VkSurfaceKHR)vk_surface, NULL);
  }
}

/* ---------------- per-canvas state ---------------- */

typedef struct vk_tex_t {
  VkImage img;
  VkDeviceMemory mem;
  VkImageView view;
  VkDescriptorSet ds;
} vk_tex_t;

typedef struct vk_glyph_entry_t {
  my_font_t* font;
  uint32_t codepoint;
  bool key_is_glyph_id;
  int32_t size;
  vk_tex_t tex; /* .img == VK_NULL_HANDLE = empty */
} vk_glyph_entry_t;

typedef struct vk_img_entry_t {
  const uint8_t* ptr;
  int32_t w, h;
  my_scale_filter_t filter;
  vk_tex_t tex;
  uint64_t last_used;
} vk_img_entry_t;

typedef struct vk_state_t {
  my_color_t fill_color;
  my_color_t stroke_color;
  float line_width;
  my_line_cap_t line_cap;
  my_line_join_t line_join;
  float tx, ty, scale;
  my_rect_t clip;
  my_font_t* font;
  int32_t font_size;
  my_scale_filter_t scale_filter;
} vk_state_t;

typedef struct vk_frame_t {
  VkCommandBuffer cmd;
  VkFence fence;
  VkSemaphore sem_acquire;
  VkSemaphore sem_present;
  VkDeviceSize vbuf_off; /* start offset inside the shared vbuf */
  VkDeviceSize vbuf_used;
} vk_frame_t;

typedef struct my_vgcanvas_vulkan_t {
  my_vgcanvas_t base;
  const my_allocator_t* allocator;
  bool offscreen;
  int32_t fb_w, fb_h;
  int32_t pending_fb_w, pending_fb_h;
  bool need_recreate;
  int dbg_frames; /* MYUI_VK_DUMP frame counter (debug only) */
  int dbg_dump_frame; /* dump at the Nth present (MYUI_VK_DUMP_FRAME) */
  const char* dbg_dump_path; /* env snapshot at create (debug only) */

  VkSurfaceKHR surface;   /* windowed only */
  VkSwapchainKHR swapchain;
  VkFormat format;
  VkSampleCountFlagBits samples;
  uint32_t img_count;
  VkImage target_imgs[VKC_MAX_IMGS];  /* swapchain or 1 offscreen image */
  VkImageView target_views[VKC_MAX_IMGS];
  VkFramebuffer fbs[VKC_MAX_IMGS];
  VkDeviceMemory offscreen_mem; /* offscreen target memory (windowed: n/a) */
  VkImage msaa_img;
  VkDeviceMemory msaa_mem;
  VkImageView msaa_view;

  VkRenderPass renderpass;
  /* resolve-only renderpass + per-target framebuffers (M25c): the
   * windowed MSAA resolve goes through a zero-draw subpass so the
   * swapchain images need no TRANSFER usages (WSI dmabuf constraint) */
  VkRenderPass resolve_rp;
  VkFramebuffer resolve_fbs[VKC_MAX_IMGS];
  VkFramebuffer pending_fb[VKC_MAX_IMGS]; /* transient clear-rp fbs */
  VkDescriptorSetLayout ds_layout;
  VkDescriptorPool ds_pool;
  VkSampler sampler;
  VkSampler nearest_sampler;
  VkPipelineLayout pipe_layout;
  VkPipeline pipe_flat, pipe_text, pipe_img;

  VkCommandPool cmd_pool;
  /* deferred texture destruction (M25b): an evicted texture may still be
   * referenced by an in-flight frame; retired textures are destroyed when
   * the frame slot they were retired into is reused (fence waited). The
   * lists grow on demand (a frame may evict many glyphs at once) */
  vk_tex_t* retired[VKC_FRAMES];
  size_t retired_count[VKC_FRAMES];
  size_t retired_cap[VKC_FRAMES];
  vk_frame_t frames[VKC_FRAMES];
  uint32_t frame_idx;
  uint32_t img_idx;
  bool cmd_pending;
  bool in_renderpass;

  VkBuffer vbuf;
  VkDeviceMemory vbuf_mem;
  void* vbuf_map;

  vk_glyph_entry_t glyph_cache[VKC_GLYPH_CACHE];
  vk_img_entry_t img_cache[VKC_IMG_CACHE];
  uint64_t img_tick;

  my_vggeometry_t geo;
  vk_state_t state;
  vk_state_t* stack;
  size_t stack_count, stack_cap;
} my_vgcanvas_vulkan_t;

/* ---------------- small vk helpers ---------------- */

static uint32_t vk_mem_type(uint32_t bits, VkMemoryPropertyFlags props) {
  VkPhysicalDeviceMemoryProperties mp;
  uint32_t i;
  vkGetPhysicalDeviceMemoryProperties(g_vk.pdev, &mp);
  for (i = 0; i < mp.memoryTypeCount; i++) {
    if ((bits & (1u << i)) != 0 &&
        (mp.memoryTypes[i].propertyFlags & props) == props) {
      return i;
    }
  }
  return UINT32_MAX;
}

static my_ret_t vk_make_buffer(VkDeviceSize size, VkBufferUsageFlags usage,
                               VkMemoryPropertyFlags props, VkBuffer* buf,
                               VkDeviceMemory* mem) {
  VkBufferCreateInfo bci;
  VkMemoryRequirements req;
  VkMemoryAllocateInfo mai;
  memset(&bci, 0, sizeof(bci));
  bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bci.size = size;
  bci.usage = usage;
  bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  if (vkCreateBuffer(g_vk.dev, &bci, NULL, buf) != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  vkGetBufferMemoryRequirements(g_vk.dev, *buf, &req);
  memset(&mai, 0, sizeof(mai));
  mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mai.allocationSize = req.size;
  mai.memoryTypeIndex = vk_mem_type(req.memoryTypeBits, props);
  if (mai.memoryTypeIndex == UINT32_MAX ||
      vkAllocateMemory(g_vk.dev, &mai, NULL, mem) != VK_SUCCESS) {
    vkDestroyBuffer(g_vk.dev, *buf, NULL);
    return MY_RET_FAIL;
  }
  vkBindBufferMemory(g_vk.dev, *buf, *mem, 0);
  return MY_RET_OK;
}

/** @brief Record a one-shot command, submit and wait (uploads only). */
static my_ret_t vk_oneshot(VkCommandBuffer* out_cmd) {
  VkCommandBufferAllocateInfo cai;
  VkCommandBufferBeginInfo bi;
  memset(&cai, 0, sizeof(cai));
  cai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cai.commandPool = g_vk.upload_pool;
  cai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cai.commandBufferCount = 1;
  if (vkAllocateCommandBuffers(g_vk.dev, &cai, out_cmd) != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  memset(&bi, 0, sizeof(bi));
  bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  vkBeginCommandBuffer(*out_cmd, &bi);
  return MY_RET_OK;
}

static my_ret_t vk_oneshot_submit(VkCommandBuffer cmd) {
  VkSubmitInfo si;
  vkEndCommandBuffer(cmd);
  memset(&si, 0, sizeof(si));
  si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  si.commandBufferCount = 1;
  si.pCommandBuffers = &cmd;
  if (vkQueueSubmit(g_vk.queue, 1, &si, VK_NULL_HANDLE) != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  vkQueueWaitIdle(g_vk.queue);
  vkFreeCommandBuffers(g_vk.dev, g_vk.upload_pool, 1, &cmd);
  return MY_RET_OK;
}

static void vk_transition(VkCommandBuffer cmd, VkImage img,
                          VkImageLayout from, VkImageLayout to,
                          VkAccessFlags src_a, VkAccessFlags dst_a,
                          VkPipelineStageFlags src_s,
                          VkPipelineStageFlags dst_s, uint32_t samples_ignored) {
  VkImageMemoryBarrier b;
  (void)samples_ignored;
  memset(&b, 0, sizeof(b));
  b.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  b.oldLayout = from;
  b.newLayout = to;
  b.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  b.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  b.image = img;
  b.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  b.subresourceRange.levelCount = 1;
  b.subresourceRange.layerCount = 1;
  b.srcAccessMask = src_a;
  b.dstAccessMask = dst_a;
  vkCmdPipelineBarrier(cmd, src_s, dst_s, 0, 0, NULL, 0, NULL, 1, &b);
}

/* ---------------- textures ---------------- */

static my_ret_t vk_tex_create(my_vgcanvas_vulkan_t* c, vk_tex_t* t,
                              const uint8_t* pixels, int32_t w, int32_t h,
                              VkFormat fmt, VkSampler sampler) {
  VkImageCreateInfo ici;
  VkMemoryRequirements req;
  VkMemoryAllocateInfo mai;
  VkImageViewCreateInfo vci;
  VkBuffer staging;
  VkDeviceMemory staging_mem;
  void* map;
  VkCommandBuffer cmd;
  VkDescriptorSetAllocateInfo dai;
  VkDescriptorImageInfo dii;
  VkWriteDescriptorSet wr;

  memset(t, 0, sizeof(*t));
  memset(&ici, 0, sizeof(ici));
  ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  ici.imageType = VK_IMAGE_TYPE_2D;
  ici.format = fmt;
  ici.extent.width = (uint32_t)w;
  ici.extent.height = (uint32_t)h;
  ici.extent.depth = 1;
  ici.mipLevels = 1;
  ici.arrayLayers = 1;
  ici.samples = VK_SAMPLE_COUNT_1_BIT;
  ici.tiling = VK_IMAGE_TILING_OPTIMAL;
  ici.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  if (vkCreateImage(g_vk.dev, &ici, NULL, &t->img) != VK_SUCCESS) {
    goto fail;
  }
  vkGetImageMemoryRequirements(g_vk.dev, t->img, &req);
  memset(&mai, 0, sizeof(mai));
  mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mai.allocationSize = req.size;
  mai.memoryTypeIndex = vk_mem_type(req.memoryTypeBits,
                                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  if (mai.memoryTypeIndex == UINT32_MAX ||
      vkAllocateMemory(g_vk.dev, &mai, NULL, &t->mem) != VK_SUCCESS) {
    goto fail;
  }
  vkBindImageMemory(g_vk.dev, t->img, t->mem, 0);
  memset(&vci, 0, sizeof(vci));
  vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  vci.image = t->img;
  vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
  vci.format = fmt;
  vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  vci.subresourceRange.levelCount = 1;
  vci.subresourceRange.layerCount = 1;
  if (vkCreateImageView(g_vk.dev, &vci, NULL, &t->view) != VK_SUCCESS) {
    goto fail;
  }
  /* staging upload (one-shot, synchronous) */
  {
    VkDeviceSize sz = (VkDeviceSize)w * (VkDeviceSize)h *
                      (fmt == VK_FORMAT_R8_UNORM ? 1 : 4);
    if (vk_make_buffer(sz, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                           VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                       &staging, &staging_mem) != MY_RET_OK) {
      goto fail;
    }
    vkMapMemory(g_vk.dev, staging_mem, 0, sz, 0, &map);
    memcpy(map, pixels, (size_t)sz);
    vkUnmapMemory(g_vk.dev, staging_mem);
  }
  if (vk_oneshot(&cmd) != MY_RET_OK) {
    vkDestroyBuffer(g_vk.dev, staging, NULL);
    vkFreeMemory(g_vk.dev, staging_mem, NULL);
    goto fail;
  }
  vk_transition(cmd, t->img, VK_IMAGE_LAYOUT_UNDEFINED,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 0,
                VK_ACCESS_TRANSFER_WRITE_BIT, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
  {
    VkBufferImageCopy cp;
    memset(&cp, 0, sizeof(cp));
    cp.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    cp.imageSubresource.layerCount = 1;
    cp.imageExtent.width = (uint32_t)w;
    cp.imageExtent.height = (uint32_t)h;
    cp.imageExtent.depth = 1;
    vkCmdCopyBufferToImage(cmd, staging, t->img,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &cp);
  }
  vk_transition(cmd, t->img, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0);
  vk_oneshot_submit(cmd);
  vkDestroyBuffer(g_vk.dev, staging, NULL);
  vkFreeMemory(g_vk.dev, staging_mem, NULL);
  /* descriptor */
  memset(&dai, 0, sizeof(dai));
  dai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  dai.descriptorPool = c->ds_pool;
  dai.descriptorSetCount = 1;
  dai.pSetLayouts = &c->ds_layout;
  if (vkAllocateDescriptorSets(g_vk.dev, &dai, &t->ds) != VK_SUCCESS) {
    goto fail;
  }
  memset(&dii, 0, sizeof(dii));
  dii.sampler = sampler;
  dii.imageView = t->view;
  dii.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  memset(&wr, 0, sizeof(wr));
  wr.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  wr.dstSet = t->ds;
  wr.dstBinding = 0;
  wr.descriptorCount = 1;
  wr.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  wr.pImageInfo = &dii;
  vkUpdateDescriptorSets(g_vk.dev, 1, &wr, 0, NULL);
  return MY_RET_OK;

fail:
  /* full cleanup: a partially created texture (img set, ds missing)
   * would otherwise be mistaken for a cache hit and bind a NULL
   * descriptor set */
  if (t->view != VK_NULL_HANDLE) {
    vkDestroyImageView(g_vk.dev, t->view, NULL);
  }
  if (t->img != VK_NULL_HANDLE) {
    vkDestroyImage(g_vk.dev, t->img, NULL);
  }
  if (t->mem != VK_NULL_HANDLE) {
    vkFreeMemory(g_vk.dev, t->mem, NULL);
  }
  memset(t, 0, sizeof(*t));
  return MY_RET_FAIL;
}

static void vk_tex_destroy_now(my_vgcanvas_vulkan_t* c, vk_tex_t* t) {
  if (t->img != VK_NULL_HANDLE) {
    if (t->ds != VK_NULL_HANDLE) {
      vkFreeDescriptorSets(g_vk.dev, c->ds_pool, 1, &t->ds);
      t->ds = VK_NULL_HANDLE;
    }
    vkDestroyImageView(g_vk.dev, t->view, NULL);
    vkDestroyImage(g_vk.dev, t->img, NULL);
    vkFreeMemory(g_vk.dev, t->mem, NULL);
    t->img = VK_NULL_HANDLE;
  }
}

/** @brief Defer a texture's destruction to the reuse of the current frame
 * slot (its fence proves all referencing work has completed). Never
 * destroys synchronously: this runs while a frame may be RECORDING and
 * referencing the texture's descriptor set. */
static bool vk_tex_retire(my_vgcanvas_vulkan_t* c, vk_tex_t* t) {
  size_t idx = c->frame_idx;
  vk_tex_t* grown;
  size_t new_cap;
  if (t->img == VK_NULL_HANDLE) {
    return true;
  }
  if (c->retired_count[idx] + 1 > c->retired_cap[idx]) {
    new_cap = c->retired_cap[idx] > 0 ? c->retired_cap[idx] * 2 : 32;
    grown = (vk_tex_t*)my_mem_realloc(c->allocator, c->retired[idx],
                                      new_cap * sizeof(vk_tex_t));
    if (grown == NULL) {
      return false;
    }
    c->retired[idx] = grown;
    c->retired_cap[idx] = new_cap;
  }
  c->retired[idx][c->retired_count[idx]++] = *t;
  memset(t, 0, sizeof(*t)); /* the cache slot is free again */
  return true;
}

/** @brief Really destroy everything retired into `slot` (called right
 * after that slot's fence was waited, so the GPU is done with them). */
static void vk_retire_collect(my_vgcanvas_vulkan_t* c, uint32_t slot) {
  size_t i;
  for (i = 0; i < c->retired_count[slot]; i++) {
    vk_tex_destroy_now(c, &c->retired[slot][i]);
  }
  c->retired_count[slot] = 0;
}

/* ---------------- render targets (swapchain / offscreen) ---------------- */

static void vk_destroy_targets(my_vgcanvas_vulkan_t* c) {
  uint32_t i;
  for (i = 0; i < c->img_count; i++) {
    if (c->fbs[i] != VK_NULL_HANDLE) {
      vkDestroyFramebuffer(g_vk.dev, c->fbs[i], NULL);
      c->fbs[i] = VK_NULL_HANDLE;
    }
    if (c->resolve_fbs[i] != VK_NULL_HANDLE) {
      vkDestroyFramebuffer(g_vk.dev, c->resolve_fbs[i], NULL);
      c->resolve_fbs[i] = VK_NULL_HANDLE;
    }
    if (c->target_views[i] != VK_NULL_HANDLE) {
      vkDestroyImageView(g_vk.dev, c->target_views[i], NULL);
      c->target_views[i] = VK_NULL_HANDLE;
    }
  }
  if (c->msaa_view != VK_NULL_HANDLE) {
    vkDestroyImageView(g_vk.dev, c->msaa_view, NULL);
    c->msaa_view = VK_NULL_HANDLE;
  }
  if (c->msaa_img != VK_NULL_HANDLE) {
    vkDestroyImage(g_vk.dev, c->msaa_img, NULL);
    c->msaa_img = VK_NULL_HANDLE;
  }
  if (c->msaa_mem != VK_NULL_HANDLE) {
    vkFreeMemory(g_vk.dev, c->msaa_mem, NULL);
    c->msaa_mem = VK_NULL_HANDLE;
  }
  if (c->swapchain != VK_NULL_HANDLE) {
    vkDestroySwapchainKHR(g_vk.dev, c->swapchain, NULL);
    c->swapchain = VK_NULL_HANDLE;
  }
  if (c->offscreen && c->target_imgs[0] != VK_NULL_HANDLE) {
    vkDestroyImage(g_vk.dev, c->target_imgs[0], NULL);
    c->target_imgs[0] = VK_NULL_HANDLE;
  }
  if (c->offscreen_mem != VK_NULL_HANDLE) {
    vkFreeMemory(g_vk.dev, c->offscreen_mem, NULL);
    c->offscreen_mem = VK_NULL_HANDLE;
  }
  c->img_count = 0;
}

static void vk_clear_resource_handles(my_vgcanvas_vulkan_t* c) {
  uint32_t i;
  c->swapchain = VK_NULL_HANDLE;
  c->img_count = 0;
  c->offscreen_mem = VK_NULL_HANDLE;
  c->msaa_img = VK_NULL_HANDLE;
  c->msaa_mem = VK_NULL_HANDLE;
  c->msaa_view = VK_NULL_HANDLE;
  c->renderpass = VK_NULL_HANDLE;
  c->resolve_rp = VK_NULL_HANDLE;
  c->ds_layout = VK_NULL_HANDLE;
  c->ds_pool = VK_NULL_HANDLE;
  c->sampler = VK_NULL_HANDLE;
  c->nearest_sampler = VK_NULL_HANDLE;
  c->pipe_layout = VK_NULL_HANDLE;
  c->pipe_flat = VK_NULL_HANDLE;
  c->pipe_text = VK_NULL_HANDLE;
  c->pipe_img = VK_NULL_HANDLE;
  for (i = 0; i < VKC_MAX_IMGS; i++) {
    c->target_imgs[i] = VK_NULL_HANDLE;
    c->target_views[i] = VK_NULL_HANDLE;
    c->fbs[i] = VK_NULL_HANDLE;
    c->resolve_fbs[i] = VK_NULL_HANDLE;
    c->pending_fb[i] = VK_NULL_HANDLE;
  }
}

static void vk_destroy_resource_handles(my_vgcanvas_vulkan_t* c) {
  if (c == NULL) {
    return;
  }
  vk_destroy_targets(c);
  if (c->pipe_flat != VK_NULL_HANDLE) {
    vkDestroyPipeline(g_vk.dev, c->pipe_flat, NULL);
  }
  if (c->pipe_text != VK_NULL_HANDLE) {
    vkDestroyPipeline(g_vk.dev, c->pipe_text, NULL);
  }
  if (c->pipe_img != VK_NULL_HANDLE) {
    vkDestroyPipeline(g_vk.dev, c->pipe_img, NULL);
  }
  if (c->pipe_layout != VK_NULL_HANDLE) {
    vkDestroyPipelineLayout(g_vk.dev, c->pipe_layout, NULL);
  }
  if (c->ds_pool != VK_NULL_HANDLE) {
    vkDestroyDescriptorPool(g_vk.dev, c->ds_pool, NULL);
  }
  if (c->ds_layout != VK_NULL_HANDLE) {
    vkDestroyDescriptorSetLayout(g_vk.dev, c->ds_layout, NULL);
  }
  if (c->sampler != VK_NULL_HANDLE) {
    vkDestroySampler(g_vk.dev, c->sampler, NULL);
  }
  if (c->nearest_sampler != VK_NULL_HANDLE) {
    vkDestroySampler(g_vk.dev, c->nearest_sampler, NULL);
  }
  if (c->renderpass != VK_NULL_HANDLE) {
    vkDestroyRenderPass(g_vk.dev, c->renderpass, NULL);
  }
  if (c->resolve_rp != VK_NULL_HANDLE) {
    vkDestroyRenderPass(g_vk.dev, c->resolve_rp, NULL);
  }
  vk_clear_resource_handles(c);
}

static void vk_swap_resource_handles(my_vgcanvas_vulkan_t* a,
                                     my_vgcanvas_vulkan_t* b) {
  my_vgcanvas_vulkan_t tmp = *a;
  a->swapchain = b->swapchain;
  a->format = b->format;
  a->samples = b->samples;
  a->img_count = b->img_count;
  memcpy(a->target_imgs, b->target_imgs, sizeof(a->target_imgs));
  memcpy(a->target_views, b->target_views, sizeof(a->target_views));
  memcpy(a->fbs, b->fbs, sizeof(a->fbs));
  a->offscreen_mem = b->offscreen_mem;
  a->msaa_img = b->msaa_img;
  a->msaa_mem = b->msaa_mem;
  a->msaa_view = b->msaa_view;
  a->renderpass = b->renderpass;
  a->resolve_rp = b->resolve_rp;
  memcpy(a->resolve_fbs, b->resolve_fbs, sizeof(a->resolve_fbs));
  memcpy(a->pending_fb, b->pending_fb, sizeof(a->pending_fb));
  a->ds_layout = b->ds_layout;
  a->ds_pool = b->ds_pool;
  a->sampler = b->sampler;
  a->nearest_sampler = b->nearest_sampler;
  a->pipe_layout = b->pipe_layout;
  a->pipe_flat = b->pipe_flat;
  a->pipe_text = b->pipe_text;
  a->pipe_img = b->pipe_img;

  b->swapchain = tmp.swapchain;
  b->format = tmp.format;
  b->samples = tmp.samples;
  b->img_count = tmp.img_count;
  memcpy(b->target_imgs, tmp.target_imgs, sizeof(b->target_imgs));
  memcpy(b->target_views, tmp.target_views, sizeof(b->target_views));
  memcpy(b->fbs, tmp.fbs, sizeof(b->fbs));
  b->offscreen_mem = tmp.offscreen_mem;
  b->msaa_img = tmp.msaa_img;
  b->msaa_mem = tmp.msaa_mem;
  b->msaa_view = tmp.msaa_view;
  b->renderpass = tmp.renderpass;
  b->resolve_rp = tmp.resolve_rp;
  memcpy(b->resolve_fbs, tmp.resolve_fbs, sizeof(b->resolve_fbs));
  memcpy(b->pending_fb, tmp.pending_fb, sizeof(b->pending_fb));
  b->ds_layout = tmp.ds_layout;
  b->ds_pool = tmp.ds_pool;
  b->sampler = tmp.sampler;
  b->nearest_sampler = tmp.nearest_sampler;
  b->pipe_layout = tmp.pipe_layout;
  b->pipe_flat = tmp.pipe_flat;
  b->pipe_text = tmp.pipe_text;
  b->pipe_img = tmp.pipe_img;
}

/** @brief Create the MSAA color image when samples > 1. */
static my_ret_t vk_create_msaa(my_vgcanvas_vulkan_t* c) {
  VkImageCreateInfo ici;
  VkMemoryRequirements req;
  VkMemoryAllocateInfo mai;
  VkImageViewCreateInfo vci;
  if (c->samples == VK_SAMPLE_COUNT_1_BIT) {
    return MY_RET_OK;
  }
  memset(&ici, 0, sizeof(ici));
  ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  ici.imageType = VK_IMAGE_TYPE_2D;
  ici.format = c->format;
  ici.extent.width = (uint32_t)c->fb_w;
  ici.extent.height = (uint32_t)c->fb_h;
  ici.extent.depth = 1;
  ici.mipLevels = 1;
  ici.arrayLayers = 1;
  ici.samples = c->samples;
  ici.tiling = VK_IMAGE_TILING_OPTIMAL;
  ici.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
              VK_IMAGE_USAGE_TRANSFER_DST_BIT | /* creation-time clear */
              VK_IMAGE_USAGE_TRANSFER_SRC_BIT;  /* resolve source */
  ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  if (vkCreateImage(g_vk.dev, &ici, NULL, &c->msaa_img) != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  vkGetImageMemoryRequirements(g_vk.dev, c->msaa_img, &req);
  memset(&mai, 0, sizeof(mai));
  mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mai.allocationSize = req.size;
  mai.memoryTypeIndex = vk_mem_type(req.memoryTypeBits,
                                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  if (mai.memoryTypeIndex == UINT32_MAX ||
      vkAllocateMemory(g_vk.dev, &mai, NULL, &c->msaa_mem) != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  vkBindImageMemory(g_vk.dev, c->msaa_img, c->msaa_mem, 0);
  memset(&vci, 0, sizeof(vci));
  vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  vci.image = c->msaa_img;
  vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
  vci.format = c->format;
  vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  vci.subresourceRange.levelCount = 1;
  vci.subresourceRange.layerCount = 1;
  return vkCreateImageView(g_vk.dev, &vci, NULL, &c->msaa_view) ==
                 VK_SUCCESS
             ? MY_RET_OK
             : MY_RET_FAIL;
}

static my_ret_t vk_create_framebuffers(my_vgcanvas_vulkan_t* c) {
  uint32_t i;
  for (i = 0; i < c->img_count; i++) {
    VkFramebufferCreateInfo fci;
    /* one attachment: the persistent MSAA image (samples > 1) or the
     * target itself */
    VkImageView att = c->samples != VK_SAMPLE_COUNT_1_BIT
                          ? c->msaa_view
                          : c->target_views[i];
    memset(&fci, 0, sizeof(fci));
    fci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fci.renderPass = c->renderpass;
    fci.attachmentCount = 1;
    fci.pAttachments = &att;
    fci.width = (uint32_t)c->fb_w;
    fci.height = (uint32_t)c->fb_h;
    fci.layers = 1;
    if (vkCreateFramebuffer(g_vk.dev, &fci, NULL, &c->fbs[i]) !=
        VK_SUCCESS) {
      return MY_RET_FAIL;
    }
  }
  return MY_RET_OK;
}

/** @brief M25c: zero-draw resolve renderpass for the windowed MSAA
 * path: the subpass color attachment is the persistent MSAA image
 * (LOAD/STORE), the resolve attachment the swapchain image — so the
 * swapchain needs no TRANSFER usages (WSI dmabuf constraint). */
static my_ret_t vk_create_resolve_rp(my_vgcanvas_vulkan_t* c) {
  VkAttachmentDescription atts[2];
  VkAttachmentReference color_ref, resolve_ref;
  VkSubpassDescription sub;
  VkSubpassDependency dep;
  VkRenderPassCreateInfo ri;
  uint32_t i;
  if ((c->offscreen && getenv("MYUI_VK_RPRESOLVE") == NULL) ||
      c->samples == VK_SAMPLE_COUNT_1_BIT) {
    return MY_RET_OK;
  }
  if (c->resolve_rp != VK_NULL_HANDLE) {
    /* swapchain recreation: the renderpass is format/samples-invariant,
     * but rebuild it cleanly instead of leaking the old one */
    vkDestroyRenderPass(g_vk.dev, c->resolve_rp, NULL);
    c->resolve_rp = VK_NULL_HANDLE;
  }
  memset(atts, 0, sizeof(atts));
  atts[0].format = c->format;
  atts[0].samples = c->samples;
  atts[0].loadOp = VK_ATTACHMENT_LOAD_OP_LOAD; /* persistent history */
  atts[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  atts[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  atts[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  atts[0].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  atts[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  atts[1].format = c->format;
  atts[1].samples = VK_SAMPLE_COUNT_1_BIT;
  atts[1].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE; /* fully resolved over */
  atts[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  atts[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  atts[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  atts[1].initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
  atts[1].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
  memset(&color_ref, 0, sizeof(color_ref));
  color_ref.attachment = 0;
  color_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  memset(&resolve_ref, 0, sizeof(resolve_ref));
  resolve_ref.attachment = 1;
  resolve_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  memset(&sub, 0, sizeof(sub));
  sub.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  sub.colorAttachmentCount = 1;
  sub.pColorAttachments = &color_ref;
  sub.pResolveAttachments = &resolve_ref;
  memset(&dep, 0, sizeof(dep));
  dep.srcSubpass = VK_SUBPASS_EXTERNAL;
  dep.dstSubpass = 0;
  /* M25 fix: cover prior reads (resolve source) as well as writes */
  dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
                      VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
  dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  memset(&ri, 0, sizeof(ri));
  ri.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  ri.attachmentCount = 2;
  ri.pAttachments = atts;
  ri.subpassCount = 1;
  ri.pSubpasses = &sub;
  ri.dependencyCount = 1;
  ri.pDependencies = &dep;
  if (vkCreateRenderPass(g_vk.dev, &ri, NULL, &c->resolve_rp) !=
      VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  for (i = 0; i < c->img_count; i++) {
    VkImageView atts2[2];
    VkFramebufferCreateInfo fci;
    atts2[0] = c->msaa_view;
    atts2[1] = c->target_views[i];
    memset(&fci, 0, sizeof(fci));
    fci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fci.renderPass = c->resolve_rp;
    fci.attachmentCount = 2;
    fci.pAttachments = atts2;
    fci.width = (uint32_t)c->fb_w;
    fci.height = (uint32_t)c->fb_h;
    fci.layers = 1;
    if (vkCreateFramebuffer(g_vk.dev, &fci, NULL, &c->resolve_fbs[i]) !=
        VK_SUCCESS) {
      return MY_RET_FAIL;
    }
  }
  return MY_RET_OK;
}

/** @brief One-shot layout transitions + initial clear right after
 * (re)creating images (fresh images contain garbage; clear to
 * transparent black so untouched pixels are deterministic). */
static my_ret_t vk_pre_transition_targets(my_vgcanvas_vulkan_t* c) {
  VkCommandBuffer cmd;
  uint32_t i;
  VkClearColorValue black;
  VkImageSubresourceRange range;
  VkImageLayout home = c->offscreen ? VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
                                    : VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
  memset(&black, 0, sizeof(black));
  memset(&range, 0, sizeof(range));
  range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  range.levelCount = 1;
  range.layerCount = 1;
  if (!c->offscreen) {
    /* M25c: swapchain images may not carry TRANSFER_DST (WSI dmabuf
     * constraint), so the initial clear is a one-time CLEAR renderpass
     * per image (transient: created, used and destroyed here) */
    VkAttachmentDescription att;
    VkAttachmentReference ref;
    VkSubpassDescription sub;
    VkRenderPassCreateInfo ri;
    VkRenderPass clear_rp = VK_NULL_HANDLE;
    memset(&att, 0, sizeof(att));
    att.format = c->format;
    att.samples = VK_SAMPLE_COUNT_1_BIT;
    att.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    att.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    att.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    memset(&ref, 0, sizeof(ref));
    ref.attachment = 0;
    ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    memset(&sub, 0, sizeof(sub));
    sub.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sub.colorAttachmentCount = 1;
    sub.pColorAttachments = &ref;
    memset(&ri, 0, sizeof(ri));
    ri.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    ri.attachmentCount = 1;
    ri.pAttachments = &att;
    ri.subpassCount = 1;
    ri.pSubpasses = &sub;
    if (vkCreateRenderPass(g_vk.dev, &ri, NULL, &clear_rp) != VK_SUCCESS) {
      return MY_RET_FAIL;
    }
    if (vk_oneshot(&cmd) == MY_RET_OK) {
      for (i = 0; i < c->img_count; i++) {
        VkFramebufferCreateInfo fci;
        VkFramebuffer fb = VK_NULL_HANDLE;
        VkRenderPassBeginInfo rbi;
        VkClearValue clear;
        memset(&clear, 0, sizeof(clear));
        memset(&fci, 0, sizeof(fci));
        fci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        fci.renderPass = clear_rp;
        fci.attachmentCount = 1;
        fci.pAttachments = &c->target_views[i];
        fci.width = (uint32_t)c->fb_w;
        fci.height = (uint32_t)c->fb_h;
        fci.layers = 1;
        if (vkCreateFramebuffer(g_vk.dev, &fci, NULL, &fb) != VK_SUCCESS) {
          continue;
        }
        memset(&rbi, 0, sizeof(rbi));
        rbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        rbi.renderPass = clear_rp;
        rbi.framebuffer = fb;
        rbi.renderArea.extent.width = (uint32_t)c->fb_w;
        rbi.renderArea.extent.height = (uint32_t)c->fb_h;
        rbi.clearValueCount = 1;
        rbi.pClearValues = &clear;
        vkCmdBeginRenderPass(cmd, &rbi, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdEndRenderPass(cmd);
        c->pending_fb[i] = fb; /* destroyed after the submit below */
      }
      vk_oneshot_submit(cmd);
      for (i = 0; i < c->img_count; i++) {
        if (c->pending_fb[i] != VK_NULL_HANDLE) {
          vkDestroyFramebuffer(g_vk.dev, c->pending_fb[i], NULL);
          c->pending_fb[i] = VK_NULL_HANDLE;
        }
      }
    }
    vkDestroyRenderPass(g_vk.dev, clear_rp, NULL);
  } else if (vk_oneshot(&cmd) == MY_RET_OK) {
    for (i = 0; i < c->img_count; i++) {
      vk_transition(cmd, c->target_imgs[i], VK_IMAGE_LAYOUT_UNDEFINED,
                    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 0,
                    VK_ACCESS_TRANSFER_WRITE_BIT,
                    VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                    VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
      vkCmdClearColorImage(cmd, c->target_imgs[i],
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &black, 1,
                           &range);
      vk_transition(cmd, c->target_imgs[i],
                    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, home,
                    VK_ACCESS_TRANSFER_WRITE_BIT,
                    VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                        VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                    VK_PIPELINE_STAGE_TRANSFER_BIT,
                    VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0);
    }
    vk_oneshot_submit(cmd);
  }
  /* the MSAA image is private (not a WSI swapchain image): a plain
   * transfer clear is fine */
  if (c->msaa_img != VK_NULL_HANDLE) {
    if (vk_oneshot(&cmd) != MY_RET_OK) {
      return MY_RET_FAIL;
    }
    vk_transition(cmd, c->msaa_img, VK_IMAGE_LAYOUT_UNDEFINED,
                  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 0,
                  VK_ACCESS_TRANSFER_WRITE_BIT,
                  VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                  VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
    vkCmdClearColorImage(cmd, c->msaa_img,
                         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &black, 1,
                         &range);
    vk_transition(cmd, c->msaa_img, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                  VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                  VK_ACCESS_TRANSFER_WRITE_BIT,
                  VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                  VK_PIPELINE_STAGE_TRANSFER_BIT,
                  VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0);
    return vk_oneshot_submit(cmd);
  }
  return MY_RET_OK;
}

static my_ret_t vk_create_renderpass(my_vgcanvas_vulkan_t* c) {
  VkAttachmentDescription att;
  VkAttachmentReference color_ref;
  VkSubpassDescription sub;
  VkSubpassDependency dep;
  VkRenderPassCreateInfo ri;
  /* the target image lives in this layout BETWEEN frames; the subpass
   * transitions in and out of COLOR_ATTACHMENT_OPTIMAL automatically.
   * loadOp=LOAD preserves the previous frame's content: partial
   * (dirty-rect) repaints stay correct (M25b). */
  VkImageLayout home = c->offscreen ? VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
                                    : VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  memset(&att, 0, sizeof(att));
  memset(&ri, 0, sizeof(ri));
  if (c->samples != VK_SAMPLE_COUNT_1_BIT) {
    /* single attachment: the persistent MSAA color image (manual
     * dirty-union resolve into the target at frame end) */
    att.format = c->format;
    att.samples = c->samples;
    att.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    att.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    att.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    att.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  } else {
    att.format = c->format;
    att.samples = VK_SAMPLE_COUNT_1_BIT;
    att.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    att.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    att.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att.initialLayout = home;
    att.finalLayout = home;
  }
  memset(&color_ref, 0, sizeof(color_ref));
  color_ref.attachment = 0;
  color_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  memset(&sub, 0, sizeof(sub));
  sub.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  sub.colorAttachmentCount = 1;
  sub.pColorAttachments = &color_ref;
  memset(&dep, 0, sizeof(dep));
  dep.srcSubpass = VK_SUBPASS_EXTERNAL;
  dep.dstSubpass = 0;
  /* M25 fix: with VKC_FRAMES=2 in flight, frame N+1's render into the ONE
   * persistent MSAA image may overlap frame N's resolve READING it (its
   * begin_frame only waited the N-1 fence). srcStage/srcAccess therefore
   * cover color READS (resolve source) and TRANSFER reads (offscreen
   * resolve), ordering this renderpass behind those reads. */
  dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                     VK_PIPELINE_STAGE_TRANSFER_BIT;
  dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
                      VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                      VK_ACCESS_TRANSFER_READ_BIT;
  dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  ri.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  ri.attachmentCount = 1;
  ri.pAttachments = &att;
  ri.subpassCount = 1;
  ri.pSubpasses = &sub;
  ri.dependencyCount = 1;
  ri.pDependencies = &dep;
  return vkCreateRenderPass(g_vk.dev, &ri, NULL, &c->renderpass) ==
                 VK_SUCCESS
             ? MY_RET_OK
             : MY_RET_FAIL;
}

/** @brief (Re)create the render targets after create/resize. */
static my_ret_t vk_create_targets(my_vgcanvas_vulkan_t* c) {
  VkImageViewCreateInfo vci;
  uint32_t i;
  vkDeviceWaitIdle(g_vk.dev);
  vk_destroy_targets(c);
  if (c->samples == 0) {
    /* first creation: offscreen prefers 4x MSAA; windowed defaults to
     * single-sample because some drivers (Mesa ANV) produce wider edge
     * transitions in windowed MSAA than the reference soft backend.
     * MYUI_VK_MSAA=1 forces windowed 4x; MYUI_VK_NOMSAA=1 disables MSAA. */
    VkPhysicalDeviceProperties props;
    uint32_t sample_counts;
    vkGetPhysicalDeviceProperties(g_vk.pdev, &props);
    sample_counts = (uint32_t)props.limits.framebufferColorSampleCounts;
    c->samples = (sample_counts & VK_SAMPLE_COUNT_4_BIT) != 0
                     ? VK_SAMPLE_COUNT_4_BIT
                     : VK_SAMPLE_COUNT_1_BIT;
    if (!c->offscreen) {
      c->samples = VK_SAMPLE_COUNT_1_BIT;
    }
    if (getenv("MYUI_VK_MSAA") != NULL &&
        (sample_counts & VK_SAMPLE_COUNT_4_BIT) != 0u) {
      c->samples = VK_SAMPLE_COUNT_4_BIT;
    }
    if (getenv("MYUI_VK_NOMSAA") != NULL) {
      c->samples = VK_SAMPLE_COUNT_1_BIT;
    }
  }
  if (c->offscreen) {
    VkImageCreateInfo ici;
    VkMemoryRequirements req;
    VkMemoryAllocateInfo mai;
    c->format = VK_FORMAT_R8G8B8A8_UNORM;
    c->img_count = 1;
    memset(&ici, 0, sizeof(ici));
    ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ici.imageType = VK_IMAGE_TYPE_2D;
    ici.format = c->format;
    ici.extent.width = (uint32_t)c->fb_w;
    ici.extent.height = (uint32_t)c->fb_h;
    ici.extent.depth = 1;
    ici.mipLevels = 1;
    ici.arrayLayers = 1;
    ici.samples = VK_SAMPLE_COUNT_1_BIT;
    ici.tiling = VK_IMAGE_TILING_OPTIMAL;
    ici.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
                VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(g_vk.dev, &ici, NULL, &c->target_imgs[0]) !=
        VK_SUCCESS) {
      return MY_RET_FAIL;
    }
    vkGetImageMemoryRequirements(g_vk.dev, c->target_imgs[0], &req);
    memset(&mai, 0, sizeof(mai));
    mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mai.allocationSize = req.size;
    mai.memoryTypeIndex = vk_mem_type(req.memoryTypeBits,
                                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (mai.memoryTypeIndex == UINT32_MAX ||
        vkAllocateMemory(g_vk.dev, &mai, NULL, &c->offscreen_mem) !=
            VK_SUCCESS) {
      return MY_RET_FAIL;
    }
    vkBindImageMemory(g_vk.dev, c->target_imgs[0], c->offscreen_mem, 0);
    /* offscreen: the single-sample target is rendered/resolved into
     * directly; MSAA resolve also targets it */
  } else {
    VkSurfaceCapabilitiesKHR caps;
    VkSwapchainCreateInfoKHR sci;
    VkSurfaceFormatKHR fmts[16];
    uint32_t nfmt = 0;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(g_vk.pdev, c->surface,
                                                  &caps) != VK_SUCCESS) {
      return MY_RET_FAIL;
    }
    if (vkGetPhysicalDeviceSurfaceFormatsKHR(g_vk.pdev, c->surface, &nfmt,
                                             NULL) != VK_SUCCESS ||
        nfmt == 0) {
      return MY_RET_FAIL;
    }
    if (nfmt > 16) {
      nfmt = 16;
    }
    vkGetPhysicalDeviceSurfaceFormatsKHR(g_vk.pdev, c->surface, &nfmt,
                                         fmts);
    c->format = fmts[0].format;
    for (i = 0; i < nfmt; i++) {
      if (fmts[i].format == VK_FORMAT_B8G8R8A8_UNORM) {
        c->format = fmts[i].format;
      }
    }
    memset(&sci, 0, sizeof(sci));
    sci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    sci.surface = c->surface;
    sci.minImageCount = caps.minImageCount + 1;
    if (caps.maxImageCount > 0 && sci.minImageCount > caps.maxImageCount) {
      sci.minImageCount = caps.maxImageCount;
    }
    sci.imageFormat = c->format;
    sci.imageColorSpace = fmts[0].colorSpace;
    sci.imageExtent.width = (uint32_t)c->fb_w;
    sci.imageExtent.height = (uint32_t)c->fb_h;
    sci.imageArrayLayers = 1;
    /* M25c: COLOR_ATTACHMENT ONLY. Mesa's wayland WSI rejects transfer
     * usages on swapchain images for the dmabuf path (falls back to
     * wl_shm, which the compositor's explicit-sync protocol then
     * rejects). The creation-time clear and the MSAA resolve are done
     * with renderpasses instead (vk_pre_transition_targets / flush). */
    sci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    sci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    sci.preTransform = caps.currentTransform;
    sci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    sci.presentMode = VK_PRESENT_MODE_FIFO_KHR; /* vsync, guaranteed */
    sci.clipped = VK_TRUE;
    if (getenv("MYUI_VK_DEBUG") != NULL) {
      fprintf(stderr,
              "[vkdbg] swapchain: fb=%dx%d caps.currentExtent=%ux%u "
              "samples=%d\n",
              (int)c->fb_w, (int)c->fb_h, caps.currentExtent.width,
              caps.currentExtent.height, (int)c->samples);
    }
    if (vkCreateSwapchainKHR(g_vk.dev, &sci, NULL, &c->swapchain) !=
        VK_SUCCESS) {
      return MY_RET_FAIL;
    }
    if (vkGetSwapchainImagesKHR(g_vk.dev, c->swapchain, &c->img_count,
                                NULL) != VK_SUCCESS ||
        c->img_count == 0 || c->img_count > VKC_MAX_IMGS) {
      return MY_RET_FAIL;
    }
    vkGetSwapchainImagesKHR(g_vk.dev, c->swapchain, &c->img_count,
                            c->target_imgs);
  }
  /* views + msaa + framebuffers */
  for (i = 0; i < c->img_count; i++) {
    memset(&vci, 0, sizeof(vci));
    vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image = c->target_imgs[i];
    vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    vci.format = c->format;
    vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    vci.subresourceRange.levelCount = 1;
    vci.subresourceRange.layerCount = 1;
    if (vkCreateImageView(g_vk.dev, &vci, NULL, &c->target_views[i]) !=
        VK_SUCCESS) {
      return MY_RET_FAIL;
    }
  }
  if (c->renderpass == VK_NULL_HANDLE &&
      vk_create_renderpass(c) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (vk_create_msaa(c) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (vk_create_framebuffers(c) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (vk_create_resolve_rp(c) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  return vk_pre_transition_targets(c);
}

/* ---------------- pipelines ---------------- */

static VkShaderModule vk_shader(const uint32_t* words, size_t byte_len) {
  VkShaderModuleCreateInfo ci;
  VkShaderModule mod = VK_NULL_HANDLE;
  memset(&ci, 0, sizeof(ci));
  ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  ci.codeSize = byte_len;
  ci.pCode = words;
  if (vkCreateShaderModule(g_vk.dev, &ci, NULL, &mod) != VK_SUCCESS) {
    return VK_NULL_HANDLE;
  }
  return mod;
}

static my_ret_t vk_create_pipelines(my_vgcanvas_vulkan_t* c) {
  VkPushConstantRange pcr;
  VkPipelineLayoutCreateInfo lci;
  VkDescriptorSetLayoutBinding bind;
  VkDescriptorSetLayoutCreateInfo dci;
  VkDescriptorPoolSize pool_size;
  VkDescriptorPoolCreateInfo pci;
  VkSamplerCreateInfo sci;

  /* Shared clamp samplers; image filtering changes only the sampler bound
   * in the image descriptor, while glyphs always use linear sampling. */
  memset(&sci, 0, sizeof(sci));
  sci.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  sci.magFilter = VK_FILTER_LINEAR;
  sci.minFilter = VK_FILTER_LINEAR;
  sci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  sci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  sci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
  if (vkCreateSampler(g_vk.dev, &sci, NULL, &c->sampler) != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  sci.magFilter = VK_FILTER_NEAREST;
  sci.minFilter = VK_FILTER_NEAREST;
  if (vkCreateSampler(g_vk.dev, &sci, NULL, &c->nearest_sampler) !=
      VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  /* descriptor set layout: one combined image sampler at binding 0 */
  memset(&bind, 0, sizeof(bind));
  bind.binding = 0;
  bind.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  bind.descriptorCount = 1;
  bind.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  memset(&dci, 0, sizeof(dci));
  dci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  dci.bindingCount = 1;
  dci.pBindings = &bind;
  if (vkCreateDescriptorSetLayout(g_vk.dev, &dci, NULL, &c->ds_layout) !=
      VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  memset(&pool_size, 0, sizeof(pool_size));
  pool_size.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  pool_size.descriptorCount = 256;
  memset(&pci, 0, sizeof(pci));
  pci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pci.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
  pci.maxSets = 256;
  pci.poolSizeCount = 1;
  pci.pPoolSizes = &pool_size;
  if (vkCreateDescriptorPool(g_vk.dev, &pci, NULL, &c->ds_pool) !=
      VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  /* layout: push constants (resolution + color) + one texture set */
  memset(&pcr, 0, sizeof(pcr));
  pcr.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
  pcr.offset = 0;
  pcr.size = VKC_PUSH_SIZE;
  memset(&lci, 0, sizeof(lci));
  lci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  lci.setLayoutCount = 1;
  lci.pSetLayouts = &c->ds_layout;
  lci.pushConstantRangeCount = 1;
  lci.pPushConstantRanges = &pcr;
  if (vkCreatePipelineLayout(g_vk.dev, &lci, NULL, &c->pipe_layout) !=
      VK_SUCCESS) {
    return MY_RET_FAIL;
  }

  {
    VkPipelineVertexInputStateCreateInfo vi;
    VkVertexInputBindingDescription vi_b;
    VkVertexInputAttributeDescription vi_a[2];
    VkPipelineInputAssemblyStateCreateInfo ia;
    VkPipelineViewportStateCreateInfo vp;
    VkPipelineRasterizationStateCreateInfo rs;
    VkPipelineMultisampleStateCreateInfo ms;
    VkPipelineColorBlendAttachmentState cba;
    VkPipelineColorBlendStateCreateInfo cb;
    VkDynamicState dyn_states[2];
    VkPipelineDynamicStateCreateInfo dyn;
    VkPipelineShaderStageCreateInfo stages[2];
    VkGraphicsPipelineCreateInfo pi;
    VkShaderModule mods[3];
    int pipe_idx;

    memset(&vi_b, 0, sizeof(vi_b));
    memset(vi_a, 0, sizeof(vi_a));
    memset(&vi, 0, sizeof(vi));
    memset(&ia, 0, sizeof(ia));
    memset(&vp, 0, sizeof(vp));
    memset(&rs, 0, sizeof(rs));
    memset(&ms, 0, sizeof(ms));
    memset(&cba, 0, sizeof(cba));
    memset(&cb, 0, sizeof(cb));
    memset(&dyn, 0, sizeof(dyn));
    memset(stages, 0, sizeof(stages));
    memset(&pi, 0, sizeof(pi));

    mods[0] = vk_shader(VKSPV_FLAT_VERT, sizeof(VKSPV_FLAT_VERT));
    mods[1] = vk_shader(VKSPV_TEX_VERT, sizeof(VKSPV_TEX_VERT));
    mods[2] = NULL; /* per-pipe fragment module below */

    ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vp.viewportCount = 1;
    vp.scissorCount = 1; /* dynamic */
    rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rs.polygonMode = VK_POLYGON_MODE_FILL;
    rs.cullMode = VK_CULL_MODE_NONE;
    rs.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rs.lineWidth = 1.0f;
    ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    ms.rasterizationSamples = c->samples;
    cba.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                         VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    cba.blendEnable = VK_TRUE;
    cba.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    cba.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    cba.colorBlendOp = VK_BLEND_OP_ADD;
    cba.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    cba.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    cba.alphaBlendOp = VK_BLEND_OP_ADD;
    cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    cb.attachmentCount = 1;
    cb.pAttachments = &cba;
    dyn_states[0] = VK_DYNAMIC_STATE_VIEWPORT;
    dyn_states[1] = VK_DYNAMIC_STATE_SCISSOR;
    dyn.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dyn.dynamicStateCount = 2;
    dyn.pDynamicStates = dyn_states;
    stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    stages[0].pName = "main";
    stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    stages[1].pName = "main";
    vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vi.vertexBindingDescriptionCount = 1;
    vi.pVertexBindingDescriptions = &vi_b;
    vi.pVertexAttributeDescriptions = vi_a;
    pi.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pi.stageCount = 2;
    pi.pStages = stages;
    pi.pVertexInputState = &vi;
    pi.pInputAssemblyState = &ia;
    pi.pViewportState = &vp;
    pi.pRasterizationState = &rs;
    pi.pMultisampleState = &ms;
    pi.pColorBlendState = &cb;
    pi.pDynamicState = &dyn;
    pi.layout = c->pipe_layout;
    pi.renderPass = c->renderpass;
    pi.subpass = 0;

    for (pipe_idx = 0; pipe_idx < 3 && mods[0] != VK_NULL_HANDLE &&
                        mods[1] != VK_NULL_HANDLE;
         pipe_idx++) {
      VkShaderModule fs_mod = VK_NULL_HANDLE;
      VkPipeline* out = pipe_idx == 0   ? &c->pipe_flat
                        : pipe_idx == 1 ? &c->pipe_text
                                        : &c->pipe_img;
      if (pipe_idx == 0) {
        /* flat: vec2 positions */
        vi_b.binding = 0;
        vi_b.stride = 8;
        vi_b.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        vi_a[0].location = 0;
        vi_a[0].binding = 0;
        vi_a[0].format = VK_FORMAT_R32G32_SFLOAT;
        vi_a[0].offset = 0;
        vi.vertexAttributeDescriptionCount = 1;
        stages[0].module = mods[0];
        fs_mod = vk_shader(VKSPV_FLAT_FRAG, sizeof(VKSPV_FLAT_FRAG));
      } else {
        /* textured: vec2 pos + vec2 uv */
        vi_b.binding = 0;
        vi_b.stride = 16;
        vi_b.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        vi_a[0].location = 0;
        vi_a[0].binding = 0;
        vi_a[0].format = VK_FORMAT_R32G32_SFLOAT;
        vi_a[0].offset = 0;
        vi_a[1].location = 1;
        vi_a[1].binding = 0;
        vi_a[1].format = VK_FORMAT_R32G32_SFLOAT;
        vi_a[1].offset = 8;
        vi.vertexAttributeDescriptionCount = 2;
        stages[0].module = mods[1];
        fs_mod = pipe_idx == 1
                     ? vk_shader(VKSPV_TEXT_FRAG, sizeof(VKSPV_TEXT_FRAG))
                     : vk_shader(VKSPV_IMG_FRAG, sizeof(VKSPV_IMG_FRAG));
      }
      if (fs_mod == VK_NULL_HANDLE) {
        break;
      }
      stages[1].module = fs_mod;
      if (vkCreateGraphicsPipelines(g_vk.dev, VK_NULL_HANDLE, 1, &pi, NULL,
                                    out) != VK_SUCCESS) {
        vkDestroyShaderModule(g_vk.dev, fs_mod, NULL);
        break;
      }
      vkDestroyShaderModule(g_vk.dev, fs_mod, NULL);
    }
    if (mods[0] != VK_NULL_HANDLE) {
      vkDestroyShaderModule(g_vk.dev, mods[0], NULL);
    }
    if (mods[1] != VK_NULL_HANDLE) {
      vkDestroyShaderModule(g_vk.dev, mods[1], NULL);
    }
    if (c->pipe_flat == VK_NULL_HANDLE || c->pipe_text == VK_NULL_HANDLE ||
        c->pipe_img == VK_NULL_HANDLE) {
      return MY_RET_FAIL;
    }
  }
  return MY_RET_OK;
}

static uint32_t vk_supported_sample_counts(const my_vgcanvas_vulkan_t* c) {
  VkPhysicalDeviceProperties props;
  VkImageFormatProperties image_props;
  VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  uint32_t counts;

  if (c == NULL) {
    return 0u;
  }
  vkGetPhysicalDeviceProperties(g_vk.pdev, &props);
  counts = (uint32_t)props.limits.framebufferColorSampleCounts;
  memset(&image_props, 0, sizeof(image_props));
  if (vkGetPhysicalDeviceImageFormatProperties(
          g_vk.pdev, c->format, VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_OPTIMAL,
          usage, 0, &image_props) == VK_SUCCESS) {
    counts &= (uint32_t)image_props.sampleCounts;
  } else {
    counts = VK_SAMPLE_COUNT_1_BIT;
  }
  counts |= (uint32_t)c->samples;
  return counts & (uint32_t)(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT |
                             VK_SAMPLE_COUNT_4_BIT);
}

static uint8_t vk_antialias_level_for_samples(VkSampleCountFlagBits samples) {
  switch (samples) {
    case VK_SAMPLE_COUNT_2_BIT:
      return 1u;
    case VK_SAMPLE_COUNT_4_BIT:
      return 2u;
    default:
      return 0u;
  }
}

static void vk_update_capabilities(my_vgcanvas_vulkan_t* c) {
  uint32_t sample_counts = vk_supported_sample_counts(c);
  c->base.capabilities.antialias_levels =
      my_vgcanvas_antialias_levels_for_sample_counts(sample_counts);
  c->base.capabilities.active_antialias_level =
      vk_antialias_level_for_samples(c->samples);
}

static my_ret_t vk_rebuild_resources(my_vgcanvas_vulkan_t* c, int32_t width,
                                     int32_t height,
                                     VkSampleCountFlagBits samples) {
  my_vgcanvas_vulkan_t candidate;

  if (c == NULL || width <= 0 || height <= 0 ||
      (samples != VK_SAMPLE_COUNT_1_BIT &&
       samples != VK_SAMPLE_COUNT_2_BIT &&
       samples != VK_SAMPLE_COUNT_4_BIT)) {
    return MY_RET_INVALID_PARAMS;
  }
  candidate = *c;
  vk_clear_resource_handles(&candidate);
  candidate.fb_w = width;
  candidate.fb_h = height;
  candidate.samples = samples;
  if (vk_create_targets(&candidate) != MY_RET_OK ||
      vk_create_pipelines(&candidate) != MY_RET_OK) {
    vk_destroy_resource_handles(&candidate);
    return MY_RET_FAIL;
  }
  if (candidate.samples != samples) {
    vk_destroy_resource_handles(&candidate);
    return MY_RET_FAIL;
  }
  vkDeviceWaitIdle(g_vk.dev);
  vk_swap_resource_handles(c, &candidate);
  vk_destroy_resource_handles(&candidate);
  c->fb_w = width;
  c->fb_h = height;
  c->state.clip = my_rect_init(0, 0, width, height);
  vk_update_capabilities(c);
  return MY_RET_OK;
}

/* ---------------- frame lifecycle ---------------- */

static void vk_push(my_vgcanvas_vulkan_t* c, my_color_t color) {
  /* std140 push-constant block: u_resolution at 0, u_color at byte 16 */
  float pc[8];
  pc[0] = (float)c->fb_w;
  pc[1] = (float)c->fb_h;
  pc[2] = 0.0f;
  pc[3] = 0.0f;
  pc[4] = (float)color.r / 255.0f;
  pc[5] = (float)color.g / 255.0f;
  pc[6] = (float)color.b / 255.0f;
  pc[7] = (float)color.a / 255.0f;
  vkCmdPushConstants(c->frames[c->frame_idx].cmd, c->pipe_layout,
                     VK_SHADER_STAGE_VERTEX_BIT |
                         VK_SHADER_STAGE_FRAGMENT_BIT,
                     0, VKC_PUSH_SIZE, pc);
}

static void vk_apply_clip(my_vgcanvas_vulkan_t* c) {
  VkRect2D sc;
  /* Vulkan scissor origin is top-left: NO y flip (unlike GL) */
  sc.offset.x = c->state.clip.x;
  sc.offset.y = c->state.clip.y;
  sc.extent.width = (uint32_t)(c->state.clip.w > 0 ? c->state.clip.w : 0);
  sc.extent.height = (uint32_t)(c->state.clip.h > 0 ? c->state.clip.h : 0);
  vkCmdSetScissor(c->frames[c->frame_idx].cmd, 0, 1, &sc);
}

static void vk_begin_renderpass(my_vgcanvas_vulkan_t* c) {
  VkRenderPassBeginInfo rbi;
  VkClearValue clear;
  memset(&clear, 0, sizeof(clear)); /* transparent black */
  memset(&rbi, 0, sizeof(rbi));
  rbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  rbi.renderPass = c->renderpass;
  rbi.framebuffer = c->fbs[c->img_idx];
  rbi.renderArea.offset.x = 0;
  rbi.renderArea.offset.y = 0;
  rbi.renderArea.extent.width = (uint32_t)c->fb_w;
  rbi.renderArea.extent.height = (uint32_t)c->fb_h;
  rbi.clearValueCount = 1;
  rbi.pClearValues = &clear;
  vkCmdBeginRenderPass(c->frames[c->frame_idx].cmd, &rbi,
                       VK_SUBPASS_CONTENTS_INLINE);
  c->in_renderpass = true;
  {
    VkViewport vp;
    vp.x = 0.0f;
    vp.y = 0.0f;
    vp.width = (float)c->fb_w;
    vp.height = (float)c->fb_h;
    vp.minDepth = 0.0f;
    vp.maxDepth = 1.0f;
    vkCmdSetViewport(c->frames[c->frame_idx].cmd, 0, 1, &vp);
  }
  vk_apply_clip(c);
}

static my_ret_t vk_begin_frame(my_vgcanvas_t* vg, const my_rect_t* dirty) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  vk_frame_t* f;
  VkCommandBufferBeginInfo bi;
  int32_t target_w;
  int32_t target_h;
  (void)dirty;
  if (c->need_recreate) {
    target_w = c->pending_fb_w > 0 ? c->pending_fb_w : c->fb_w;
    target_h = c->pending_fb_h > 0 ? c->pending_fb_h : c->fb_h;
    if (vk_rebuild_resources(c, target_w, target_h, c->samples) !=
        MY_RET_OK) {
      return MY_RET_FAIL;
    }
    c->pending_fb_w = 0;
    c->pending_fb_h = 0;
    c->need_recreate = false;
  }
  f = &c->frames[c->frame_idx];
  vkWaitForFences(g_vk.dev, 1, &f->fence, VK_TRUE, UINT64_MAX);
  vk_retire_collect(c, c->frame_idx); /* slot's GPU work is done */
  vkResetFences(g_vk.dev, 1, &f->fence);
  if (!c->offscreen) {
    VkResult acq = vkAcquireNextImageKHR(g_vk.dev, c->swapchain, UINT64_MAX,
                                         f->sem_acquire, VK_NULL_HANDLE,
                                         &c->img_idx);
    if (acq == VK_ERROR_OUT_OF_DATE_KHR) {
      if (vk_rebuild_resources(c, c->fb_w, c->fb_h, c->samples) !=
          MY_RET_OK) {
        return MY_RET_FAIL;
      }
      acq = vkAcquireNextImageKHR(g_vk.dev, c->swapchain, UINT64_MAX,
                                  f->sem_acquire, VK_NULL_HANDLE,
                                  &c->img_idx);
    }
    if (acq != VK_SUCCESS && acq != VK_SUBOPTIMAL_KHR) {
      return MY_RET_FAIL;
    }
  } else {
    c->img_idx = 0;
  }
  vkResetCommandBuffer(f->cmd, 0);
  f->vbuf_used = 0;
  memset(&bi, 0, sizeof(bi));
  bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  if (vkBeginCommandBuffer(f->cmd, &bi) != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  c->cmd_pending = true;
  vk_begin_renderpass(c);
  return MY_RET_OK;
}

/** @brief Submit the recorded command buffer (and wait on the fence). */
static my_ret_t vk_flush(my_vgcanvas_vulkan_t* c) {
  vk_frame_t* f = &c->frames[c->frame_idx];
  VkSubmitInfo si;
  VkPipelineStageFlags wait_stage =
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  if (!c->cmd_pending) {
    return MY_RET_OK;
  }
  if (c->in_renderpass) {
    vkCmdEndRenderPass(f->cmd);
    c->in_renderpass = false;
  }
  if (c->samples != VK_SAMPLE_COUNT_1_BIT &&
      (!c->offscreen || getenv("MYUI_VK_RPRESOLVE") != NULL)) {
    /* windowed MSAA: zero-draw resolve renderpass — the subpass end
     * resolves the persistent MSAA image into the swapchain image
     * (full renderArea; the MSAA image's loadOp=LOAD history keeps
     * partial repaints correct). No TRANSFER usage on the swapchain
     * (M25c, WSI dmabuf constraint). */
    VkRenderPassBeginInfo rbi;
    memset(&rbi, 0, sizeof(rbi));
    rbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rbi.renderPass = c->resolve_rp;
    rbi.framebuffer = c->resolve_fbs[c->img_idx];
    rbi.renderArea.extent.width = (uint32_t)c->fb_w;
    rbi.renderArea.extent.height = (uint32_t)c->fb_h;
    vkCmdBeginRenderPass(f->cmd, &rbi, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdEndRenderPass(f->cmd);
  } else if (c->samples != VK_SAMPLE_COUNT_1_BIT) {
    /* offscreen: manual full-extent resolve (the private target image
     * carries TRANSFER usages; both images are persistent, so resolving
     * the whole image preserves the regions this frame did not touch) */
    VkImageLayout home = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    VkImageResolve region;
    vk_transition(f->cmd, c->msaa_img,
                  VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                  VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                  VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                  VK_ACCESS_TRANSFER_READ_BIT,
                  VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                  VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
    vk_transition(f->cmd, c->target_imgs[c->img_idx], home,
                  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                  VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                  VK_ACCESS_TRANSFER_WRITE_BIT,
                  VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                  VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
    memset(&region, 0, sizeof(region));
    region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.srcSubresource.layerCount = 1;
    region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.dstSubresource.layerCount = 1;
    region.extent.width = (uint32_t)c->fb_w;
    region.extent.height = (uint32_t)c->fb_h;
    region.extent.depth = 1;
    vkCmdResolveImage(f->cmd, c->msaa_img,
                      VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                      c->target_imgs[c->img_idx],
                      VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
    vk_transition(f->cmd, c->msaa_img,
                  VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                  VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                  VK_ACCESS_TRANSFER_READ_BIT,
                  VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                  VK_PIPELINE_STAGE_TRANSFER_BIT,
                  VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0);
    vk_transition(f->cmd, c->target_imgs[c->img_idx],
                  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, home,
                  VK_ACCESS_TRANSFER_WRITE_BIT,
                  VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                      VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                  VK_PIPELINE_STAGE_TRANSFER_BIT,
                  VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0);
  }
  vkEndCommandBuffer(f->cmd);
  memset(&si, 0, sizeof(si));
  si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  if (!c->offscreen) {
    si.waitSemaphoreCount = 1;
    si.pWaitSemaphores = &f->sem_acquire;
    si.pWaitDstStageMask = &wait_stage;
    si.signalSemaphoreCount = 1;
    si.pSignalSemaphores = &f->sem_present;
  }
  si.commandBufferCount = 1;
  si.pCommandBuffers = &f->cmd;
  if (vkQueueSubmit(g_vk.queue, 1, &si, f->fence) != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  c->cmd_pending = false;
  return MY_RET_OK;
}

static my_ret_t vk_end_frame(my_vgcanvas_t* vg) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (c->offscreen) {
    /* offscreen has no present step: submit right away */
    my_ret_t r = vk_flush(c);
    if (r == MY_RET_OK) {
      vk_frame_t* f = &c->frames[c->frame_idx];
      vkWaitForFences(g_vk.dev, 1, &f->fence, VK_TRUE, UINT64_MAX);
    }
    return r;
  }
  /* windowed: submission happens in my_vgcanvas_vulkan_present() (the
   * adapter's swap_buffers), matching the GL present protocol */
  if (c->in_renderpass) {
    vkCmdEndRenderPass(c->frames[c->frame_idx].cmd);
    c->in_renderpass = false;
  }
  return MY_RET_OK;
}

/** @brief Debug helper (MYUI_VK_DUMP): resolve the persistent MSAA image
 * into a private single-sample image and dump it as PPM. */
static void vk_debug_dump(my_vgcanvas_vulkan_t* c, const char* path) {
  VkImageCreateInfo ici;
  VkMemoryRequirements req;
  VkMemoryAllocateInfo mai;
  VkImage dbg = VK_NULL_HANDLE;
  VkDeviceMemory dbg_mem = VK_NULL_HANDLE;
  VkBuffer buf = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;
  VkCommandBuffer cmd;
  VkDeviceSize sz = (VkDeviceSize)c->fb_w * (VkDeviceSize)c->fb_h * 4;
  void* map = NULL;
  FILE* fp;
  int x, y;
  const uint8_t* px;
  if (c->msaa_img == VK_NULL_HANDLE) {
    return;
  }
  vkDeviceWaitIdle(g_vk.dev);
  memset(&ici, 0, sizeof(ici));
  ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  ici.imageType = VK_IMAGE_TYPE_2D;
  ici.format = c->format;
  ici.extent.width = (uint32_t)c->fb_w;
  ici.extent.height = (uint32_t)c->fb_h;
  ici.extent.depth = 1;
  ici.mipLevels = 1;
  ici.arrayLayers = 1;
  ici.samples = VK_SAMPLE_COUNT_1_BIT;
  ici.tiling = VK_IMAGE_TILING_OPTIMAL;
  ici.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
  ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  if (vkCreateImage(g_vk.dev, &ici, NULL, &dbg) != VK_SUCCESS) {
    return;
  }
  vkGetImageMemoryRequirements(g_vk.dev, dbg, &req);
  memset(&mai, 0, sizeof(mai));
  mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  mai.allocationSize = req.size;
  mai.memoryTypeIndex = vk_mem_type(req.memoryTypeBits,
                                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  if (vkAllocateMemory(g_vk.dev, &mai, NULL, &dbg_mem) != VK_SUCCESS ||
      vkBindImageMemory(g_vk.dev, dbg, dbg_mem, 0) != VK_SUCCESS ||
      vk_make_buffer(sz, VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     &buf, &mem) != MY_RET_OK ||
      vk_oneshot(&cmd) != MY_RET_OK) {
    goto done;
  }
  vk_transition(cmd, dbg, VK_IMAGE_LAYOUT_UNDEFINED,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 0,
                VK_ACCESS_TRANSFER_WRITE_BIT,
                VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
  vk_transition(cmd, c->msaa_img, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                VK_ACCESS_TRANSFER_READ_BIT,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
  {
    VkImageResolve rs;
    memset(&rs, 0, sizeof(rs));
    rs.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    rs.srcSubresource.layerCount = 1;
    rs.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    rs.dstSubresource.layerCount = 1;
    rs.extent.width = (uint32_t)c->fb_w;
    rs.extent.height = (uint32_t)c->fb_h;
    rs.extent.depth = 1;
    vkCmdResolveImage(cmd, c->msaa_img, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                      dbg, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &rs);
  }
  vk_transition(cmd, c->msaa_img, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_ACCESS_TRANSFER_READ_BIT,
                VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                    VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0);
  vk_transition(cmd, dbg, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_TRANSFER_READ_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
  {
    VkBufferImageCopy cp;
    memset(&cp, 0, sizeof(cp));
    cp.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    cp.imageSubresource.layerCount = 1;
    cp.imageExtent.width = (uint32_t)c->fb_w;
    cp.imageExtent.height = (uint32_t)c->fb_h;
    cp.imageExtent.depth = 1;
    vkCmdCopyImageToBuffer(cmd, dbg, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                           buf, 1, &cp);
  }
  if (vk_oneshot_submit(cmd) != MY_RET_OK ||
      vkMapMemory(g_vk.dev, mem, 0, sz, 0, &map) != VK_SUCCESS) {
    goto done;
  }
  fp = fopen(path, "wb");
  if (fp != NULL) {
    fprintf(fp, "P6\n%d %d\n255\n", (int)c->fb_w, (int)c->fb_h);
    px = (const uint8_t*)map;
    for (y = 0; y < c->fb_h; y++) {
      for (x = 0; x < c->fb_w; x++) {
        const uint8_t* p = px + ((size_t)y * (size_t)c->fb_w + (size_t)x) * 4;
        fputc(p[2], fp); /* BGRA -> RGB */
        fputc(p[1], fp);
        fputc(p[0], fp);
      }
    }
    fclose(fp);
    fprintf(stderr, "[vkdbg] dumped %s\n", path);
  }
  vkUnmapMemory(g_vk.dev, mem);
done:
  if (buf != VK_NULL_HANDLE) {
    vkDestroyBuffer(g_vk.dev, buf, NULL);
  }
  if (mem != VK_NULL_HANDLE) {
    vkFreeMemory(g_vk.dev, mem, NULL);
  }
  if (dbg != VK_NULL_HANDLE) {
    vkDestroyImage(g_vk.dev, dbg, NULL);
  }
  if (dbg_mem != VK_NULL_HANDLE) {
    vkFreeMemory(g_vk.dev, dbg_mem, NULL);
  }
}

my_ret_t my_vgcanvas_vulkan_present(my_vgcanvas_t* vg) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  vk_frame_t* f;
  VkPresentInfoKHR pri;
  VkResult pr;
  if (c == NULL || c->offscreen) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!c->cmd_pending) {
    /* nothing was recorded this frame (e.g. begin_frame failed):
     * presenting now would wait on a semaphore that no submit signaled
     * and desync the swapchain — skip (M25 crash fix) */
    return MY_RET_OK;
  }
  if (vk_flush(c) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  f = &c->frames[c->frame_idx];
  memset(&pri, 0, sizeof(pri));
  pri.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  pri.waitSemaphoreCount = 1;
  pri.pWaitSemaphores = &f->sem_present;
  pri.swapchainCount = 1;
  pri.pSwapchains = &c->swapchain;
  pri.pImageIndices = &c->img_idx;
  pr = vkQueuePresentKHR(g_vk.queue, &pri);
  if (pr == VK_ERROR_OUT_OF_DATE_KHR || pr == VK_SUBOPTIMAL_KHR) {
    c->need_recreate = true;
  } else if (pr != VK_SUCCESS) {
    return MY_RET_FAIL;
  }
  c->frame_idx = (c->frame_idx + 1) % VKC_FRAMES;
  /* debug: MYUI_VK_DUMP=<path> dumps the resolved frame content once
   * (resolves the persistent MSAA image into a private 1-sample image,
   * which unlike swapchain images may carry TRANSFER usage) */
  if (c->dbg_dump_path != NULL) {
    c->dbg_frames++;
    if (c->dbg_frames == c->dbg_dump_frame) {
      vk_debug_dump(c, c->dbg_dump_path);
    }
  }
  return MY_RET_OK;
}

my_ret_t my_vgcanvas_vulkan_resize(my_vgcanvas_t* vg, int32_t width,
                                   int32_t height) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (c == NULL || width <= 0 || height <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (c->fb_w != width || c->fb_h != height) {
    c->pending_fb_w = width;
    c->pending_fb_h = height;
    c->need_recreate = true;
  }
  return MY_RET_OK;
}

/* ---------------- state vtable ---------------- */

static my_ret_t vk_save(my_vgcanvas_t* vg) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  vk_state_t* grown;
  size_t new_cap = c->stack_cap > 0 ? c->stack_cap : 8;
  if (c->stack_count + 1 > c->stack_cap) {
    while (new_cap < c->stack_count + 1) {
      new_cap *= 2;
    }
    grown = (vk_state_t*)my_mem_realloc(c->allocator, c->stack,
                                        new_cap * sizeof(vk_state_t));
    if (grown == NULL) {
      return MY_RET_OOM;
    }
    c->stack = grown;
    c->stack_cap = new_cap;
  }
  c->stack[c->stack_count++] = c->state;
  return MY_RET_OK;
}

static my_ret_t vk_restore(my_vgcanvas_t* vg) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (c->stack_count == 0) {
    return MY_RET_FAIL;
  }
  c->state = c->stack[--c->stack_count];
  if (c->in_renderpass) {
    vk_apply_clip(c);
  }
  return MY_RET_OK;
}

static my_ret_t vk_translate(my_vgcanvas_t* vg, float dx, float dy) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  c->state.tx += dx;
  c->state.ty += dy;
  return MY_RET_OK;
}

/** @brief reset_clip slot (M25): same device-space math as clip_rect but
 * REPLACES the clip instead of intersecting (overlay escape hatch). */
static my_ret_t vk_reset_clip(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  c->state.clip = my_rect_init(
      (int32_t)floorf((rect->x + c->state.tx) * c->state.scale),
      (int32_t)floorf((rect->y + c->state.ty) * c->state.scale),
      (int32_t)ceilf((rect->x + c->state.tx + rect->w) * c->state.scale) -
          (int32_t)floorf((rect->x + c->state.tx) * c->state.scale),
      (int32_t)ceilf((rect->y + c->state.ty + rect->h) * c->state.scale) -
          (int32_t)floorf((rect->y + c->state.ty) * c->state.scale));
  if (c->in_renderpass) {
    vk_apply_clip(c);
  }
  return MY_RET_OK;
}

static my_ret_t vk_clip_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  my_rect_t dev, clipped;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  dev = my_rect_init(
      (int32_t)floorf((rect->x + c->state.tx) * c->state.scale),
      (int32_t)floorf((rect->y + c->state.ty) * c->state.scale),
      (int32_t)ceilf((rect->x + c->state.tx + rect->w) * c->state.scale) -
          (int32_t)floorf((rect->x + c->state.tx) * c->state.scale),
      (int32_t)ceilf((rect->y + c->state.ty + rect->h) * c->state.scale) -
          (int32_t)floorf((rect->y + c->state.ty) * c->state.scale));
  if (my_rect_intersect(&c->state.clip, &dev, &clipped)) {
    c->state.clip = clipped;
  } else {
    c->state.clip = my_rect_init(0, 0, 0, 0);
  }
  if (c->in_renderpass) {
    vk_apply_clip(c);
  }
  return MY_RET_OK;
}

static my_ret_t vk_set_fill_color(my_vgcanvas_t* vg, my_color_t color) {
  ((my_vgcanvas_vulkan_t*)vg)->state.fill_color = color;
  return MY_RET_OK;
}

static my_ret_t vk_set_stroke_color(my_vgcanvas_t* vg, my_color_t color) {
  ((my_vgcanvas_vulkan_t*)vg)->state.stroke_color = color;
  return MY_RET_OK;
}

static my_ret_t vk_set_line_width(my_vgcanvas_t* vg, float width) {
  ((my_vgcanvas_vulkan_t*)vg)->state.line_width = width;
  return MY_RET_OK;
}

static my_ret_t vk_set_line_cap(my_vgcanvas_t* vg, my_line_cap_t cap) {
  ((my_vgcanvas_vulkan_t*)vg)->state.line_cap = cap;
  return MY_RET_OK;
}

static my_ret_t vk_set_line_join(my_vgcanvas_t* vg, my_line_join_t join) {
  ((my_vgcanvas_vulkan_t*)vg)->state.line_join = join;
  return MY_RET_OK;
}

static my_ret_t vk_set_scale_vtable(my_vgcanvas_t* vg, float scale) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (c == NULL || scale <= 0.0f) {
    return MY_RET_INVALID_PARAMS;
  }
  c->state.scale = scale;
  return MY_RET_OK;
}

static my_ret_t vk_set_antialias_level_vtable(my_vgcanvas_t* vg, int level) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  uint32_t sample_count;
  int32_t target_w;
  int32_t target_h;
  my_ret_t ret;
  if (c == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  sample_count = my_vgcanvas_antialias_level_sample_count(level);
  if (sample_count == 0u) {
    return MY_RET_INVALID_PARAMS;
  }
  if (c->cmd_pending || c->in_renderpass) {
    return MY_RET_FAIL;
  }
  target_w = c->pending_fb_w > 0 ? c->pending_fb_w : c->fb_w;
  target_h = c->pending_fb_h > 0 ? c->pending_fb_h : c->fb_h;
  ret = vk_rebuild_resources(c, target_w, target_h,
                             (VkSampleCountFlagBits)sample_count);
  if (ret == MY_RET_OK) {
    c->pending_fb_w = 0;
    c->pending_fb_h = 0;
    c->need_recreate = false;
  }
  return ret;
}

static my_ret_t vk_set_scale_filter_vtable(my_vgcanvas_t* vg,
                                           my_scale_filter_t filter) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (c == NULL || (filter != MY_SCALE_FILTER_NEAREST &&
                    filter != MY_SCALE_FILTER_BILINEAR)) {
    return MY_RET_INVALID_PARAMS;
  }
  c->state.scale_filter = filter;
  return MY_RET_OK;
}

/* ---------------- draws ---------------- */

/** @brief Upload vertex bytes into this frame's vbuf slot and bind. */
static my_ret_t vk_bind_verts(my_vgcanvas_vulkan_t* c, const float* data,
                              size_t byte_len, VkDeviceSize* out_off) {
  vk_frame_t* f = &c->frames[c->frame_idx];
  VkBuffer bufs[1];
  if (byte_len == 0) {
    return MY_RET_FAIL;
  }
  if (f->vbuf_used + byte_len > VKC_VBUF_PER_FRAME) {
    MY_LOGE("vulkan: frame vertex buffer overflow (%u bytes), draw dropped",
            (unsigned)byte_len);
    return MY_RET_FAIL;
  }
  memcpy((char*)c->vbuf_map + f->vbuf_off + f->vbuf_used, data, byte_len);
  *out_off = f->vbuf_off + f->vbuf_used;
  f->vbuf_used += byte_len;
  bufs[0] = c->vbuf;
  vkCmdBindVertexBuffers(f->cmd, 0, 1, bufs, out_off);
  return MY_RET_OK;
}

static void vk_draw_flat(my_vgcanvas_vulkan_t* c, my_color_t color) {
  vk_frame_t* f = &c->frames[c->frame_idx];
  VkDeviceSize off;
  if (c->geo.vert_count == 0) {
    return;
  }
  if (vk_bind_verts(c, c->geo.verts, c->geo.vert_count * sizeof(float),
                    &off) != MY_RET_OK) {
    return;
  }
  vkCmdBindPipeline(f->cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, c->pipe_flat);
  vk_push(c, color);
  vkCmdDraw(f->cmd, (uint32_t)(c->geo.vert_count / 2), 1, 0, 0);
}

static void vk_draw_textured(my_vgcanvas_vulkan_t* c, VkPipeline pipe,
                             vk_tex_t* tex, const float* xyuv, int32_t count,
                             my_color_t color) {
  vk_frame_t* f = &c->frames[c->frame_idx];
  VkDeviceSize off;
  if (vk_bind_verts(c, xyuv, (size_t)count * 4 * sizeof(float), &off) !=
      MY_RET_OK) {
    return;
  }
  vkCmdBindPipeline(f->cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipe);
  vkCmdBindDescriptorSets(f->cmd, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          c->pipe_layout, 0, 1, &tex->ds, 0, NULL);
  vk_push(c, color);
  vkCmdDraw(f->cmd, (uint32_t)count, 1, 0, 0);
}

static void vk_geo_setup(my_vgcanvas_vulkan_t* c) {
  my_vggeometry_set_transform(&c->geo, c->state.tx, c->state.ty,
                              c->state.scale);
  my_vggeometry_begin_verts(&c->geo);
}

static my_ret_t vk_fill_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  vk_geo_setup(c);
  my_vggeometry_rect(&c->geo, rect->x, rect->y, rect->x + rect->w,
                     rect->y + rect->h);
  vk_draw_flat(c, c->state.fill_color);
  return MY_RET_OK;
}

static my_ret_t vk_stroke_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  vk_geo_setup(c);
  my_vggeometry_stroke_rect(&c->geo, rect->x, rect->y, rect->w, rect->h,
                            c->state.line_width);
  vk_draw_flat(c, c->state.stroke_color);
  return MY_RET_OK;
}

static my_ret_t vk_fill_rounded_rect(my_vgcanvas_t* vg,
                                     const my_rectf_t* rect, float radius) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  vk_geo_setup(c);
  my_vggeometry_fill_rounded_rect(&c->geo, rect->x, rect->y, rect->w,
                                  rect->h, radius);
  vk_draw_flat(c, c->state.fill_color);
  return MY_RET_OK;
}

/* ---------------- path ---------------- */

static my_ret_t vk_begin_path(my_vgcanvas_t* vg) {
  return my_vggeometry_begin_path(&((my_vgcanvas_vulkan_t*)vg)->geo);
}

static my_ret_t vk_move_to(my_vgcanvas_t* vg, float x, float y) {
  return my_vggeometry_move_to(&((my_vgcanvas_vulkan_t*)vg)->geo, x, y);
}

static my_ret_t vk_line_to(my_vgcanvas_t* vg, float x, float y) {
  return my_vggeometry_line_to(&((my_vgcanvas_vulkan_t*)vg)->geo, x, y);
}

static my_ret_t vk_close_path(my_vgcanvas_t* vg) {
  return my_vggeometry_close_path(&((my_vgcanvas_vulkan_t*)vg)->geo);
}

static my_ret_t vk_curve_to(my_vgcanvas_t* vg, float cx1, float cy1,
                            float cx2, float cy2, float x, float y) {
  return my_vggeometry_curve_to(&((my_vgcanvas_vulkan_t*)vg)->geo, cx1, cy1,
                                cx2, cy2, x, y);
}

static my_ret_t vk_fill(my_vgcanvas_t* vg) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  vk_geo_setup(c);
  if (my_vggeometry_fill(&c->geo, &c->state.clip) == MY_RET_OOM) {
    return MY_RET_OOM;
  }
  vk_draw_flat(c, c->state.fill_color);
  return MY_RET_OK;
}

static my_ret_t vk_stroke(my_vgcanvas_t* vg) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  vk_geo_setup(c);
  my_vggeometry_stroke(&c->geo, c->state.line_width, c->state.line_cap,
                       c->state.line_join);
  vk_draw_flat(c, c->state.stroke_color);
  return MY_RET_OK;
}

/* ---------------- text ---------------- */

static int32_t vk_dev_font_size(const my_vgcanvas_vulkan_t* c) {
  int32_t d = (int32_t)((float)c->state.font_size * c->state.scale + 0.5f);
  return d > 0 ? d : 1;
}

/** @brief Draw one codepoint at pen_x and advance it. */
static void vk_draw_cp(my_vgcanvas_vulkan_t* c, uint32_t cp, float* pen_x,
                       float top, int32_t ascent) {
  my_glyph_t g = {0};
  uint32_t slot;
  float gx, gy;
  if (my_font_get_glyph(c->state.font, cp, vk_dev_font_size(c), &g) !=
          MY_RET_OK ||
      g.bitmap == NULL || g.w <= 0 || g.h <= 0) {
    *pen_x += g.advance > 0 ? (float)g.advance : 0.0f;
    return;
  }
  /* direct-mapped texture cache: evict on slot collision (same as gles2) */
  slot = (cp ^ (uint32_t)vk_dev_font_size(c)) % VKC_GLYPH_CACHE;
  if (c->glyph_cache[slot].tex.img == VK_NULL_HANDLE ||
      c->glyph_cache[slot].font != c->state.font ||
      c->glyph_cache[slot].key_is_glyph_id ||
      c->glyph_cache[slot].codepoint != cp ||
      c->glyph_cache[slot].size != vk_dev_font_size(c)) {
    if (!vk_tex_retire(c, &c->glyph_cache[slot].tex)) {
      *pen_x += (float)g.advance;
      return;
    }
    if (vk_tex_create(c, &c->glyph_cache[slot].tex, g.bitmap, g.w, g.h,
                      VK_FORMAT_R8_UNORM, c->sampler) != MY_RET_OK) {
      *pen_x += (float)g.advance;
      return;
    }
    c->glyph_cache[slot].font = c->state.font;
    c->glyph_cache[slot].codepoint = cp;
    c->glyph_cache[slot].key_is_glyph_id = false;
    c->glyph_cache[slot].size = vk_dev_font_size(c);
  }
  gx = *pen_x + (float)g.bearing_x;
  gy = top + (float)(ascent - g.bearing_y);
  {
    float x0 = gx, y0 = gy, x1 = gx + (float)g.w, y1 = gy + (float)g.h;
    const float quad[6][4] = {{x0, y0, 0, 0}, {x1, y0, 1, 0}, {x1, y1, 1, 1},
                              {x0, y0, 0, 0}, {x1, y1, 1, 1}, {x0, y1, 0, 1}};
    vk_draw_textured(c, c->pipe_text, &c->glyph_cache[slot].tex, &quad[0][0],
                     6, c->state.fill_color);
  }
  *pen_x += (float)g.advance;
}

static void vk_draw_shaped_glyph(my_vgcanvas_vulkan_t* c,
                                 const my_font_shape_glyph_t* shaped,
                                 float* pen_x, float top, int32_t ascent) {
  my_glyph_t g = {0};
  my_font_t* font = shaped->font != NULL ? shaped->font : c->state.font;
  uint32_t slot;
  float gx, gy;
  float advance = (float)shaped->advance_x_26_6 / 64.0f;
  if (my_font_get_glyph_id(
          font, shaped->glyph_id, vk_dev_font_size(c), &g) != MY_RET_OK ||
      g.bitmap == NULL || g.w <= 0 || g.h <= 0) {
    *pen_x += advance;
    return;
  }
  slot = (shaped->glyph_id ^ (uint32_t)vk_dev_font_size(c)) % VKC_GLYPH_CACHE;
  if (c->glyph_cache[slot].tex.img == VK_NULL_HANDLE ||
      c->glyph_cache[slot].font != font ||
      !c->glyph_cache[slot].key_is_glyph_id ||
      c->glyph_cache[slot].codepoint != shaped->glyph_id ||
      c->glyph_cache[slot].size != vk_dev_font_size(c)) {
    if (!vk_tex_retire(c, &c->glyph_cache[slot].tex)) {
      *pen_x += advance;
      return;
    }
    if (vk_tex_create(c, &c->glyph_cache[slot].tex, g.bitmap, g.w, g.h,
                      VK_FORMAT_R8_UNORM, c->sampler) != MY_RET_OK) {
      *pen_x += advance;
      return;
    }
    c->glyph_cache[slot].font = font;
    c->glyph_cache[slot].codepoint = shaped->glyph_id;
    c->glyph_cache[slot].key_is_glyph_id = true;
    c->glyph_cache[slot].size = vk_dev_font_size(c);
  }
  gx = *pen_x + (float)shaped->offset_x_26_6 / 64.0f + (float)g.bearing_x;
  gy = top + (float)(ascent - g.bearing_y) -
       (float)shaped->offset_y_26_6 / 64.0f;
  {
    float x0 = gx, y0 = gy, x1 = gx + (float)g.w, y1 = gy + (float)g.h;
    const float quad[6][4] = {{x0, y0, 0, 0}, {x1, y0, 1, 0}, {x1, y1, 1, 1},
                              {x0, y0, 0, 0}, {x1, y1, 1, 1}, {x0, y1, 0, 1}};
    vk_draw_textured(c, c->pipe_text, &c->glyph_cache[slot].tex,
                     &quad[0][0], 6, c->state.fill_color);
  }
  *pen_x += advance;
}

static my_ret_t vk_draw_text(my_vgcanvas_t* vg, const char* text, float x,
                             float y) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  int32_t ascent;
  float pen_x, top;
  const char* p = text;
  if (text == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (c->state.font == NULL || c->state.font_size <= 0) {
    return MY_RET_NOT_SUPPORTED;
  }
  ascent = my_font_ascent(c->state.font, vk_dev_font_size(c));
  pen_x = (x + c->state.tx) * c->state.scale;
  top = (y + c->state.ty) * c->state.scale;
  if (!my_text_layout_may_need_bidi(text)) {
    my_font_shape_result_t shaped = {0};
    if (my_vgcanvas_shape_font(vg, c->state.font, text,
                               vk_dev_font_size(c), false, c->allocator,
                               &shaped) == MY_RET_OK) {
      size_t i;
      for (i = 0; i < shaped.count; i++) {
        vk_draw_shaped_glyph(c, &shaped.glyphs[i], &pen_x, top, ascent);
      }
      my_font_shape_destroy(&shaped);
    } else {
      while (*p != '\0') {
        vk_draw_cp(c, my_utf8_next(&p), &pen_x, top, ascent);
      }
    }
  } else {
    my_text_layout_t* l = my_text_layout_process(c->allocator, text);
    my_font_shape_result_t shaped = {0};
    my_ret_t shape_ret;
    size_t i;
    if (l == NULL) {
      return MY_RET_OOM;
    }
    shape_ret = my_vgcanvas_shape_layout(
        vg, l, text, c->state.font, vk_dev_font_size(c), c->allocator,
        &shaped);
    if (shape_ret == MY_RET_OK) {
      for (i = 0; i < shaped.count; i++) {
        vk_draw_shaped_glyph(c, &shaped.glyphs[i], &pen_x, top, ascent);
      }
      my_font_shape_destroy(&shaped);
    } else if (shape_ret == MY_RET_NOT_SUPPORTED) {
      for (i = 0; i < l->len; i++) {
        vk_draw_cp(c, l->visual_cps[i], &pen_x, top, ascent);
      }
    } else {
      my_text_layout_destroy(l);
      return shape_ret;
    }
    my_text_layout_destroy(l);
  }
  return MY_RET_OK;
}

static my_ret_t vk_set_font(my_vgcanvas_t* vg, my_font_t* font, int32_t size) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  if (font != NULL) {
    c->state.font = font;
  }
  if (size > 0) {
    c->state.font_size = size;
  }
  return MY_RET_OK;
}

static my_ret_t vk_measure_text(my_vgcanvas_t* vg, const char* text,
                                int32_t* w, int32_t* h) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  my_ret_t ret;
  if (c->state.font == NULL || c->state.font_size <= 0) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (text != NULL && my_text_layout_may_need_bidi(text)) {
    my_text_layout_t* l = my_text_layout_process(c->allocator, text);
    if (l == NULL) {
      return MY_RET_OOM;
    }
    {
      my_font_shape_result_t shaped = {0};
      ret = my_vgcanvas_shape_layout(
          vg, l, text, c->state.font, vk_dev_font_size(c), c->allocator,
          &shaped);
      if (ret == MY_RET_OK) {
        int64_t width = 0;
        size_t i;
        for (i = 0; i < shaped.count; i++) {
          width += shaped.glyphs[i].advance_x_26_6;
        }
        if (w != NULL) *w = (int32_t)((width + 32) / 64);
        if (h != NULL) {
          *h = my_font_line_height(c->state.font, vk_dev_font_size(c));
        }
        my_font_shape_destroy(&shaped);
      } else if (ret == MY_RET_NOT_SUPPORTED) {
        ret = my_font_measure(c->state.font, l->visual_utf8,
                              vk_dev_font_size(c), w, h);
      }
    }
    my_text_layout_destroy(l);
  } else {
    my_font_shape_result_t shaped = {0};
    ret = my_vgcanvas_shape_font(vg, c->state.font, text,
                                 vk_dev_font_size(c), false, c->allocator,
                                 &shaped);
    if (ret == MY_RET_OK) {
      int64_t width = 0;
      size_t i;
      for (i = 0; i < shaped.count; i++) width += shaped.glyphs[i].advance_x_26_6;
      if (w != NULL) *w = (int32_t)((width + 32) / 64);
      if (h != NULL) *h = my_font_line_height(c->state.font,
                                               vk_dev_font_size(c));
      my_font_shape_destroy(&shaped);
    } else {
      ret = my_font_measure(c->state.font, text, vk_dev_font_size(c), w, h);
    }
  }
  if (ret == MY_RET_OK && c->state.scale != 1.0f) {
    if (w != NULL) {
      *w = (int32_t)((float)*w / c->state.scale + 0.5f);
    }
    if (h != NULL) {
      *h = (int32_t)((float)*h / c->state.scale + 0.5f);
    }
  }
  return ret;
}

/* ---------------- image ---------------- */

/** @brief LRU texture for a caller bitmap (same policy as gles2, M25b). */
static vk_tex_t* vk_image_texture(my_vgcanvas_vulkan_t* c, const uint8_t* rgba,
                                  int32_t w, int32_t h,
                                  my_scale_filter_t filter) {
  size_t i;
  vk_img_entry_t* lru = &c->img_cache[0];
  for (i = 0; i < VKC_IMG_CACHE; i++) {
    vk_img_entry_t* e = &c->img_cache[i];
    if (e->tex.img == VK_NULL_HANDLE) {
      lru = e;
      continue;
    }
    if (e->last_used < lru->last_used) {
      lru = e;
    }
    if (e->ptr == rgba && e->w == w && e->h == h && e->filter == filter) {
      e->last_used = ++c->img_tick;
      return &e->tex;
    }
  }
  if (!vk_tex_retire(c, &lru->tex)) {
    return NULL;
  }
  if (vk_tex_create(c, &lru->tex, rgba, w, h, VK_FORMAT_R8G8B8A8_UNORM,
                    filter == MY_SCALE_FILTER_BILINEAR ? c->sampler
                                                        : c->nearest_sampler) !=
      MY_RET_OK) {
    return NULL;
  }
  lru->ptr = rgba;
  lru->w = w;
  lru->h = h;
  lru->filter = filter;
  lru->last_used = ++c->img_tick;
  return &lru->tex;
}

static my_ret_t vk_draw_image(my_vgcanvas_t* vg, const uint8_t* rgba,
                              int32_t w, int32_t h, const my_rectf_t* dst,
                              const my_color_t* bg) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  vk_tex_t* tex;
  if (rgba == NULL || dst == NULL || w <= 0 || h <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  /* bg compositing: paint bg rect first, then blend the textured quad */
  if (bg != NULL && bg->a > 0) {
    vk_geo_setup(c);
    my_vggeometry_rect(&c->geo, dst->x, dst->y, dst->x + dst->w,
                       dst->y + dst->h);
    vk_draw_flat(c, *bg);
  }
  tex = vk_image_texture(c, rgba, w, h, c->state.scale_filter);
  if (tex == NULL) {
    return MY_RET_OOM;
  }
  {
    float x0 = (dst->x + c->state.tx) * c->state.scale;
    float y0 = (dst->y + c->state.ty) * c->state.scale;
    float x1 = x0 + dst->w * c->state.scale;
    float y1 = y0 + dst->h * c->state.scale;
    const float quad[6][4] = {{x0, y0, 0, 0}, {x1, y0, 1, 0}, {x1, y1, 1, 1},
                              {x0, y0, 0, 0}, {x1, y1, 1, 1}, {x0, y1, 0, 1}};
    my_color_t white = {255, 255, 255, 255};
    vk_draw_textured(c, c->pipe_img, tex, &quad[0][0], 6, white);
  }
  return MY_RET_OK;
}

/* ---------------- lifecycle ---------------- */

static void vk_destroy(my_vgcanvas_t* vg) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  size_t i;
  if (c == NULL) {
    return;
  }
  vkDeviceWaitIdle(g_vk.dev);
  vk_retire_collect(c, 0);
  vk_retire_collect(c, 1);
  my_mem_free(c->allocator, c->retired[0]);
  my_mem_free(c->allocator, c->retired[1]);
  for (i = 0; i < VKC_GLYPH_CACHE; i++) {
    vk_tex_destroy_now(c, &c->glyph_cache[i].tex);
  }
  for (i = 0; i < VKC_IMG_CACHE; i++) {
    vk_tex_destroy_now(c, &c->img_cache[i].tex);
  }
  vk_destroy_resource_handles(c);
  if (c->surface != VK_NULL_HANDLE) {
    vkDestroySurfaceKHR(g_vk.inst, c->surface, NULL);
  }
  for (i = 0; i < VKC_FRAMES; i++) {
    if (c->frames[i].sem_acquire != VK_NULL_HANDLE) {
      vkDestroySemaphore(g_vk.dev, c->frames[i].sem_acquire, NULL);
    }
    if (c->frames[i].sem_present != VK_NULL_HANDLE) {
      vkDestroySemaphore(g_vk.dev, c->frames[i].sem_present, NULL);
    }
    if (c->frames[i].fence != VK_NULL_HANDLE) {
      vkDestroyFence(g_vk.dev, c->frames[i].fence, NULL);
    }
  }
  if (c->cmd_pool != VK_NULL_HANDLE) {
    vkDestroyCommandPool(g_vk.dev, c->cmd_pool, NULL);
  }
  if (c->vbuf != VK_NULL_HANDLE) {
    vkUnmapMemory(g_vk.dev, c->vbuf_mem);
    vkDestroyBuffer(g_vk.dev, c->vbuf, NULL);
    vkFreeMemory(g_vk.dev, c->vbuf_mem, NULL);
  }
  my_vggeometry_destroy(&c->geo);
  my_mem_free(c->allocator, c->stack);
  vk_global_release();
  my_mem_free(c->allocator, c);
}

static const my_vgcanvas_vtable_t s_vk_vtable = {
    vk_begin_frame,      vk_end_frame,   vk_save,          vk_restore,
    vk_translate,        vk_clip_rect,   vk_set_fill_color,
    vk_set_stroke_color, vk_set_line_width, vk_fill_rect,  vk_stroke_rect,
    vk_fill_rounded_rect, vk_begin_path, vk_move_to,       vk_line_to,
    vk_close_path,       vk_fill,        vk_stroke,        vk_draw_text,
    vk_destroy,          vk_set_font,    vk_measure_text,
    vk_draw_image,       vk_set_line_cap, vk_set_line_join,
    vk_curve_to,         vk_reset_clip,  vk_set_scale_vtable,
    vk_set_antialias_level_vtable, vk_set_scale_filter_vtable};

static my_vgcanvas_t* vk_create_common(const my_allocator_t* allocator,
                                       VkSurfaceKHR surface, int32_t width,
                                       int32_t height, bool offscreen) {
  my_vgcanvas_vulkan_t* c;
  VkCommandPoolCreateInfo pci;
  VkCommandBufferAllocateInfo cai;
  VkCommandBuffer cmds[VKC_FRAMES];
  VkSemaphoreCreateInfo sci;
  VkFenceCreateInfo fci;
  uint32_t i;
  if (vk_global_acquire() != MY_RET_OK) {
    return NULL;
  }
  if (!offscreen) {
    VkBool32 sup = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(g_vk.pdev, g_vk.qfam, surface,
                                         &sup);
    if (sup != VK_TRUE) {
      vk_global_release();
      return NULL;
    }
  }
  c = (my_vgcanvas_vulkan_t*)my_mem_calloc(allocator, 1,
                                           sizeof(my_vgcanvas_vulkan_t));
  if (c == NULL) {
    vk_global_release();
    return NULL;
  }
  c->base.vtable = &s_vk_vtable;
  c->base.capabilities.antialias_levels = MY_VGCANVAS_AA_LEVEL_BIT(0);
  c->base.capabilities.scale_filters =
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_NEAREST) |
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_BILINEAR);
  c->base.capabilities.active_antialias_level = 0u;
  c->base.capabilities.active_scale_filter = MY_SCALE_FILTER_BILINEAR;
  c->allocator = allocator;
  c->offscreen = offscreen;
  c->surface = surface;
  c->fb_w = width;
  c->fb_h = height;
  my_vggeometry_init(&c->geo, allocator);
  c->state.fill_color = my_color_rgba(0, 0, 0, 255);
  c->state.stroke_color = my_color_rgba(0, 0, 0, 255);
  c->state.line_width = 1.0f;
  c->state.line_cap = MY_LINE_CAP_BUTT;
  c->state.line_join = MY_LINE_JOIN_MITER;
  c->state.scale = 1.0f;
  c->state.scale_filter = MY_SCALE_FILTER_BILINEAR;
  c->state.font = NULL;
  c->state.font_size = 16;
  c->state.clip = my_rect_init(0, 0, width, height);
  if (vk_create_targets(c) != MY_RET_OK ||
      vk_create_pipelines(c) != MY_RET_OK) {
    vk_destroy((my_vgcanvas_t*)c);
    return NULL;
  }
  vk_update_capabilities(c);
  if (vk_make_buffer(VKC_VBUF_PER_FRAME * VKC_FRAMES,
                     VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     &c->vbuf, &c->vbuf_mem) != MY_RET_OK ||
      vkMapMemory(g_vk.dev, c->vbuf_mem, 0, VK_WHOLE_SIZE, 0,
                  &c->vbuf_map) != VK_SUCCESS) {
    vk_destroy((my_vgcanvas_t*)c);
    return NULL;
  }
  memset(&pci, 0, sizeof(pci));
  pci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  pci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  pci.queueFamilyIndex = g_vk.qfam;
  if (vkCreateCommandPool(g_vk.dev, &pci, NULL, &c->cmd_pool) !=
      VK_SUCCESS) {
    vk_destroy((my_vgcanvas_t*)c);
    return NULL;
  }
  memset(&cai, 0, sizeof(cai));
  cai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cai.commandPool = c->cmd_pool;
  cai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  cai.commandBufferCount = VKC_FRAMES;
  if (vkAllocateCommandBuffers(g_vk.dev, &cai, cmds) != VK_SUCCESS) {
    vk_destroy((my_vgcanvas_t*)c);
    return NULL;
  }
  memset(&sci, 0, sizeof(sci));
  sci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  memset(&fci, 0, sizeof(fci));
  fci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fci.flags = VK_FENCE_CREATE_SIGNALED_BIT; /* first frame may wait */
  for (i = 0; i < VKC_FRAMES; i++) {
    c->frames[i].cmd = cmds[i];
    c->frames[i].vbuf_off = (VkDeviceSize)i * VKC_VBUF_PER_FRAME;
    if (vkCreateSemaphore(g_vk.dev, &sci, NULL,
                          &c->frames[i].sem_acquire) != VK_SUCCESS ||
        vkCreateSemaphore(g_vk.dev, &sci, NULL,
                          &c->frames[i].sem_present) != VK_SUCCESS ||
        vkCreateFence(g_vk.dev, &fci, NULL, &c->frames[i].fence) !=
            VK_SUCCESS) {
      vk_destroy((my_vgcanvas_t*)c);
      return NULL;
    }
  }
  c->dbg_dump_path = getenv("MYUI_VK_DUMP"); /* debug snapshot (once) */
  c->dbg_dump_frame = 90;
  {
    const char* df = getenv("MYUI_VK_DUMP_FRAME");
    if (df != NULL && atoi(df) > 0) {
      c->dbg_dump_frame = atoi(df);
    }
  }
  return (my_vgcanvas_t*)c;
}

my_vgcanvas_t* my_vgcanvas_vulkan_create(const my_allocator_t* allocator,
                                         void* vk_surface, int32_t width,
                                         int32_t height) {
  if (vk_surface == NULL || width <= 0 || height <= 0) {
    return NULL;
  }
  return vk_create_common(allocator, (VkSurfaceKHR)vk_surface, width,
                          height, false);
}

my_vgcanvas_t* my_vgcanvas_vulkan_create_offscreen(
    const my_allocator_t* allocator, int32_t width, int32_t height) {
  if (width <= 0 || height <= 0) {
    return NULL;
  }
  return vk_create_common(allocator, VK_NULL_HANDLE, width, height, true);
}

/* ---------------- readback (offscreen) ---------------- */

my_ret_t my_vgcanvas_vulkan_readback(my_vgcanvas_t* vg, uint8_t* rgba,
                                     int32_t width, int32_t height) {
  my_vgcanvas_vulkan_t* c = (my_vgcanvas_vulkan_t*)vg;
  VkBuffer buf = VK_NULL_HANDLE;
  VkDeviceMemory mem = VK_NULL_HANDLE;
  VkCommandBuffer cmd;
  VkDeviceSize sz;
  void* map;
  if (c == NULL || rgba == NULL || width != c->fb_w || height != c->fb_h) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!c->offscreen) {
    /* M25c: windowed readback is intentionally NOT_SUPPORTED — swapchain
     * images carry no TRANSFER_SRC (WSI dmabuf constraint), and no caller
     * depends on it (the smoke test uses the offscreen canvas). Read the
     * persistent MSAA/offscreen image instead if this ever becomes
     * needed. */
    return MY_RET_NOT_SUPPORTED;
  }
  if (c->cmd_pending) {
    vk_frame_t* f = &c->frames[c->frame_idx];
    if (vk_flush(c) != MY_RET_OK) {
      return MY_RET_FAIL;
    }
    vkWaitForFences(g_vk.dev, 1, &f->fence, VK_TRUE, UINT64_MAX);
  }
  sz = (VkDeviceSize)width * (VkDeviceSize)height * 4;
  if (vk_make_buffer(sz, VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     &buf, &mem) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (vk_oneshot(&cmd) != MY_RET_OK) {
    vkDestroyBuffer(g_vk.dev, buf, NULL);
    vkFreeMemory(g_vk.dev, mem, NULL);
    return MY_RET_FAIL;
  }
  vk_transition(cmd, c->target_imgs[0],
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                VK_ACCESS_TRANSFER_READ_BIT,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT, 0);
  {
    VkBufferImageCopy cp;
    memset(&cp, 0, sizeof(cp));
    cp.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    cp.imageSubresource.layerCount = 1;
    cp.imageExtent.width = (uint32_t)width;
    cp.imageExtent.height = (uint32_t)height;
    cp.imageExtent.depth = 1;
    vkCmdCopyImageToBuffer(cmd, c->target_imgs[0],
                           VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buf, 1,
                           &cp);
  }
  vk_transition(cmd, c->target_imgs[0],
                VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                VK_ACCESS_TRANSFER_READ_BIT,
                VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                    VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                VK_PIPELINE_STAGE_TRANSFER_BIT,
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0);
  if (vk_oneshot_submit(cmd) != MY_RET_OK) {
    vkDestroyBuffer(g_vk.dev, buf, NULL);
    vkFreeMemory(g_vk.dev, mem, NULL);
    return MY_RET_FAIL;
  }
  vkMapMemory(g_vk.dev, mem, 0, sz, 0, &map);
  memcpy(rgba, map, (size_t)sz);
  vkUnmapMemory(g_vk.dev, mem);
  vkDestroyBuffer(g_vk.dev, buf, NULL);
  vkFreeMemory(g_vk.dev, mem, NULL);
  return MY_RET_OK;
}

#else /* !MYUI_HAS_VULKAN */

void* my_vgcanvas_vulkan_instance(void) {
  return NULL;
}

my_vgcanvas_t* my_vgcanvas_vulkan_create(const my_allocator_t* allocator,
                                         void* vk_surface, int32_t width,
                                         int32_t height) {
  (void)allocator;
  (void)vk_surface;
  (void)width;
  (void)height;
  return NULL;
}

void my_vgcanvas_vulkan_destroy_surface(void* vk_surface) {
  (void)vk_surface;
}

my_vgcanvas_t* my_vgcanvas_vulkan_create_offscreen(
    const my_allocator_t* allocator, int32_t width, int32_t height) {
  (void)allocator;
  (void)width;
  (void)height;
  return NULL;
}

my_ret_t my_vgcanvas_vulkan_resize(my_vgcanvas_t* vg, int32_t width,
                                   int32_t height) {
  (void)vg;
  (void)width;
  (void)height;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_vgcanvas_vulkan_present(my_vgcanvas_t* vg) {
  (void)vg;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_vgcanvas_vulkan_readback(my_vgcanvas_t* vg, uint8_t* rgba,
                                     int32_t width, int32_t height) {
  (void)vg;
  (void)rgba;
  (void)width;
  (void)height;
  return MY_RET_NOT_SUPPORTED;
}

#endif /* MYUI_HAS_VULKAN */
