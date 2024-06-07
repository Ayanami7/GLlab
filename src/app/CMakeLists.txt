add_executable(QBApp
    main.cpp
    widget.h
    widget.cpp
    renderer.h
    renderer.cpp
    resourceManager.h
    resourceManager.cpp
)

target_include_directories(QBApp PUBLIC
    ${IMGUI_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_dependencies(QBApp QBCore)
add_dependencies(QBApp imgui)

if (MSVC)
    target_compile_options(QBApp PUBLIC /utf-8)    # MSVC unicode support
endif()



target_link_libraries(QBApp PUBLIC QBCore)
target_link_libraries(QBApp PUBLIC imgui)