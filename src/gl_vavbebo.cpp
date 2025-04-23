#include "../include/gl_util/gl_vavbebo.h"

GL_UTIL_BEGIN

VAVBEBO::VAVBEBO() 
    : _is_bind(false) {
}

VAVBEBO::~VAVBEBO() { 
    if(_is_bind){
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
        _is_bind = false;
    }
}

void VAVBEBO::bind(const float* vertices, size_t vertices_size, 
                   const std::vector<uint8_t>& vertex_desc, const unsigned int* indices, 
                   size_t indices_size, size_t gl_draw_mode) {
    if(!_is_bind) {
        glGenVertexArrays(1, &_vao);
    }
    glBindVertexArray(_vao);
    
    // Generate VBO
    if(!_is_bind) {
        glGenBuffers(1, &_vbo);
    }
    /* Bind the GL_ARRAY_BUFFER to VBO, after which, any calling of the 
       GL_ARRAY_BUFFER will configure current binded VBO. */
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // Copy the input vertices into our GL_ARRAY_BUFFER.
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, gl_draw_mode);

    if(indices){
        if(!_is_bind) {
            glGenBuffers(1, &_ebo);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
    }
    _is_bind = true;

    /* Now, explain the input vertices to OpenGL.
       Calculte the stride of vertices. */
    unsigned int vertex_stride = 0;
    for(const auto val : vertex_desc) {
        vertex_stride += val;
    }
    vertex_stride *= sizeof(float);
    // Explain each element of a vertex and enable the corresponding vertex property.
    unsigned int offset = 0;
    for(int i = 0; i < vertex_desc.size(); i++) {
        uint8_t esize = vertex_desc[i];
        glVertexAttribPointer(i, esize, GL_FLOAT, GL_FALSE, vertex_stride, 
                             (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += esize;
    }
}

void VAVBEBO::bindVertexArray() {
    if(!_is_bind){
        GL_UTIL_LOG("ERROR: No valid vertices are binded to VAVBEBO object!\n");
        return;
    }  
    glBindVertexArray(_vao);
}

void VAVBEBO::unBindVertexArray() {
    glBindVertexArray(0);
}

GL_UTIL_END