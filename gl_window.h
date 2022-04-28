/**--------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
 *																		
 * Description:													
 *   A class for managing GLFWwindow.
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
#include "gl_module_ns.h"

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
     * @brief Activate current window.
     * This is useful when there are more than one GL Window exist.
     */
    void activate();


    /**
     * @brief Swap buffers
     * Note, OpenGL adopts double-buffers to store the rendered image to avoid
     * the display flickering that may occur in single buffer mode.
     */
    void refresh();


    /**
     * @brief Check the window close flag of current window
     * @return  
     *  - true, if the window should be closed
     *  - false. otherwise
     */
    bool shouldClose();


    /**
     * @brief Terminate GLFW library
     */
    void release();


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
        float R;
        float G;
        float B;
        float A;
    }_color;                    //!< The background color of the window

    // The callback function for keyboard event
    std::function<void(GLFWwindow* window)> _callback_kbe;
};

GL_UTIL_END
#endif // GL_UTIL_WINDOW_H_LF
