#include "mypal/my_pal.h"

#include <stdatomic.h>

#define MY_PAL_MEDIA_PROVIDER_SLOTS 64u

typedef struct my_pal_media_slot_t {
  my_pal_t* pal;
  my_pal_media_provider_t provider;
  uint32_t active_queries;
  bool retiring;
} my_pal_media_slot_t;

static my_pal_media_slot_t s_slots[MY_PAL_MEDIA_PROVIDER_SLOTS];
static atomic_flag s_lock = ATOMIC_FLAG_INIT;

static void media_lock(void) {
  while (atomic_flag_test_and_set_explicit(&s_lock, memory_order_acquire)) {
  }
}

static void media_unlock(void) {
  atomic_flag_clear_explicit(&s_lock, memory_order_release);
}

static void media_release_provider(const my_pal_media_provider_t* provider) {
  if (provider != NULL && provider->release_context != NULL) {
    provider->release_context(provider->context);
  }
}

my_ret_t my_pal_register_media_provider(
    my_pal_t* pal, const my_pal_media_provider_t* provider) {
  size_t i;
  my_pal_media_provider_t replaced = {0};
  if (pal == NULL || provider == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (provider->size < offsetof(my_pal_media_provider_t, release_context) +
                           sizeof(provider->release_context) ||
      provider->abi_version != MY_PAL_MEDIA_PROVIDER_ABI_VERSION ||
      provider->get_context == NULL || provider->release_context == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  media_lock();
  for (i = 0; i < MY_PAL_MEDIA_PROVIDER_SLOTS; i++) {
    if (s_slots[i].pal == pal && s_slots[i].active_queries != 0u) {
      media_unlock();
      return MY_RET_PENDING;
    }
    /* A retiring slot keeps its PAL identity until the last query leaves.
     * Do not reuse it: the PAL may already be in destruction, and its
     * provider context must remain owned by the in-flight query. */
    if (s_slots[i].pal == pal ||
        (s_slots[i].pal == NULL && !s_slots[i].retiring)) {
      if (s_slots[i].pal == pal) {
        replaced = s_slots[i].provider;
      }
      s_slots[i].pal = pal;
      s_slots[i].provider = *provider;
      s_slots[i].retiring = false;
      media_unlock();
      media_release_provider(&replaced);
      return MY_RET_OK;
    }
  }
  media_unlock();
  return MY_RET_OOM;
}

void my_pal_unregister_media_provider(my_pal_t* pal) {
  size_t i;
  my_pal_media_provider_t provider = {0};
  if (pal == NULL) return;
  media_lock();
  for (i = 0; i < MY_PAL_MEDIA_PROVIDER_SLOTS; i++) {
    if (s_slots[i].pal == pal) {
      s_slots[i].retiring = true;
      if (s_slots[i].active_queries == 0u) {
        provider = s_slots[i].provider;
        s_slots[i].pal = NULL;
        s_slots[i].provider = (my_pal_media_provider_t){0};
        s_slots[i].retiring = false;
      }
      break;
    }
  }
  media_unlock();
  media_release_provider(&provider);
}

my_ret_t my_pal_get_media_context_ex(my_pal_t* pal,
                                     my_pal_media_context_ex_t* out) {
  my_pal_media_provider_t provider = {0};
  size_t i;
  size_t slot_index = SIZE_MAX;
  my_ret_t ret;
  my_pal_media_provider_t retired_provider = {0};
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = (my_pal_media_context_ex_t){0};
  if (pal == NULL) return MY_RET_NOT_SUPPORTED;
  media_lock();
  for (i = 0; i < MY_PAL_MEDIA_PROVIDER_SLOTS; i++) {
    if (s_slots[i].pal == pal) {
      slot_index = i;
      provider = s_slots[i].provider;
      if (s_slots[i].retiring) {
        provider.get_context = NULL;
        break;
      }
      if (s_slots[i].active_queries == UINT32_MAX) {
        provider.get_context = NULL;
      } else {
        s_slots[i].active_queries++;
      }
      break;
    }
  }
  media_unlock();
  if (provider.get_context == NULL) return MY_RET_NOT_SUPPORTED;
  ret = provider.get_context(provider.context, out);
  if (ret == MY_RET_OK) {
    out->base.capabilities &= MY_PAL_MEDIA_CAP_ALL;
    out->known &= MY_PAL_MEDIA_KNOWN_ALL;
  }
  media_lock();
  if (slot_index < MY_PAL_MEDIA_PROVIDER_SLOTS &&
      s_slots[slot_index].active_queries != 0u) {
    s_slots[slot_index].active_queries--;
    if (s_slots[slot_index].active_queries == 0u &&
        s_slots[slot_index].retiring) {
      retired_provider = s_slots[slot_index].provider;
      s_slots[slot_index].pal = NULL;
      s_slots[slot_index].provider = (my_pal_media_provider_t){0};
      s_slots[slot_index].retiring = false;
    }
  }
  media_unlock();
  media_release_provider(&retired_provider);
  return ret;
}
