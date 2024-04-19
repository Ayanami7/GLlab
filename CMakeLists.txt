cmake_minimum_required(VERSION 3.0)
project(vkproj)

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

add_executable(obj
    src/main.cpp
    src/common.h
    src/common.cpp
    src/widget.h
    src/widget.cpp
    src/loadShader.h
    src/loadShader.cpp
)
target_compile_options(obj PUBLIC /utf-8) # MSVC unicode support
add_dependencies(obj imgui)
add_dependencies(obj glad)

target_include_directories(obj
PUBLIC
    ext/glm
    ext/stb
    ${IMGUI_INCLUDE}
)

target_link_libraries(obj PUBLIC imgui)
target_link_libraries(obj PUBLIC glad)
target_link_libraries(obj PUBLIC glfw)
