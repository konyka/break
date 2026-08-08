# Clang on Linux
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_LINKER lld)
# CMAKE_LINKER alone does not make the clang driver select lld. This is
# required when Release IPO emits LLVM bitcode into libengine.a.
set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_AR llvm-ar)
set(CMAKE_RANLIB llvm-ranlib)
