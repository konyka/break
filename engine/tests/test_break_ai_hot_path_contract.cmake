if(NOT DEFINED AI_SOURCE_DIR)
    message(FATAL_ERROR "AI_SOURCE_DIR is required")
endif()

foreach(source IN ITEMS
        break_nav_query.c
        break_ai_obstacle.c
        break_ai_query.c)
    file(READ "${AI_SOURCE_DIR}/${source}" source_text)
    if(source_text MATCHES "(malloc|calloc|realloc|free)[ \t\r\n]*\\(")
        message(FATAL_ERROR "${source} allocates in a query hot path")
    endif()
endforeach()
