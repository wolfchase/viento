cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("Viento")

# Unix like systems

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
    
# Windows
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

# Hell if I know what this does
if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

# Set some helper variables for paths
set(VIENTO_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE ${VIENTO_DIRECTORY}/include)

# Add include folder
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add src folder
add_subdirectory(src)

add_executable(viento ${SOURCE} ${HEADERS})

# Set appropriate C++ standard
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set_property(TARGET viento PROPERTY CXX_STANDARD 14)
    set_property(TARGET viento PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# Messy options for bin output for VS, clean up later
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_target_properties( viento PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${VIENTO_DIRECTORY}/bin/win32/debug )
    set_target_properties( viento PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${VIENTO_DIRECTORY}/bin/win32/release )
    set_target_properties( viento PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${VIENTO_DIRECTORY}/bin/win32 )
    set_target_properties( viento PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${VIENTO_DIRECTORY}/bin/win32/debug )
    set_target_properties( viento PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${VIENTO_DIRECTORY}/bin/win32/release )
	set( EXECUTABLE_OUTPUT_PATH "../" )
	SET_TARGET_PROPERTIES( viento  PROPERTIES PREFIX "../")
endif()