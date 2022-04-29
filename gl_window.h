/** -------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
 *																		
 * @file 		gl_window.h 
 * 
 * @brief 		A manager for the GLFWwindow object.
 * 
 * @author		Longfei Wang
 * 
 * @version		2.0.0
 * 
 * @date		2021/10/08
 * 
 * @license		
 * 
 * Copyright (C) 2021 Longfei Wang.
 * 
 * --------------------------------------------------------------------
 * Change History:                        
 * 
 * 2022.4.29 Add interface to enable/disable DepthTest, so that the 
 *   depth buffer will also be clear when the Window::clear() be called.
 * 2022.4.28 Refactor the codes:
 *   # Complete set to fullscreen interface;
 *   # Add set user defined keyboard event function interface;
 *   # Add interface for set background color;
 * 2021.10.9 Complete the doxygen comments.
 * -------------------------------------------------------------------*/
#ifndef GL_UTIL_WINDOW_H_LF
#define GL_UTIL_WINDOW_H_LF
/** NOTE, GLAD header file should be included before the GLFW header file, since
 * the correct OpenGL header files are included in GLAD */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>
#include <functional>
#include "gl_util_ns.h"

struct GLFWwindow;

GL_UTIL_BEGIN

typedef void (*CallbackKeyboardEvent)(GLFWwindow* window);

/**
 * @brief A windows class which help to manage GLFWwindow object.
 * The default GLFW version is 3 for MAJOR VERSION and 3 for MINOR VERSION.
 */
class Window
{
public:
    /**
     * @brief Construct a new Window object
     * 
     * @param width  The width of the window
     * @param height  The height of the window
     * @param ver_major The major version of glfw
     * @param ver_minor The minor version of glfw
     * @return  Window object
     */
    Window(uint16_t width, uint16_t height, uint8_t ver_major = 3, uint8_t ver_minor = 3);
    ~Window();

    
    /**
     * @brief Activate current window
     * . This is useful when there are more than one GL Window exist.
     */
    void activate();


    /**
     * @brief  Clear the window color and buffer
     */
    inline void clear();


    /**
     * @brief Swap buffers
     * . Note, OpenGL adopts double-buffers to store the rendered image to avoid
     * the display flickering that may occur in single buffer mode.
     */
    inline void refresh();


    /**
     * @brief Check the window close flag of current window
     * @return  
     *  - true, if the window should be closed
     *  - false. otherwise
     */
    inline bool shouldClose();


    /**
     * @brief Terminate GLFW library
     */
    inline void release();


    /**
     * @brief Enable depth test
     * . So that OpenGL while detemine which pixel should be showed and which 
     * pixel should be hiddened based on the Z-buffer.
     */
    inline void enableDepthTest();


    /**
     * @brief Disable depth test
     * . See also enableDepth();
     */
    inline void disableDepthTest();


    /**
     * @brief Set the background color of the window
     * 
     * @param R  The red value
     * @param G  The blue value
     * @param B  The green value
     * @param A  The alpha value
     */
    void setBackgroundColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255);


    /**
     * @brief Set current GLFWwindow to full screen object
     * 
     * @param monitor_id  The index of the monitor to display (when there are 
     * more than one monitor exist). O denotes the default monitor.
     * @return 
     *  - true, if set successfully
     *  - false, otherwise
     */
    bool setToFullScreen(uint8_t monitor_id = 0);

    
    /**
     * @brief Set the keyboard event call back
     * 
     * NOTE, the default keyboard event only consider the window close event 
     * that triggered by key 'Esc' event.
     * This function can facilate the user to define there keyboard event 
     * function rather than use the default function.
     */
    void setKeyboardEventCallBack(CallbackKeyboardEvent callbackfunc);

private:
    /* Create GLFW window */ 
    bool createGLFWwindow();
    /* Process keyboar event */
    void processKeyboardEvent();

private:
    GLFWwindow* _window;        //!< The object of GLFWwindow
    uint16_t    _win_width;     //!< The width of the window
    uint16_t    _win_height;    //!< The height of the window
    std::string _win_name;      //!< The name of the window

    struct{
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t A;
    }_color;                    //!< The background color of the window

    // The callback function for keyboard event
    std::function<void(GLFWwindow* window)> _callback_kbe;

    bool _is_depth_test_on;     //!< The flag for depth test
};

/* ------------------------------------------------------------------- */
/*                            Window Utility                           */
/* ------------------------------------------------------------------- */

/**
 * @brief GLAD load all the OpenGL function pointers
 * . GLAD is used to manage the pointers of OpenGL functions, so the 
 * intialization for GLAD should be done before call any OpenGL interface.
 * 
 * @return true if success, otherwise return false 
 * 
 * NOTE, the GLAD was initialized if any gl_util::Window was created.
 */
inline bool initGLAD()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        GL_LOG("Failed to initialize GLAD.\n");
        return false;
    }
    return true;
}


/**
 * @brief Clear the window color and buffer
 * . Same as the class function Window::clear().
 * NOTE, this function should be called before any glDraw operation. If the
 * function is called after glDraw operation, the buffer will be cleared.
 */
inline void clear(uint8_t R = 50, uint8_t G = 75, uint8_t B = 75, uint8_t A = 255, bool is_depth_on = false)
{
    // Clear and reset window color, this step is just a STATUS SETTING
    glClearColor(R/255.f, G/255.f, B/255.f, A/255.f);   
    // Clear previous color buffer and validate current color buffer
    glClear(GL_COLOR_BUFFER_BIT); 

    // Clear depth buffer if the Depth Test Enabled
    if(is_depth_on){
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}


/* ------------------------------------------------------------------- */
/*                     Window Inline Implementation                    */
/* ------------------------------------------------------------------- */

inline void Window::clear()
{
    gl_util::clear(_color.R, _color.G, _color.B, _color.A, _is_depth_test_on);
}


inline void Window::refresh()
{
    // Swap the double buffer
    glfwSwapBuffers(_window);

    // Check the keys pressed/released, mouse moved etc. events
    glfwPollEvents();
}


inline bool Window::shouldClose()
{
    return glfwWindowShouldClose(_window);
}


inline void Window::release()
{
    // Terminate GLFW library
    glfwTerminate();
}


inline void Window::enableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
    _is_depth_test_on = true;
}


inline void Window::disableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
    _is_depth_test_on = false;
}

GL_UTIL_END
#endif // GL_UTIL_WINDOW_H_LF
