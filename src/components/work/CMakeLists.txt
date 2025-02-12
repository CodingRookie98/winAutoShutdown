target_sources(winAutoShutdown
        PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} FILES
        worker.h
        work.h
        PRIVATE
        worker.cpp
        work.cpp
)

target_include_directories(winAutoShutdown PUBLIC $${CMAKE_CURRENT_SOURCE_DIR})
