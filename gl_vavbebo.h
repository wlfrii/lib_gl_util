/** -------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
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
 * @license		
 * 
 * Copyright (C) 2021 Longfei Wang.
 * 
 * --------------------------------------------------------------------
 * Change History:                        
 * 
 * 2022.4.29 Refactor the codes:
 *   # Complete the doxygen comments;
 * -------------------------------------------------------------------*/
#ifndef GL_UTIL_VAVBEBO_H_LF
#define GL_UTIL_VAVBEBO_H_LF
#include <glad/glad.h>
#include "gl_util_ns.h"

GL_UTIL_BEGIN

class VAVBEBO
{
public:
    VAVBEBO();
    ~VAVBEBO();

    /**
     * @brief  Bind vertices to current object.
     * 
     * @param vertices  The array of vertices
     * @param vertices_size  The size of vertices
     * @param indices   The array of indices of tri-face
     * @param indices_size  The size of indices
     * @param gl_draw_mode  The mode we want the GPU to manage the vertex data
     *  - GL_STATIC_DRAW  The data will (almost) never be changed
     *  - GL_DYNAMIC_DRAW  The data will be changed
     *  - GL_STREAM_DRAW  The data will be changed in every render-loop
     */
    inline void bind(float* vertices, size_t vertices_size, unsigned int* indices = nullptr, size_t indices_size = 0, size_t gl_draw_mode = GL_STATIC_DRAW);


    /**
     * @brief  Call OpenGL to bind current VAO to render based on the binded 
     * buffer in VBO
     */
    inline void bindVertexArray();


    /**
     * @brief Call OpenGL to un bind current VAO ofter rendering.
     * (Optionally, there is no need to unbind in every render-loop)
     */
    inline void unBindVertexArray();


    /**
     * @brief De-allocate all resources once they've outlived their purpose
     * This operation is optionally.
     */
    inline void release();


private:
    GLuint _vao;        //!< Vertex Array Object
    GLuint _vbo;        //!< Vertex Buffer Object
    GLuint _ebo;        //!< Element Buffer Object
    bool _is_bind;      //!< Flag to whether bind vertices data
};


/* ------------------------------------------------------------------- */
/*                        VAVBEBO implementation                       */
/* ------------------------------------------------------------------- */

VAVBEBO::VAVBEBO() 
    : _is_bind(false) 
{
}


VAVBEBO::~VAVBEBO() 
{ 
    release(); 
}


inline void VAVBEBO::bind(float* vertices, size_t vertices_size, unsigned int* indices, size_t indices_size, size_t gl_draw_mode)
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    // Generate VBO
    glGenBuffers(1, &_vbo);
    // Bind the GL_ARRAY_BUFFER to VBO, after which, any calling of the 
    // GL_ARRAY_BUFFER will configure current binded VBO
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // Copy the input vertices into our GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, gl_draw_mode);

    if(indices){
        glGenBuffers(1, &_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
    }
    _is_bind = true;
}


inline void VAVBEBO::bindVertexArray()
{
    if(!_is_bind){
        GL_LOG("ERROR: No valid vertices are binded to VAVBEBO object!\n");
        return;
    }  
    glBindVertexArray(_vao);
}


inline void VAVBEBO::unBindVertexArray()
{
    glBindVertexArray(0);
}


inline void VAVBEBO::release()
{
    if(_is_bind){
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        _is_bind = false;
    }
}


GL_UTIL_END
#endif // GL_UTIL_VAVBEBO_H_LF