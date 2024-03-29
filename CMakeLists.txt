cmake_minimum_required(VERSION 3.23)
project(EventLoop VERSION 0.0.1)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(${PROJECT_NAME} SHARED)

if (CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif ()

# For cross compiling, this needs to change
if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)")
    target_compile_definitions(${PROJECT_NAME} PUBLIC __x86__)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "(amd64)|(AMD64)|(EM64T)|(em64t)|(ARM64)|(arm64)|(IA64)|(ia64)")
    target_compile_definitions(${PROJECT_NAME} PUBLIC __x64__)
endif ()

target_sources(${PROJECT_NAME}
        PRIVATE
            src/eventloop.cpp
            src/application.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

enable_testing()
add_subdirectory(tests)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

generate_export_header(${PROJECT_NAME}
        EXPORT_FILE_NAME
            ${CMAKE_SOURCE_DIR}/include/eventloop_export.hpp)

set(PUBLIC_HEADERS
        include/eventloop_export.hpp
        include/eventloop.hpp
        include/event.hpp
        include/application.hpp)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})

install(TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}Targets"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT "${PROJECT_NAME}Targets"
        FILE "${PROJECT_NAME}Targets.cmake"
        NAMESPACE ${namespace}::
        DESTINATION cmake)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION cmake)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION cmake)

export(EXPORT "${PROJECT_NAME}Targets"
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
        NAMESPACE ${namespace}::)

configure_file(EventLoop.pc.in EventLoop.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/EventLoop.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
