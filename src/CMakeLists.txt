add_executable(viento main.cpp viento.cpp
                      ${VIENTO_DIRECTORY}/include/viento.h)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_target_properties( viento PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${VIENTO_DIRECTORY}/bin/win32/debug )
    set_target_properties( viento PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${VIENTO_DIRECTORY}/bin/win32/release )
    set_target_properties( viento PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${VIENTO_DIRECTORY}/bin/win32 )
    set_target_properties( viento PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${VIENTO_DIRECTORY}/bin/win32/debug )
    set_target_properties( viento PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${VIENTO_DIRECTORY}/bin/win32/release )
	set( EXECUTABLE_OUTPUT_PATH "../" )
	SET_TARGET_PROPERTIES( viento  PROPERTIES PREFIX "../")
endif()
