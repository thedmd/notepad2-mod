cmake_minimum_required(VERSION 3.21)

project(Scintilla VERSION 5.1.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(
    GLOB sources
    CONFIGURE_DEPENDS
    include/*
    call/*
    src/*
    win32/*
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

add_library(Scintilla STATIC ${sources})

target_include_directories(Scintilla
    PUBLIC
        include
    PRIVATE
        src
)

set_property(TARGET Scintilla PROPERTY FOLDER "external")