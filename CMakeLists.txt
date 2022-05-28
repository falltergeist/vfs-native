cmake_minimum_required(VERSION 3.8)
project(falltergeist_vfs_native VERSION 0.1.0 DESCRIPTION "Virtual File System native FS module")

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/submodules")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT TARGET falltergeist::vfs)
    add_subdirectory(submodules/falltergeist/vfs)
endif()

add_library(${PROJECT_NAME} STATIC)
add_library(falltergeist::vfs::native ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    src/NativeDriver.cpp
    src/NativeFile.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
)

include(GNUInstallDirs)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    # where the library itself will look for its internal headers
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
    # where top-level project will look for the library's public headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # where external projects will look for the library's public headers
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(
    ${PROJECT_NAME}
    falltergeist::vfs
)
