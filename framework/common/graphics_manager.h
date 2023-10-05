/*****************************************************************************
 * 
 * 	break engine source file.
 * 	copyright (C), break 
 * 
 * 	file name:   graphics_manager.h
 * 	version:     v1.0.0
 * 	created:     2023/10/5 by SandBox
 * 	compilers:   visual studio、clang、gcc
 * 	description: 
 * ---------------------------------------------------------------------------
 * 	history: 
 * 
 *****************************************************************************/

//

#ifndef __BREAK_FRAMEWORK_COMMON_GRAPHICS_MANAGER_H__
#define __BREAK_FRAMEWORK_COMMON_GRAPHICS_MANAGER_H__
#include "runtime_module_interface.h"

namespace bk {

class GraphicsManager : public RuntimeModuleInterface {
 public:
  virtual ~GraphicsManager() {}
};

} // bk

#endif //__BREAK_FRAMEWORK_COMMON_GRAPHICS_MANAGER_H__
