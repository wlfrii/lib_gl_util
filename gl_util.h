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
 * @license		
 * 
 * Copyright (C) 2021 Longfei Wang.
 * 
 * --------------------------------------------------------------------
 * Change History:                        
 * 
 * 2022.4.30 Refactor the codes:
 * -------------------------------------------------------------------*/
#ifndef GL_UTILITY_H_LF
#define GL_UTILITY_H_LF

#include "gl_window.h"
#include "gl_shader.h"
#include "gl_vavbebo.h"
#include "gl_texture.h"
#include "gl_camera.h"

#include "gl_projection.h"

/* The other uitilities */
GL_UTIL_BEGIN

inline void print(const char* name, const glm::mat4& mat){
    printf("%s:\n", name);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("%f,", mat[i][j]);
        }
        printf("\n");
    }
}

inline void print(const char* name, const glm::vec3& vec)
{
    printf("%s, [%f,%f,%f] ", name, vec.x, vec.y, vec.z);
};

GL_UTIL_END

#endif // GL_UTILITY_H_LF