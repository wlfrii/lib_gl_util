#include "gl_window.h"

namespace {

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

}


GL_UTIL_BEGIN


Window::Window(uint16_t width, uint16_t height, uint8_t ver_major, uint8_t ver_minor)
    : _win_width(width)
    , _win_height(height)
    , _win_name("Displayer")
{
    /** Initialize GLFW **/
    glfwInit();
    // Configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ver_major); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ver_minor); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
#ifdef __APPLE__ 
    // The following command should be add in Mac OS platform to validate the 
    // commands above. 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /** Create GLFWwindo object **/
    if(!createGLFWwindow()){
        exit(-1);
    }

    /** Initialize GLAD **/
    // GLAD is used to manage the pointers of OpenGL functions and the right 
    // header files are included in GLAD, so the intialization for GLAD should 
    // be done before call any OpenGL interface.
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        GL_LOG("Failed to initialize GLAD.\n");
        exit(-1);
    }

    _color = {0.2, 0.3, 0.3, 1.0};
}


Window::~Window()
{
    glfwTerminate();
}


void Window::activate()
{
    // Activate current window
    glfwMakeContextCurrent(_window);

    // Make current window visiable
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

    // Monitoring kewboard event
    if(_callback_kbe){
        _callback_kbe(this->_window);
    }
    else{
        processKeyboardEvent();
    }
}


void Window::refresh()
{
    // Swap the double buffer
    glfwSwapBuffers(_window);

    // Check the mouse/keyboard events
    glfwPollEvents();
}


bool Window::shouldClose()
{
    return glfwWindowShouldClose(_window);
}


void Window::release()
{
    // Terminate GLFW library
    glfwTerminate();
}


void Window::setBackgroundColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    _color.R = R / 255.f;
    _color.G = G / 255.f;
    _color.B = B / 255.f;
    _color.A = A / 255.f;
}


bool Window::setToFullScreen(uint8_t monitor_id)
{
    bool ret = false;
    if(_window)
    {
        // Read the number of the available monitor
        int monitor_count = 0;
        GLFWmonitor** monitor = glfwGetMonitors(&monitor_count);
        printf("[%d] monitors have been found.\n", monitor_count);
        if(monitor_id > monitor_count){
            printf("The specified monitor index out of valid range.\n");
            return ret;
        }

        // Set monitor to display window
        const GLFWvidmode* mode = glfwGetVideoMode(monitor[monitor_id]);
        glfwSetWindowMonitor(_window, monitor[monitor_id], 0, 0,
                mode->width, mode->height, mode->refreshRate);
    
    }
    return ret;
}


// --- PRIVATE ---
bool Window::createGLFWwindow()
{
    _window = glfwCreateWindow(_win_width, _win_height, _win_name.c_str(), nullptr, nullptr);
    if(_window == nullptr){
        GL_LOG("Failed to creat GLFW window.\n");
        glfwTerminate();
        return false;
    }

    // Activate current window
    glfwMakeContextCurrent(_window);
    
    // Set the framebuffer resize callback for this window, i.e. resize the 
    // buffer to viewport.
    glfwSetFramebufferSizeCallback(_window, ::frameBufferSizeCallback);
    
    // Hidden current window since there is nothing to show now.
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    return true;
}

void Window::processKeyboardEvent()
{
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}


void Window::setKeyboardEventCallBack(CallbackKeyboardEvent callbackfunc)
{
    _callback_kbe = callbackfunc;
}

GL_UTIL_END
