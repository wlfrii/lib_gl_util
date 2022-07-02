#include "gl_vavbebo.h"

GL_UTIL_BEGIN

VAVBEBO::VAVBEBO() 
    : _is_bind(false) 
{
}


VAVBEBO::~VAVBEBO() 
{ 
    release(); 
}


void VAVBEBO::bind(float* vertices, size_t vertices_size, unsigned int* indices, size_t indices_size, size_t gl_draw_mode)
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


void VAVBEBO::bindVertexArray()
{
    if(!_is_bind){
        GL_UTIL_LOG("ERROR: No valid vertices are binded to VAVBEBO object!\n");
        return;
    }  
    glBindVertexArray(_vao);
}


void VAVBEBO::unBindVertexArray()
{
    glBindVertexArray(0);
}


void VAVBEBO::release()
{
    if(_is_bind){
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        _is_bind = false;
    }
}

GL_UTIL_END