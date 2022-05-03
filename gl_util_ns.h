/** -------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
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
 * @license		
 * 
 * Copyright (C) 2021 Longfei Wang.
 * 
 * --------------------------------------------------------------------
 * Change History:                        
 * 
 * 2022.4.28 Add log to facilate debug.
 * -------------------------------------------------------------------*/
#ifndef GL_UTIL_NS_H_LF
#define GL_UTIL_NS_H_LF
#include <cstdio>

#define GL_UTIL_BEGIN namespace gl_util{
#define GL_UTIL_END }

#define GL_UTIL_LOG(fmt, ...) \
    printf("[%s][%s][%d] " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#endif // GL_WARPPER_NS_H_LF
