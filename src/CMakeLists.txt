add_subdirectory(ui)
add_subdirectory(components)
add_subdirectory(res)
target_sources(winAutoShutdown PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)


