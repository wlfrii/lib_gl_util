#include "../include/gl_util/gl_window.h"

GL_UTIL_BEGIN

/* ----------------------------------------------------------------------------------- */
/*                                    Window Utility                                   */
/* ----------------------------------------------------------------------------------- */

/**
 * @brief Shard window for shared context in multi-windows.
 */
static GLFWwindow* shared_window = nullptr;

/**
 * @brief GLFW error callback.
 * 
 * @param error The error code.
 * @param desc The error description.
 */
void errorCallback(int error, const char* desc) {
    GL_UTIL_PRINT("GLFW ERROR: %d, description: %s\n", error, desc);
}

void clear(uint8_t R, uint8_t G, uint8_t B, uint8_t A, bool is_depth_on) {
    // Clear and reset window color, this step is just a STATUS SETTING
    glClearColor(R/255.f, G/255.f, B/255.f, A/255.f);   
    // Clear previous color buffer and validate current color buffer
    glClear(GL_COLOR_BUFFER_BIT); 

    // Clear depth buffer if the Depth Test Enabled
    if(is_depth_on){
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}

uint8_t init(uint8_t ver_major, uint8_t ver_minor) {
    if(shared_window) {
        return 1;
    }

    // Add error callback before any GLFW operation.
    glfwSetErrorCallback(errorCallback);
    // Initialize GLFW.
    if(glfwInit() != GLFW_TRUE) {
        GL_UTIL_PRINT("GLFW ERROR: cannot initialize GLFW.\n");
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ver_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ver_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
#ifdef __APPLE__ 
    // The following command should be add in Mac OS platform to validate the 
    // commands above. 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Initialize shared window.
    // Create a hidden main window
    shared_window = glfwCreateWindow(1, 1, "main", nullptr, nullptr);
    glfwMakeContextCurrent(shared_window);
    glfwHideWindow(shared_window);
    glfwSetWindowPos(shared_window, 0, 0);

    // Only enable vsync for the main window to be swapped to
    // avoid waiting out the interval for each window
    glfwSwapInterval(1);

    /* Initialize GLAD to load all the OpenGL function pointers.
       GLAD is used to manage the pointers of OpenGL functions, so the intialization 
       for GLAD should be done before call any OpenGL interface. */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        GL_UTIL_PRINT("GLAD ERROR: failed to initialize GLAD.\n");
        std::exit(-1);
    }
    return 2;
}

void checkInitStatus() {
    if(shared_window) {
        return;
    }
    GL_UTIL_PRINT("ERROR, the GL context has not been initialized. "
        "Before using OpenGL, a valid OpenGL context should be created first, "
        "which could be simply completed by constructing a gl_util::Window object, "
        "or directly calling gl_util::init().\n");
    std::exit(EXIT_FAILURE);
}

/**
 * @brief GLFW whenever the window size changed (by OS or user resize) this 
 * callback function executes.
 * 
 * @param width Window width.
 * @param height Window height.
 */
inline void frameBufferSizeCallback(GLFWwindow*, int width, int height) {
    /* make sure the viewport matches the new window dimensions; note that
     width and height will be significantly larger than specified on retina 
     displays. */
    glViewport(0, 0, width, height);
}

/* ----------------------------------------------------------------------------------- */
/*                                 Window Implementation                               */
/* ----------------------------------------------------------------------------------- */

Window::Window(uint16_t width, uint16_t height, const std::string &name,
               bool is_window_visible)
    : width(width)
    , height(height)
    , name(name)
    , _is_depth_test_on(false) {

    // Initialize OpenGL context using default version.
    init();
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    /** Create GLFWwindo object **/
    if(!createGLFWwindow(is_window_visible)){
        exit(-1);
    }

    _color = {50, 75, 75, 255};
}

Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

GLFWwindow* Window::ptr() const {
    return _window;
}

void Window::activate() {
    // Activate current window
    glfwMakeContextCurrent(_window);

    // Monitoring kewboard event
    if(_callback_kbe){
        _callback_kbe(this->_window); 
    }
    else{
        processKeyboardEvent();
    }
}

void Window::deactivate() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glfwMakeContextCurrent(nullptr);
}

void Window::hidden() {
    glfwHideWindow(_window);
}

void Window::clear() {
    gl_util::clear(_color.R, _color.G, _color.B, _color.A, _is_depth_test_on);
}

void Window::refresh() {
    // Swap the double buffer
    glfwSwapBuffers(_window);

    // Check the keys pressed/released, mouse moved etc. events
    glfwPollEvents();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(_window);
}

void Window::enableDepthTest(size_t depth_cmp) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(depth_cmp);
    _is_depth_test_on = true;
}

void Window::disableDepthTest() {
    glDisable(GL_DEPTH_TEST);
    _is_depth_test_on = false;
}

void Window::setBackgroundColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
    _color = {R, G, B, A};
}

bool Window::setToFullScreen(uint8_t monitor_id) {
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
bool Window::createGLFWwindow(bool is_window_visible) {
    // This flag should be set before creating a glfwWindow.
    glfwWindowHint(GLFW_VISIBLE, is_window_visible);

    _window = glfwCreateWindow(width, height, name.c_str(), nullptr, shared_window);
    if(_window == nullptr){
        GL_UTIL_LOG("Failed to creat GLFW window.\n");
        glfwTerminate();
        return false;
    }

    // Activate current window
    glfwMakeContextCurrent(_window);
    
    // Set the framebuffer resize callback for this window, i.e. resize the 
    // buffer to viewport.
    glfwSetFramebufferSizeCallback(_window, frameBufferSizeCallback);
    
    return true;
}

void Window::processKeyboardEvent() {
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}

void Window::setKeyboardEventCallBack(CallbackKeyboardEvent callbackfunc) {
    _callback_kbe = callbackfunc;
}



GL_UTIL_END
