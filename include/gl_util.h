/** -------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
 *																		
 * @file 		gl_util.h 
 * 
 * @brief 		The header file include all the method in gl_util{}
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
 * --------------------------------------------------------------------
 * Change History:                        
 * 
 * 2022.4.30 Refactor the codes:
 * -------------------------------------------------------------------*/
#ifndef GL_UTILITY_H_LF
#define GL_UTILITY_H_LF
#include <iostream>

#include "gl_util/gl_window.h"
#include "gl_util/gl_shader.h"
#include "gl_util/gl_vavbebo.h"
#include "gl_util/gl_texture.h"
#include "gl_util/gl_camera.h"
#include "gl_util/gl_projection.h"

/* The other uitilities */
GL_UTIL_BEGIN

/**
 * @brief Print glm::mat to console.
 * 
 * @tparam T Typename
 * @tparam Q Qualifier
 * @tparam C Number of columns
 * @tparam R Number of rows
 * @param name The name of the matrix.
 * @param mat The data of the matrix.
 */
template <typename T, glm::qualifier Q, size_t C, size_t R>
void print(const char* name, const glm::mat<C, R, T, Q>& mat) {
    std::cout << name << "(" << C << "x" << R << "):\n[";
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < C; ++j) {
            std::cout << mat[i][j]; 
            if (i < R - 1 && j < C - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "]\n";
}

/**
 * @brief Print glm::vec to console.
 * 
 * @tparam T Typename
 * @tparam Q Qualifier
 * @tparam N Vector size
 * @param name The name of the vector.
 * @param vec The vector data.
 */
template <typename T, glm::qualifier Q, size_t N>
void print(const char* name, const glm::vec<N, T, Q>& vec) {
    std::cout << name << ": [";
    for (size_t i = 0; i < N; ++i) {
        std::cout << vec[i];
        if (i < N - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

GL_UTIL_END

#endif // GL_UTILITY_H_LF