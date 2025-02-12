add_subdirectory(operations)
add_subdirectory(work)

target_include_directories(winAutoShutdown PUBLIC "./operations" "./work")