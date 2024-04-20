Bezier曲面生成
==

##### 工程结构

```
GLlab2
    |--bin						//二进制文件
    	|--Debug				//默认工作目录
    	|--Release
    |--ext						//第三方库目录
    |--shader					//着色器文件
    |--src                      //源码
        |--common.h
        |--common.cpp
        |--loadShader.h
		...
        |--main.cpp
    .editorconfig				//格式配置文件
    CMakeLists.txt				//CMake文件
```
程序使用CMake构建，工程内包含全部的外部依赖  

对于CMake3.0以上版本和C++17支持的编译器，可以使用下列命令进行构建

```bash
cmake -S . -B build
cd build
cmake --build . --config Debug -j 8
```



##### 使用的第三方库

[glfw](https://github.com/glfw/glfw)  开源跨平台窗口库

[glad](https://github.com/Dav1dde/glad)  可用于OpenGL的函数加载库

[glm](https://github.com/icaven/glm)  基于 [GLSL规范](https://www.opengl.org/registry/doc/GLSLangSpec.4.50.diff.pdf)的 C++ Header-only数学库

[imgui](https://github.com/ocornut/imgui)  轻量C++界面库