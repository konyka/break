#pragma once

#include <renderer/sl_dlss.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Build-time optional adapter. `module` is the loaded sl.interposer.dll
 * HMODULE returned by LoadLibrary; ownership remains with the C loader. */
bool sl_dlss_streamline_adapter_create(void *module, SLDlssCppAdapter *out);

#ifdef __cplusplus
}
#endif
