/*****************************************************************************
 * 
 * 	break engine source file.
 * 	copyright (C), break 
 * 
 * 	file name:   runtime_module_interface.h
 * 	version:     v1.0.0
 * 	created:     2023/10/4 by SandBox
 * 	compilers:   visual studio、clang、gcc
 * 	description: 
 * ---------------------------------------------------------------------------
 * 	history: 
 * 
 *****************************************************************************/



#ifndef __BREAK_FRAMEWORK_INTERFACE_RUNTIME_MODULE_INTERFACE_H__
#define __BREAK_FRAMEWORK_INTERFACE_RUNTIME_MODULE_INTERFACE_H__

namespace bk {

class RuntimeModuleInterface {
 public:
  virtual ~RuntimeModuleInterface() {};

  virtual int Init() = 0;
  virtual void DeInit() = 0;
  virtual void Tick() = 0;
};

} // bk

#endif //__BREAK_FRAMEWORK_INTERFACE_RUNTIME_MODULE_INTERFACE_H__
