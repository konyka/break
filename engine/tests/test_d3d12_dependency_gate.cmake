if(NOT WIN32)
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (non-Windows host)")
    return()
endif()

find_path(D3D12_INCLUDE_DIR d3d12.h
    PATHS "$ENV{WindowsSdkDir}/Include"
    PATH_SUFFIXES um)
find_path(DXGI_INCLUDE_DIR NAMES dxgi.h dxgi1_4.h dxgi1_6.h
    PATHS "$ENV{WindowsSdkDir}/Include"
    PATH_SUFFIXES shared um)
find_library(D3D12_LIBRARY NAMES d3d12)
find_library(DXGI_LIBRARY NAMES dxgi)
find_program(DXC_EXECUTABLE NAMES dxc dxc.exe)

if(NOT D3D12_INCLUDE_DIR OR NOT DXGI_INCLUDE_DIR OR NOT D3D12_LIBRARY OR NOT DXGI_LIBRARY OR
   NOT DXC_EXECUTABLE)
    message(STATUS
        "D3D12 dependency gate: UNAVAILABLE (headers/libs/compiler incomplete)")
    message(STATUS "  d3d12_include=${D3D12_INCLUDE_DIR}")
    message(STATUS "  dxgi_include=${DXGI_INCLUDE_DIR}")
    message(STATUS "  d3d12_library=${D3D12_LIBRARY}")
    message(STATUS "  dxgi_library=${DXGI_LIBRARY}")
    message(STATUS "  dxc=${DXC_EXECUTABLE}")
    return(77)
endif()

message(STATUS "D3D12 dependency gate: COMPILE_DEPENDENCIES_AVAILABLE")
message(STATUS "  d3d12_include=${D3D12_INCLUDE_DIR}")
message(STATUS "  dxgi_include=${DXGI_INCLUDE_DIR}")
message(STATUS "  d3d12_library=${D3D12_LIBRARY}")
message(STATUS "  dxgi_library=${DXGI_LIBRARY}")
message(STATUS "  dxc=${DXC_EXECUTABLE}")
