# gl_util

This folder is refactored to a tiny but quite useful utility library for OpenGL based rendering.

## Brief

The `gl_util` library will be very helpful to the practices in [<b>LearnOpenGL</b>](https://learnopengl-cn.github.io/).

This library include several usefull classes, including:
+ [`gl_util::Window`](https://github.com/wlfrii/learn_OpenGL/blob/main/gl_util/gl_util/gl_window.h). A class degsigned to manage GLFWwindow.
+ [`gl_util::VAVBEBO`](https://github.com/wlfrii/learn_OpenGL/blob/main/gl_util/gl_util/gl_vavbebo.h) A manager for VAO, VBO, and EBO.
+ [`gl_util::Shader`](https://github.com/wlfrii/learn_OpenGL/blob/main/gl_util/gl_util/gl_shader.h) A manager for shader program object.
+ [`gl_util::Texture2D`](https://github.com/wlfrii/learn_OpenGL/blob/main/gl_util/gl_util/gl_texture.h) A manager for the GL texture.

## Instructions

#### Configuration

 The required [GLAD](https://glad.dav1d.de/), [GLFW](https://www.glfw.org/download.html), and [GLM](https://glm.g-truc.net/0.9.9/index.html) libraries have been compiled with this library. Thus, furtherly application of this library could be pretty easy in your project, just by the following steps:

1. Downloading this folder to your project.
2. Make sure `glfw` is installed, which can be quickly completed by:
    ```bash
    sudo apt install libglfw3-dev
    ```
3. Add `gl_util` in your project as follows:
    ```cmake
    # Compile the library first
    add_subdirectory(gl_util)
    # Include the library header files
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/gl_util/include
    )
    # Link the library to your project 
    target_link_libraries(${PROJECT_NAME} PRIVATE gl_util)
    ```

PLEASE NOTE, the GLAD is device-dependent library for loading and managing the OpenGL. If any GLAD-related problem occur, you can solve that by obtaining new GLAD file in the [online service websit](https://glad.dav1d.de/).
> Instruction: (1) set the language to 'C/C++', (2) choose newer Version gl in API, (3) set profile to 'Core', (4) make 'Generate a loader' sure be selected, (5) press 'Generage'.
> Then two header file folders (glad and KHR) and one source file folder are provided, replacing the files in `./3rdparty/glad` by these new files, and then try to compile again.

More usage examples could by found in my [learn_OpenGL](https://github.com/wlfrii/learn_OpenGL) repository.

#### Usage

The `gl_util::Window` object should always be created first, since there is a strictly sequentially initialization procedure, specifically:
1. The context of OpenGL includes all the OpenGL status and resources. Before using any OpenGL function, a valid OpenGL context is required.
2. GLFW is account for creating OpenGL context. When `glfwCreateWindow()` is invoked, a window-related OpenGL context is created.
3. When a valid OpenGL context, GLFW created, exists, GLAD can load and manage OpenGL function pointers using the current valid OpenGL context. If no valid OpenGL context exist, GLAD cannot work with loading OpenGL function.