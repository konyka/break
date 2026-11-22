add_library(common
        base_application.cc
        graphics_manager.cc
        main.cc
)
target_include_directories(common PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../interface
)

if(TARGET runtime_core AND TARGET engine)
    if(ENGINE_BUILD_TESTS)
        if(MSVC)
            set_property(SOURCE main.cc APPEND PROPERTY COMPILE_OPTIONS /wd4100)
        else()
            set_property(SOURCE main.cc APPEND PROPERTY COMPILE_OPTIONS -Wno-unused-parameter)
        endif()
    endif()

    add_library(common_runtime STATIC runtime_bus_application.cc)
    set_property(TARGET common_runtime PROPERTY CXX_STANDARD 20)
    set_property(TARGET common_runtime PROPERTY CXX_STANDARD_REQUIRED ON)
    target_link_libraries(common_runtime PUBLIC
            common
            runtime_core
            engine
            Threads::Threads
    )
endif()
