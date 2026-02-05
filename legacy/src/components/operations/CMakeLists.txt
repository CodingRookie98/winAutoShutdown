target_sources(winAutoShutdown PUBLIC
        PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} FILES
        operation_base.h
        power_action.h
        PRIVATE
        power_action.cpp
)

target_include_directories(winAutoShutdown PUBLIC $${CMAKE_CURRENT_SOURCE_DIR})