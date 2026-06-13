# Native MSVC (cl.exe) - typically auto-detected on Windows
# This file is mostly for documentation/CI purposes
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)
# MSVC is usually auto-detected; this file ensures explicit selection
