cmake_minimum_required(VERSION 3.21)

project(Lexilla VERSION 5.1.4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(
    GLOB sources
    CONFIGURE_DEPENDS
    include/*
    lexers/*
    lexlib/*
    src/*
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

add_library(Lexilla STATIC ${sources})

target_include_directories(Lexilla
    PUBLIC
        include
    PRIVATE
        lexlib
        src
)

target_link_libraries(Lexilla
    PUBLIC
        Scintilla
)

set_property(TARGET Lexilla PROPERTY FOLDER "external")