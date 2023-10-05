/*****************************************************************************
 *
 * 	break engine source file.
 * 	copyright (C), break
 *
 * 	file name:   base_application.h
 * 	version:     v1.0.0
 * 	created:     2023/10/4 by SandBox
 * 	compilers:   visual studio、clang、gcc
 * 	description:
 * ---------------------------------------------------------------------------
 * 	history:
 *
 *****************************************************************************/

#ifndef __BREAK_FRAMEWORK_COMMON_BASE_APPLICATION_H__
#define __BREAK_FRAMEWORK_COMMON_BASE_APPLICATION_H__
#include "application_interface.h"

namespace bk {

class BaseApplication : public ApplicationInterface {
 public:
  virtual int Init() override;
  virtual void DeInit() override;
  virtual void Tick() override;

  virtual bool IsQuit() override;

 protected:
  bool is_quit_ { false };
};

} // bk

#endif //__BREAK_FRAMEWORK_COMMON_BASE_APPLICATION_H__
