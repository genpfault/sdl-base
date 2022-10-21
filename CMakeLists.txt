cmake_minimum_required( VERSION 3.18.0 )
cmake_policy(SET CMP0091 NEW)
project( sdl-base )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE )

set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )

set( SDL_LIBC ON CACHE BOOL "" FORCE )
set( SDL_TEST OFF CACHE BOOL "" FORCE )
add_subdirectory( external/sdl )

set( SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE )
set( SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory( external/sdl-image )

set( SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2TTF_VENDORED ON CACHE BOOL "" FORCE )
set( SDL2TTF_HARFBUZZ ON CACHE BOOL "" FORCE )
add_subdirectory( external/sdl-ttf )

set( SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE )
set( SDL2MIXER_DEPS_SHARED OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_FLAC OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MOD OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MP3 OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MIDI OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_OPUS OFF CACHE BOOL "" FORCE )
add_subdirectory( external/sdl-mixer )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Android" )
    add_compile_definitions( GLM_LANG_STL11_FORCED )
endif()
include_directories( SYSTEM "external/glm" )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --emrun -sASYNCIFY=1")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

# project setup
set( SRCS
    "src/main.cpp"
    )
set( LIBS
    SDL2::SDL2main
    SDL2::SDL2-static
    SDL2_image::SDL2_image-static
    SDL2_ttf::SDL2_ttf-static
    SDL2_mixer::SDL2_mixer-static
    )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Android" )
    add_library( main SHARED ${SRCS} )
    target_link_libraries( main PRIVATE ${LIBS} )
else()
    add_executable( ${CMAKE_PROJECT_NAME} ${SRCS} )
    target_link_libraries( ${CMAKE_PROJECT_NAME} PRIVATE ${LIBS} )
endif()

if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" )
    set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME} )
    set_property( TARGET ${CMAKE_PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true )
endif()
