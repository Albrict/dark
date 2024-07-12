cmake_minimum_required( VERSION 3.18.0 )
cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0091 NEW)
project( lands )

set( CMAKE_C_STANDARD 11 CACHE STRING "" FORCE )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")
set( CMAKE_CXX_FLAGS "-ffast-math")
add_executable( main )
set_target_properties( main PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME} )

add_subdirectory( "src" )
add_subdirectory( "libs" )
add_custom_command(TARGET main POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:main>/assets)
