﻿#整体cmake设置
cmake_minimum_required (VERSION 3.14)
project ("RenderZ")


set(CMAKE_CXX_STANDARD 17)

# 默认生成linux64位下的debug版
if (NOT PLATFORM_NAME)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(PLATFORM_NAME "LINUX64")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(PLATFORM_NAME "WIN64")
    else()
        message(FATAL "Unsupported current operating system.")
    endif()
endif()


# cmake模块路径
set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/makefile/cmake
	${CMAKE_CURRENT_SOURCE_DIR}/makefile/cmake/platforms/
)
# 编译默认配置和编译路径
include(build_utils)
config_target_path(${CMAKE_CURRENT_SOURCE_DIR})
config_build_path(${CMAKE_CURRENT_SOURCE_DIR})

# 公共编译选项
include(common)
# 不同平台的编译选项
if (MSVC)
	message("Info: set windows ${PROJECT_NAME} compile flag, MSVC: ${MSVC}")
	include(windows)
    cmake_host_system_information(RESULT CPU_NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
    add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP${CPU_NUMBER_OF_LOGICAL_CORES}>)
elseif(GNUC)
	message("Info: set linux ${PROJECT_NAME} compile flag, GNUC: ${GNUC}")
	include(linux)
endif()
message("---compile ${PROJECT_NAME} Platform: ${PLATFORM_NAME}, Debug: ${DEBUG}, CXX: ${CMAKE_CXX_COMPILER}")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(MSVC)
    add_compile_options(/MP)
endif()

set(triLibraryPath ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
set(assertPath ${CMAKE_CURRENT_SOURCE_DIR}/opengl_learn/assert)
add_definitions(-DASSERT_PATH="${assertPath}")
include_directories(${triLibraryPath})


add_subdirectory ("opengl_learn") 
