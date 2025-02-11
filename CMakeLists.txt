cmake_minimum_required(VERSION 3.5)

project(winAutoShutdown VERSION 1.0.2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
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

target_link_libraries(winAutoShutdown PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(winAutoShutdown PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

install(TARGETS winAutoShutdown
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(winAutoShutdown)
endif ()
