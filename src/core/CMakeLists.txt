add_library(QBCore STATIC
    common.h
    exception.h
    shader.h
    shader.cpp
    scene.h
    scene.cpp
    model.h
    model.cpp
    pipeline.h
    pipeline.cpp
    material.h
    material.cpp
    camera.hpp
)

add_dependencies(QBCore glad)
add_dependencies(QBCore glfw)
add_dependencies(QBCore stb)

target_include_directories(QBCore PUBLIC
    ${CMAKE_SOURCE_DIR}/ext/glm
    ${CMAKE_SOURCE_DIR}/ext/stb
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if (MSVC)
    target_compile_options(QBCore PUBLIC /utf-8)    # MSVC unicode support
endif()

target_link_libraries(QBCore PUBLIC glad)
target_link_libraries(QBCore PUBLIC glfw)
target_link_libraries(QBCore PUBLIC stb)
