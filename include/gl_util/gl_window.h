/** -------------------------------------------------------------------------------------
 *																		
 *   				                 OpenGL Utilities 					
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
 * @license		MIT
 * 
 * Copyright (C) 2021-Now Longfei Wang.
 * 
 * --------------------------------------------------------------------------------------
 * Change History:                        
 * 
 * 2022.4.29 Add interface to enable/disable DepthTest, so that the 
 *   depth buffer will also be clear when the Window::clear() be called.
 * 2022.4.28 Refactor the codes:
 *   # Complete set to fullscreen interface;
 *   # Add set user defined keyboard event function interface;
 *   # Add interface for set background color;
 * 2021.10.9 Complete the doxygen comments.
 * ------------------------------------------------------------------------------------*/
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

typedef std::function<void(GLFWwindow* window)> CallbackKeyboardEvent;

/**
 * @brief A windows class which help to manage GLFWwindow object.
 */
class Window {
public:
    /**
     * @brief Construct a new Window object.
     * 
     * @details When constructing the Window object, GLAD will be initialized.
     * 
     * @param width  The width of the window.
     * @param height  The height of the window.
     * @param name  Name of the window.
     * @param is_transparent  Flag for creating transparent/opaque window.
     * @return  Window object.
     */
    Window(uint16_t width, uint16_t height, const std::string &name,
           bool is_transparent = false);

    /**
     * @brief Destroy the Window object.
     * 
     * @details When calling the destructor, the glfwTerminate will be invoked.
     */
    ~Window();

    /**
     * @brief Get the manged GLFWwindow object.
     * 
     * @return The managed GLFWwindow object.
     */
    GLFWwindow* ptr() const;
    
    /**
     * @brief Activate current window.
     * 
     * @remark This is useful when there are more than one window exist.
     * 
     * @note If gl_util::Window::clear() is invoked, the calling of this function can be 
     * omitted.
     * 
     * @see gl_util::Window::clear(), gl_util::Window::deactivate().
     */
    void activate();

    /**
     * @brief Deactivate current window.
     * 
     * @note This function is generally no need to invoke. When calling 
     * gl_util::Window::activate(), current window will become the valid context, the
     * context at previous moment will be invalid.
     * 
     * @see gl_util::Window::activate().
     */
    void deactivate();

    /**
     * @brief Hidden current window.
     * 
     * @see gl_util::Window::show().
     */
    void hidden();

    /**
     * @brief Show current window.
     * 
     * @see gl_util::Window::show().
     */
    void show();

    /**
     * @brief Clear the window color and buffer.
     * 
     * @note Calling this function will make current window as current context, even
     * through the context at the previous moment is not the current window.
     *
     * @see gl_util::clear().
     */
    void clear();

    /**
     * @brief Swap buffers.
     * 
     * @note OpenGL adopts double-buffers to store the rendered image to avoid the 
     * display flickering that may occur in single buffer mode. Calling this function 
     * will invoke glfwSwapBuffers in activated window.
     */
    void refresh();

    /**
     * @brief Check the window close flag of current window.
     * @return  
     *   @retval true  If the window should be closed
     *   @retval false Otherwise
     */
    bool shouldClose();

    /**
     * @brief Enable depth test.
     * 
     * @remark So that OpenGL while detemine which pixel should be showed and which 
     * pixel should be hiddened based on the Z-buffer.
     * 
     * @param[in] depth_cmp The method to compare deptht, the optional setting are:
     *  - GL_ALWAYS
     *  - GL_NEVER
     *  - GL_LESS
     *  - GL_EQUAL
     *  - GL_LEQUAL
     *  - GL_GREATER
     *  - GL_NOTEQUAL
     *  - GL_GEQUAL
     * 
     * @see also gl_util::Window::disableDepthTest();
     */
    void enableDepthTest(size_t depth_cmp = GL_LEQUAL);

    /**
     * @brief Disable depth test
     * 
     * @see also gl_util::Window::enableDepthTest();
     */
    void disableDepthTest();

    /**
     * @brief Set the background color of the window.
     * 
     * @param[in] R  The red value.
     * @param[in] G  The blue value.
     * @param[in] B  The green value.
     * @param[in] A  The alpha value.
     */
    void setBackgroundColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255);

    /**
     * @brief Set current GLFWwindow to full screen object.
     * 
     * @param[in] monitor_id  The index of the monitor to display (when there are 
     * more than one monitor exist). O denotes the default monitor.
     * @return 
     *   @retval true  If set successfully.
     *   @retval false Otherwise.
     */
    bool setToFullScreen(uint8_t monitor_id = 0);
    
    /**
     * @brief Set the keyboard event call back
     * 
     * @note The default keyboard event only consider the window close event 
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

public:
    const uint16_t    width;     ///< The width of the window
    const uint16_t    height;    ///< The height of the window
    const std::string name;      ///< The name of the window

private:
    GLFWwindow* _window;         ///< The object of GLFWwindow

    struct{
        float R;                 ///< Ranged in [0, 1]
        float G;                 ///< Ranged in [0, 1]
        float B;                 ///< Ranged in [0, 1]
        float A;                 ///< Ranged in [0, 1]
    }_color;                     ///< The background color of the window

    bool _is_depth_test_on;      ///< The flag for depth test

    // The callback function for keyboard event
    CallbackKeyboardEvent    _callback_kbe;
};

/* ----------------------------------------------------------------------------------- */
/*                                    Window Utility                                   */
/* ----------------------------------------------------------------------------------- */


GL_UTIL_END
#endif // GL_UTIL_WINDOW_H_LF
