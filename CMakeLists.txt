cmake_minimum_required( VERSION 3.18.0 )
cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0091 NEW)
project( sdl-base )

set( CMAKE_CXX_STANDARD 11 CACHE STRING "" FORCE )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Android" )
    add_library( main SHARED )
else()
    add_executable( main )
    set_target_properties( main PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME} )
    add_custom_command( TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<CONFIG>/assets
        )
endif()

add_subdirectory( "src" )
add_subdirectory( "external" )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten" )
    target_link_options( main PRIVATE "--emrun -sASYNCIFY=1 --preload-file assets" )
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" )
    set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME} )
    set_property( TARGET main PROPERTY WIN32_EXECUTABLE true )
endif()
