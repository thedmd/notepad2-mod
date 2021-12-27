cmake_minimum_required(VERSION 3.21)

project(Notepad2-mod VERSION 4.2.25 LANGUAGES CXX)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "In source buils are not supported.")
endif()

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
    # Enable multi-processor compilation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

    # Treat all sources as utf-8
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

# Enable Unicode builds
add_definitions(
    -DUNICODE
    -D_UNICODE
)

# Include external sources
add_subdirectory(external/scintilla)
add_subdirectory(external/lexilla)

# Fetch version details
include(tools/np2_get_version.cmake)
np2_get_version(
    VERSION             VERSION_REV
    HEAD                VERSION_HASH
    BASE                VERSION_MERGE_BASE
    BASE_VERSION        VERSION_MERGE_BASE_REV
    BRANCH              VERSION_BRANCH
    FULL                VERSION_REV_FULL
    HAS_LOCAL_CHANGES   np2_with_local_changes
)

if (VERSION_BRANCH)
    message(STATUS "On branch: ${VERSION_BRANCH}")
endif()
message(STATUS "Hash:      ${VERSION_HASH}")
if (np2_with_local_changes)
    message(STATUS "Revision:  ${VERSION_REV} (Local modifications found)")
else()
    message(STATUS "Revision:  ${VERSION_REV}")
endif()
if (VERSION_MERGE_BASE)
    message(STATUS "Mergebase: master@${VERSION_MERGE_BASE_REV} (${VERSION_MERGE_BASE})")
endif()

# Configure files
foreach(unconfigured
    src/Version.h
    res/Notepad2.exe.manifest
)
    set(configured ${CMAKE_CURRENT_BINARY_DIR}/Configured/${unconfigured})
    configure_file(${unconfigured}.in ${configured} @ONLY)
    list(APPEND configured_sources ${configured})
endforeach()

source_group(TREE ${CMAKE_CURRENT_BINARY_DIR}/Configured FILES ${configured_sources})

# Collect sources
file(
    GLOB notepad_sources
    CONFIGURE_DEPENDS
    res/*
    src/*
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${notepad_sources})

# Add target
add_executable(${PROJECT_NAME} WIN32
    ${notepad_sources}
    ${configured_sources}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/Configured/src
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        BOOKMARK_EDITION
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Lexilla
        Scintilla

        comctl32
        imm32
        shlwapi
        msimg32
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")
