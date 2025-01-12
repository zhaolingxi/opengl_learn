cmake_minimum_required(VERSION 3.14)
project(opengl_learn)

# 依赖的基础库头文件包含目录
include_directories(../3rdparty/glad/include)
include_directories(../3rdparty/glad/src)

include_directories(../3rdparty/glfw/include)
link_directories (${triLibraryPath}/glfw/lib/${TARGET_DIRNAME}/)

include_directories(../3rdparty/stb/include)

include_directories(../3rdparty/assimp/include)

include_directories(include src)

file(GLOB_RECURSE H_HEADER_FILES "include/*.h")
file(GLOB_RECURSE HPP_HEADER_FILES "include/*.hpp")
set(HEADER_FILES ${HEADER_FILES} ${H_HEADER_FILES} ${HPP_HEADER_FILES})

# 项目源文件
file(GLOB_RECURSE CPP_SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE C_SOURCE_FILES "src/*.c")
file(GLOB_RECURSE C_SOURCE_FILES "../3rdparty/glad/src/*.c")
set(SOURCE_FILES ${SOURCE_FILES} ${CPP_SOURCE_FILES} ${C_SOURCE_FILES})

file(GLOB_RECURSE GLFW_LIBS "${triLibraryPath}/glfw/lib/${TARGET_DIRNAME}/*.lib" "${triLibraryPath}/assimp/lib/${TARGET_DIRNAME}/*.lib")
message("${triLibraryPath}/glfw/lib/${TARGET_DIRNAME}/")
message(STATUS "Found libs: ${GLFW_LIBS}")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(GLFW_LIBS)
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBS})
else()
    message(FATAL_ERROR "GLFW_LIBS library not found")
endif()

if(MSVC64)
	list(APPEND DEPEND_LIBRARY_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/assimp/lib/${TARGET_DIRNAME}/)
	list(APPEND DEPEND_LIBRARY_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/glfw/lib/openssl/${TARGET_DIRNAME}/)
else()
	#list(APPEND DEPEND_LIBRARY_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()

link_directories(${DEPEND_LIBRARY_PATHS})
copy_depend_libs("${DEPEND_LIBRARY_PATHS}") # 拷贝依赖的基础库文件

if(GNUC)
	target_link_libraries(${PROJECT_NAME} pthread rt dl)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-rpath='$ORIGIN:$ORIGIN/lib'")
endif()
