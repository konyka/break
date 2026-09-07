#include "mypal/my_pal.h"

#include <stdatomic.h>
#include <string.h>

#define MY_PAL_VULKAN_PROVIDER_SLOTS 64u

typedef struct my_pal_vulkan_slot_t {
  my_pal_t* pal;
  my_pal_vulkan_provider_t provider;
  uint32_t active_queries;
  bool retiring;
} my_pal_vulkan_slot_t;

static my_pal_vulkan_slot_t s_slots[MY_PAL_VULKAN_PROVIDER_SLOTS];
static atomic_flag s_lock = ATOMIC_FLAG_INIT;

static void vulkan_lock(void) {
  while (atomic_flag_test_and_set_explicit(&s_lock, memory_order_acquire)) {
  }
}

static void vulkan_unlock(void) {
  atomic_flag_clear_explicit(&s_lock, memory_order_release);
}

static void vulkan_release_provider(
    const my_pal_vulkan_provider_t* provider) {
  if (provider != NULL && provider->release_context != NULL) {
    provider->release_context(provider->context);
  }
}

my_ret_t my_pal_register_vulkan_provider(
    my_pal_t* pal, const my_pal_vulkan_provider_t* provider) {
  size_t i;
  my_pal_vulkan_provider_t replaced = {0};
  if (pal == NULL || provider == NULL) return MY_RET_INVALID_PARAMS;
  if (provider->size < offsetof(my_pal_vulkan_provider_t, release_context) +
                           sizeof(provider->release_context) ||
      provider->abi_version != MY_PAL_VULKAN_PROVIDER_ABI_VERSION ||
      provider->get_instance_extensions == NULL ||
      provider->release_context == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  vulkan_lock();
  for (i = 0; i < MY_PAL_VULKAN_PROVIDER_SLOTS; ++i) {
    if (s_slots[i].pal == pal && s_slots[i].active_queries != 0u) {
      vulkan_unlock();
      return MY_RET_PENDING;
    }
    if (s_slots[i].pal == pal ||
        (s_slots[i].pal == NULL && !s_slots[i].retiring)) {
      if (s_slots[i].pal == pal) replaced = s_slots[i].provider;
      s_slots[i].pal = pal;
      s_slots[i].provider = *provider;
      s_slots[i].retiring = false;
      vulkan_unlock();
      vulkan_release_provider(&replaced);
      return MY_RET_OK;
    }
  }
  vulkan_unlock();
  return MY_RET_OOM;
}

void my_pal_unregister_vulkan_provider(my_pal_t* pal) {
  size_t i;
  my_pal_vulkan_provider_t provider = {0};
  if (pal == NULL) return;
  vulkan_lock();
  for (i = 0; i < MY_PAL_VULKAN_PROVIDER_SLOTS; ++i) {
    if (s_slots[i].pal == pal) {
      s_slots[i].retiring = true;
      if (s_slots[i].active_queries == 0u) {
        provider = s_slots[i].provider;
        s_slots[i].pal = NULL;
        s_slots[i].provider = (my_pal_vulkan_provider_t){0};
        s_slots[i].retiring = false;
      }
      break;
    }
  }
  vulkan_unlock();
  vulkan_release_provider(&provider);
}

my_ret_t my_pal_get_vulkan_instance_extensions(
    my_pal_t* pal, my_pal_window_t* window,
    my_pal_vulkan_instance_extensions_t* out) {
  my_pal_vulkan_provider_t provider = {0};
  my_pal_vulkan_provider_t retired_provider = {0};
  size_t slot_index = SIZE_MAX;
  size_t i;
  my_ret_t ret;
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  memset(out, 0, sizeof(*out));
  if (pal == NULL) return MY_RET_NOT_SUPPORTED;

  vulkan_lock();
  for (i = 0; i < MY_PAL_VULKAN_PROVIDER_SLOTS; ++i) {
    if (s_slots[i].pal == pal) {
      slot_index = i;
      provider = s_slots[i].provider;
      if (s_slots[i].retiring || s_slots[i].active_queries == UINT32_MAX) {
        provider.get_instance_extensions = NULL;
      } else {
        ++s_slots[i].active_queries;
      }
      break;
    }
  }
  vulkan_unlock();
  if (provider.get_instance_extensions == NULL) return MY_RET_NOT_SUPPORTED;

  {
    const char *const *names = NULL;
    uint32_t count = 0u;
    uint32_t j;
    ret = provider.get_instance_extensions(provider.context, window, &names,
                                           &count);
    if (ret == MY_RET_OK &&
        (count > MYUI_VULKAN_MAX_INSTANCE_EXTENSIONS ||
         (count != 0u && names == NULL))) {
      ret = MY_RET_INVALID_PARAMS;
    }
    if (ret == MY_RET_OK) {
      for (j = 0; j < count; ++j) {
        size_t length = 0u;
        if (names[j] == NULL || names[j][0] == '\0') {
          ret = MY_RET_INVALID_PARAMS;
          break;
        }
        while (length < MYUI_VULKAN_MAX_EXTENSION_NAME &&
               names[j][length] != '\0') {
          ++length;
        }
        if (length >= MYUI_VULKAN_MAX_EXTENSION_NAME) {
          ret = MY_RET_INVALID_PARAMS;
          break;
        }
        memcpy(out->names[j], names[j], length + 1u);
      }
      if (ret == MY_RET_OK) out->count = count;
    }
  }
  if (ret != MY_RET_OK) {
    memset(out, 0, sizeof(*out));
  }
  vulkan_lock();
  if (slot_index < MY_PAL_VULKAN_PROVIDER_SLOTS &&
      s_slots[slot_index].active_queries != 0u) {
    --s_slots[slot_index].active_queries;
    if (s_slots[slot_index].active_queries == 0u &&
        s_slots[slot_index].retiring) {
      retired_provider = s_slots[slot_index].provider;
      s_slots[slot_index].pal = NULL;
      s_slots[slot_index].provider = (my_pal_vulkan_provider_t){0};
      s_slots[slot_index].retiring = false;
    }
  }
  vulkan_unlock();
  vulkan_release_provider(&retired_provider);
  return ret;
}
