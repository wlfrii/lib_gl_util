#ifndef LEARN_OPENGL_UTILITY_H_LF
#define LEARN_OPENGL_UTILITY_H_LF
/* NOTE, the GLAD header should be included before GLFW, since GLAD include 
the correct OpenGL header files. */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include "gll_shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace gll
{

/**
 * @brief GLAD load all the OpenGL function pointers
 * GLAD is used to manage the pointers of OpenGL functions, so the intialization
 * for GLAD should be done before call any OpenGL interface.
 * 
 * @return true if success, otherwise return false 
 */
inline bool initGLAD()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Failed to initialize GLAD.\n");
        return false;
    }
    return true;
}


/**
 * @brief GLFW whenever the window size changed (by OS or user resize) this 
 * callback function executes.
 * 
 * @param window 
 * @param width 
 * @param height 
 */
inline void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    /* make sure the viewport matches the new window dimensions; note that
     width and height will be significantly larger than specified on retina 
     displays. */
    glViewport(0, 0, width, height);
}


/**
 * @brief Initialize and configure GLFW
 * 
 * @param ver_major The major version of glfw
 * @param ver_minor The minor version of glfw
 */
inline void initGLFW(uint8_t ver_major = 3, uint8_t ver_minor = 3)
{
    glfwInit();
    // Configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
#ifdef __APPLE__ 
    /* The following command should be add in Mac OS platform to 
       validate the commands above. */ 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

/**
 * @brief 
 * 
 * @param window 
 * @param win_width 
 * @param win_height 
 * @param win_name 
 * @return true 
 * @return false 
 */
inline GLFWwindow* createGLFWwindow(uint16_t win_width = 800, uint16_t win_height = 600, bool is_fullscreen = false, std::string win_name = "LearnOpenGL")
{
    GLFWwindow* window = glfwCreateWindow(win_width, win_height, win_name.c_str(), nullptr, nullptr); 

    if(window == nullptr){ 
        printf("Failed to creat GLFW window.\n"); 
        glfwTerminate();  
    } 
    else {
        glfwMakeContextCurrent(window); 

        /* Set a callback function to tell GL update the view port
        when the size of the window is changed. */ 
        glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    }
    if(is_fullscreen){
        int monitor_count = 0;
        GLFWmonitor** monitor = is_fullscreen ? glfwGetMonitors(&monitor_count) : nullptr;
        printf("[%d] monitors have been found.\n", monitor_count);
        if(monitor_count >= 2){
            const GLFWvidmode* mode = glfwGetVideoMode(monitor[monitor_count-1]);
            glfwSetWindowMonitor(window, monitor[monitor_count-1], 0, 0, mode->width, mode->height, mode->refreshRate);
        }
    }

    return window; 
}


void render()
{
    // Clear and reset window color, this step is just a STATUS SETTING
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   
    // Clear previous color buffer and validate current color buffer
    glClear(GL_COLOR_BUFFER_BIT);           
}


/**
 * @brief 
 * 
 * @param window 
 */
inline void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
    

struct VAVBEBO
{
public:
    VAVBEBO() : _is_bind(false) {}

    void bind(float* vertices, size_t vertices_size, unsigned int* indices = nullptr, size_t indices_size = 0)
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

        if(indices){
            glGenBuffers(1, &_ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices_size, indices, GL_STATIC_DRAW);
        }
        _is_bind = true;
    }

    void bindVertexArray()
    {
        glBindVertexArray(_vao);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    void release()
    {
        if(_is_bind){
            glDeleteVertexArrays(1, &_vao);
            glDeleteBuffers(1, &_vbo);
            glDeleteBuffers(1, &_ebo);
            _is_bind = false;
        }
    }

private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    bool _is_bind;
};



/**
 * @brief Load and create a texture 
 * 
 * @param texture_path 
 * @return GLuint 
 */
inline bool create2DTexture(const std::string& texture_path, unsigned int& texture, GLint st_warp = GL_LINEAR, GLint min_filter = GL_LINEAR_MIPMAP_LINEAR, GLint mag_filter = GL_LINEAR)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, st_warp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, st_warp);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true); 
    
    // load image, create texture and generate mipmaps
    int width, height, channel;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &channel, 0);
    
    GLenum fmt = GL_RGB;
    if(channel == 4) fmt = GL_RGBA;

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture: %s\n", texture_path.c_str());
        return false;
    }
    stbi_image_free(data);

    return true;
}

}

#endif // LEARN_OPENGL_UTILITY_H_LF