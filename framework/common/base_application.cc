/*****************************************************************************
 *
 * 	break engine source file.
 * 	copyright (C), break
 *
 * 	file name:   base_application.cc
 * 	version:     v1.0.0
 * 	created:     2023/10/4 by SandBox
 * 	compilers:   visual studio、clang、gcc
 * 	description:
 * ---------------------------------------------------------------------------
 * 	history:
 *
 *****************************************************************************/

#include "base_application.h"
#include <stdio.h>

namespace bk {
/***
 * @brief 解析命令行参数 读取配置文件 初始化所有子模块
 * @return
 *      0: 没有错误
 *      其他值：错误
 */
int BaseApplication::Init() {
  is_quit_ = false;
  return 0;
}

/***
 * @brief 清理所有子模块以及清理所有资源
 */
void BaseApplication::DeInit() {

}

/***
 * @brief 主循环
 */
void BaseApplication::Tick() {
}

/***
 * @brief 判断是否需要退出逻辑
 * @return true: 推出
 *          false: 不推出
 */
bool BaseApplication::IsQuit() {
    return is_quit_;
}

} // bk