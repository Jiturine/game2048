cmake_minimum_required (VERSION 3.8)
project (game2048)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

FILE(GLOB_RECURSE PIXEL_FILES   
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
                    )

set ( CMAKE_UNITY_BUILD_BATCH_SIZE 16 )

SET(RW_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR})
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/sysconfig/SysConfig.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/sysconfig/SysConfig.h
  )

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/opengl/libs)

add_executable (game2048 ${PIXEL_FILES})


MACRO( collect_head_dirs return_list )
    FILE(GLOB_RECURSE new_list 
                      ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
                      ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/src/*.tpp
                      )
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

collect_head_dirs( src_header_dirs )

target_include_directories ( game2048 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/opengl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog/include
    ${src_header_dirs}
    ${CMAKE_CURRENT_SOURCE_DIR}/sysconfig
    )

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
    
if(MSVC)
    target_link_libraries(game2048 glfw3 OpenGL32) 
elseif(MINGW)
    target_link_libraries(game2048 libglfw3.a OpenGL32)
endif()
target_link_libraries(game2048 ${FREETYPE_LIBRARIES})

install(TARGETS game2048 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)