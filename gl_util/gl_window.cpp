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
    : width(width)
    , height(height)
    , name("Displayer")
    , _is_depth_test_on(false)
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
    if(!initGLAD()){
        exit(-1);
    }

    _color = {50, 75, 75, 255};
}


Window::~Window()
{
    glfwTerminate();
}


GLFWwindow* Window::ptr() const
{
    return _window;
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


void Window::hidden()
{
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
}


void Window::clear()
{
    gl_util::clear(_color.R, _color.G, _color.B, _color.A, _is_depth_test_on);
}


void Window::refresh()
{
    // Swap the double buffer
    glfwSwapBuffers(_window);

    // Check the keys pressed/released, mouse moved etc. events
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


void Window::enableDepthTest(size_t depth_cmp)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(depth_cmp);
    _is_depth_test_on = true;
}


void Window::disableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
    _is_depth_test_on = false;
}


void Window::setBackgroundColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    _color = {R, G, B, A};
}


bool Window::setToFullScreen(uint8_t monitor_id)
{
    bool ret = false;
    if(_window)
    {
        // Read the number of the available monitor
        int monitor_count = 0;
        GLFWmonitor** monitor = glfwGetMonitors(&monitor_count);
        printf("gl_util::Window: [%d] monitors have been found.\n", monitor_count);
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
    _window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if(_window == nullptr){
        GL_UTIL_LOG("Failed to creat GLFW window.\n");
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
