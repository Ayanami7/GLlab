cmake_minimum_required(VERSION 3.0)
project(QBRender)

set(CMAKE_CXX_STANDARD 17)

file(MAKE_DIRECTORY bin/Debug)
file(MAKE_DIRECTORY bin/Release)
file(MAKE_DIRECTORY bin/spirv)

#设置生成目录
set(publish_bin_debug  ${PROJECT_SOURCE_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${publish_bin_debug})
set(publish_bin_release ${PROJECT_SOURCE_DIR}/bin/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${publish_bin_release})

#编译glad
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/glad)
#编译glfw3
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/glfw)
#编译imgui
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/imgui)
#添加stb
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/stb)
#编译核心库
add_subdirectory(${CMAKE_SOURCE_DIR}/src/core)
#编译主程序
add_subdirectory(${CMAKE_SOURCE_DIR}/src/app)
