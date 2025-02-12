cmake_minimum_required(VERSION 3.29)

project(winAutoShutdown
        VERSION 1.1.0
        LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_compile_options(/utf-8)
endif ()

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(winAutoShutdown
            MANUAL_FINALIZATION
    )
else ()
    add_executable(winAutoShutdown)
endif ()

add_subdirectory(src)
add_subdirectory(translations)

target_link_libraries(winAutoShutdown
        PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)

set_target_properties(winAutoShutdown PROPERTIES
        WIN32_EXECUTABLE TRUE
)

install(TARGETS winAutoShutdown
        BUNDLE DESTINATION "."
        LIBRARY DESTINATION "."
        RUNTIME DESTINATION ".")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install/${CMAKE_BUILD_TYPE}")
set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ".")

find_program(CMAKE_EXE cmake)
add_custom_target(install_all_targets
        COMMAND ${CMAKE_EXE} --install ${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_dependencies(install_all_targets winAutoShutdown)
include(InstallRequiredSystemLibraries)

if (CMAKE_BUILD_TYPE MATCHES "Release")
    if (WIN32)
        find_program(QT_DEPLOY_QT NAMES windeployqt)
        add_custom_target(qt_deploy_release
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_INSTALL_PREFIX} ${CMAKE_SOURCE_DIR}/dist
                COMMAND ${QT_DEPLOY_QT} --release --qmldir=${CMAKE_CURRENT_LIST_DIR}
                --plugindir ${CMAKE_SOURCE_DIR}/dist --no-translations --no-compiler-runtime --no-system-d3d-compiler
                --no-quick-import --no-system-dxc-compiler --no-opengl-sw --skip-plugin-types "generic,iconengines,imageformats,networkinformation,tls"
                ${CMAKE_SOURCE_DIR}/dist/${PROJECT_NAME}.exe
                COMMENT "Windows Deploying Qt Dependencies After Build........."
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
        add_dependencies(qt_deploy_release install_all_targets)

        set(CPACK_GENERATOR 7Z)
        set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
        set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
        set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT_NAME}_VERSION_PATCH}")
        set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
        set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}-${${PROJECT_NAME}_VERSION}-${CMAKE_BUILD_TYPE}")
        set(CPACK_PACKAGE_CHECKSUM "SHA256")
        set(CPACK_INSTALLED_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/dist" ".")
        include(CPack)
        find_program(CPACK_EXE NAMES cpack)
        add_custom_target(cpack_all
                COMMAND ${CPACK_EXE} --config CPackConfig.cmake
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
        add_dependencies(cpack_all qt_deploy_release)
    endif ()
endif ()

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(winAutoShutdown)
endif ()
