/** -------------------------------------------------------------------------------------
 *																		
 *   				                 OpenGL Utilities 					
 *																		
 * @file 		gl_util_ns.h 
 * 
 * @brief 		The global definition for gl_util{}
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
 * 2022.4.28 Add log to facilate debug.
 * ------------------------------------------------------------------------------------*/
#ifndef GL_UTIL_NS_H_LF
#define GL_UTIL_NS_H_LF
#include <cstdio>

#define GL_UTIL_BEGIN namespace gl_util{
#define GL_UTIL_END }

#define GL_UTIL_LOG(fmt, ...) \
    printf("[%s][%s][%d] " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define GL_UTIL_ERROR(fmt, ...) \
    fprintf(stderr, fmt, ##__VA_ARGS__)

struct GLFWwindow;
GL_UTIL_BEGIN
/**
 * @brief Initialization of gl_util.
 * 
 * @param ver_major The major version of OpenGL context that created by GLFW..
 * @param ver_minor The minor version of OpenGL context that created by GLFW..
 * 
 * @return bool
 *   @retval 2 The gl_util is just be initialized successfully. 
 *   @retval 1 The gl_util has been initialized.
 *   @retval 0 Failed to init gl_util, the app will auto-exit. 
 */
uint8_t init(uint8_t ver_major = 4, uint8_t ver_minor = 5);

/**
 * @brief Calling glfwTerminate() to destroy all remaining windows and context, while
 * restoring any modified gamma ramps and frees any other allocated resources.
 * 
 * @note Once this function is called, you must again call gl_util::init() successfully 
 * before you will be able to use most GLFW functions. If GLFW has been successfully 
 * initialized, this function should be called before the application exits. If 
 * initialization fails, there is no need to call this function.
 */
void terminate();

/**
 * @brief Check gl_util initialization status.
 * 
 * @note Using gl_util without properly initialization may cause core dump error. This 
 * function is used for avoiding that problems, by printing prompt and safe exit.
 */
void checkInitStatus();

/**
 * @brief Clear the window color and buffer.
 * Generally, there is no need to call this function, the renderring buffer within a
 * window will be clear after calling gl_util::Window::clear.
 * 
 * @note This function should be called before any glDraw operation. If the
 * function is called after glDraw operation, the buffer will be cleared.
 * 
 * @remark This is a overrided function, provided for convinience.
 * 
 * @param window The window to be cleared.
 * @param R The red value.
 * @param G The green value.
 * @param B The blue value.
 * @param A The alpha value.
 * @param is_depth_on The flag for clearing depth buffer.
 */
void clear(GLFWwindow* window, float R = 0.f, float G = 0.f, float B = 0.f, 
           float A = 0.f, bool is_depth_on = false);

/**
 * @brief Clear the window color and buffer.
 * Generally, there is no need to call this function, the renderring buffer within a
 * window will be clear after calling gl_util::Window::clear.
 * 
 * @note This function should be called before any glDraw operation. If the
 * function is called after glDraw operation, the buffer will be cleared.
 * 
 * @remark This is a overrided function, provided for convinience.
 * 
 * @param window The window to be cleared.
 * @param R The red value.
 * @param G The green value.
 * @param B The blue value.
 * @param A The alpha value.
 * @param is_depth_on The flag for clearing depth buffer.
 */
void clear(GLFWwindow* window, uint8_t R = 0, uint8_t G = 0, uint8_t B = 0, 
           float A = 0, bool is_depth_on = false);

GL_UTIL_END
#endif // GL_WARPPER_NS_H_LF
