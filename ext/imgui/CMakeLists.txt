file(GLOB IMGUI_SRC "*.cpp" "*.hpp" "*.h")
file(GLOB IMGUI_INCLUDE "*.h")

add_library(imgui STATIC
    ${IMGUI_SRC}
)
add_dependencies(imgui glfw)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ext/glfw/include
)

target_link_libraries(imgui PUBLIC
    glfw
)