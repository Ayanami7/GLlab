add_library(QBCore STATIC
    common.h
    common.cpp
    shader.h
    shader.cpp
    scene.h
    scene.cpp
    model.h
    model.cpp
    pipeline.h
    pipeline.cpp
    renderer.h
    renderer.cpp
    camera.hpp
)

target_include_directories(QBCore PUBLIC
    ${CMAKE_SOURCE_DIR}/ext/glm
    ${CMAKE_SOURCE_DIR}/ext/stb
)

if (MSVC)
    target_compile_options(QBCore PUBLIC /utf-8)    # MSVC unicode support
endif()

add_dependencies(QBCore glad)
add_dependencies(QBCore glfw)
add_dependencies(QBCore stb)

target_link_libraries(QBCore PUBLIC glad)
target_link_libraries(QBCore PUBLIC glfw)
target_link_libraries(QBCore PUBLIC stb)
