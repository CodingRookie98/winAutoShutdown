target_sources(winAutoShutdown PRIVATE
       ${CMAKE_CURRENT_SOURCE_DIR}/operationBase.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/operationBase.h
       ${CMAKE_CURRENT_SOURCE_DIR}/operationLogOff.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/operationLogOff.h
       ${CMAKE_CURRENT_SOURCE_DIR}/operationReboot.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/operationReboot.h
       ${CMAKE_CURRENT_SOURCE_DIR}/operationShutdown.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/operationShutdown.h
       ${CMAKE_CURRENT_SOURCE_DIR}/worker.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/worker.h
       ${CMAKE_CURRENT_SOURCE_DIR}/workBase.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/workBase.h
       ${CMAKE_CURRENT_SOURCE_DIR}/workOneShot.cpp
       ${CMAKE_CURRENT_SOURCE_DIR}/workOneShot.h
)
