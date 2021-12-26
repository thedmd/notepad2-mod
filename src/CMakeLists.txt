
file(
    GLOB sources
    CONFIGURE_DEPENDS
    *
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

add_executable(Notepad2-mod WIN32 ${sources})

target_compile_definitions(Notepad2-mod
    PRIVATE
        BOOKMARK_EDITION
)

target_link_libraries(Notepad2-mod
    PRIVATE
        Lexilla
        Scintilla
)

#set_property(TARGET Lexilla PROPERTY FOLDER "external")