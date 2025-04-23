/** -------------------------------------------------------------------------------------
 *																		
 *   				                 OpenGL Utilities 					
 *																		
 * @file 		gl_vavbebo.h 
 * 
 * @brief 		A manager for VAO, VBO, and EBO.
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
 * 2022.4.29 Refactor the codes:
 *   # Complete the doxygen comments;
 * ------------------------------------------------------------------------------------*/
#ifndef GL_UTIL_VAVBEBO_H_LF
#define GL_UTIL_VAVBEBO_H_LF
#include <glad/glad.h>
#include <cstddef>
#include "gl_util_ns.h"

GL_UTIL_BEGIN

class VAVBEBO {
public:
    /**
     * @brief Construct a new VAVBEBO object.
     */
    VAVBEBO();

    /**
     * @brief Destroy the VAVBEBO object.
     */
    ~VAVBEBO();

    /**
     * @brief  Bind vertices to current object.
     * 
     * @param vertices  The array of vertices.
     * @param vertices_size  The size of vertices.
     * @param indices   The array of indices of tri-face.
     * @param indices_size  The size of indices
     * @param gl_draw_mode  The mode we want the GPU to manage the vertex data.
     *  - GL_STATIC_DRAW  The data will (almost) never be changed.
     *  - GL_DYNAMIC_DRAW  The data will be changed.
     *  - GL_STREAM_DRAW  The data will be changed in every render-loop.
     */
    void bind(float* vertices, size_t vertices_size, unsigned int* indices = nullptr, 
              size_t indices_size = 0, size_t gl_draw_mode = GL_STATIC_DRAW);

    /**
     * @brief  Call OpenGL to bind current VAO to render based on the binded 
     * buffer in VBO
     */
    void bindVertexArray();

    /**
     * @brief Call OpenGL to un bind current VAO ofter rendering.
     * (Optionally, there is no need to unbind in every render-loop)
     */
    void unBindVertexArray();

    /**
     * @brief De-allocate all resources once they've outlived their purpose
     * This operation is optionally.
     */
    void release();

private:
    GLuint _vao;        //!< Vertex Array Object
    GLuint _vbo;        //!< Vertex Buffer Object
    GLuint _ebo;        //!< Element Buffer Object
    bool _is_bind;      //!< Flag to whether bind vertices data
};

GL_UTIL_END
#endif // GL_UTIL_VAVBEBO_H_LF