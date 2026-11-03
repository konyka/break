#ifndef TEST_VULKAN_LSAN_H
#define TEST_VULKAN_LSAN_H

#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if defined(__linux__) && \
    (defined(__SANITIZE_ADDRESS__) || __has_feature(address_sanitizer))
/* Keeping the ICD mapped lets LSan attribute its process-lifetime caches.
 * These module-only rules cannot match allocations from the statically linked
 * engine tests; libdbus is deliberately not suppressed. */
const char *__lsan_default_suppressions(void) {
  return "leak:libnvidia-glcore.so\n"
         "leak:libnvidia-glsi.so\n";
}
#endif

#endif
