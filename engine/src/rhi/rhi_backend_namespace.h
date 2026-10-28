#ifndef RHI_BACKEND_NAMESPACE_H
#define RHI_BACKEND_NAMESPACE_H

#if defined(RHI_BACKEND_NAMESPACE_GL) && defined(RHI_BACKEND_NAMESPACE_VK)
#error "Only one RHI backend namespace can be active"
#endif

#if defined(RHI_BACKEND_NAMESPACE_GL)
#include "rhi/dispatch/rhi_backend_rename_gl.h"
#elif defined(RHI_BACKEND_NAMESPACE_VK)
#include "rhi/dispatch/rhi_backend_rename_vk.h"
#endif

#endif
