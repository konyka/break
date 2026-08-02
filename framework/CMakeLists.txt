# R433: modest warnings for framework targets (no -Werror — existing code
# is not warning-clean and must not break the build).
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

add_subdirectory(common)
