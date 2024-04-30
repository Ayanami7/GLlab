基于OpenGL的简易渲染器
==

#### 开始

##### 需要的配置  

- CMake 3.0 以上版本
- C++ 17 支持的编译器

程序内集成第三方依赖库，不需要额外下载依赖  

##### 经过测试的编译器  

- [x] MinGW-W64 8.1.0

- [x] MSVC-2022-amd64

##### 构建

对于满足要求的工具链，可以在主目录下使用以下命令进行构建  

```bash
cmake -S . -B build 
cd build
cmake --build . --config Debug -j 8
```
#### 工程结构

```
GLlab2
    |--bin
    	|--Debug
    	|--Release
    |--ext
    |--shader
    |--src
        |--common.h
        |--common.cpp
        |--loadShader.h
		...
        |--main.cpp
    .editorconfig
    CMakeLists.txt
```

默认工作目录位于`/bin/Debug`目录下


#### 使用的第三方库

[glfw](https://github.com/glfw/glfw)  开源跨平台窗口库

[glad](https://github.com/Dav1dde/glad)  可用于OpenGL的函数加载库

[glm](https://github.com/icaven/glm)  基于 [GLSL规范](https://www.opengl.org/registry/doc/GLSLangSpec.4.50.diff.pdf)的 C++ Header-only数学库

[imgui](https://github.com/ocornut/imgui)  轻量C++界面库

[stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)  单头文件图片加载库

[tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)  单头文件obj加载库