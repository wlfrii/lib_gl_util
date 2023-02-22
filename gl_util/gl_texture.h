/** -------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
 *																		
 * @file 		gl_window.h 
 * 
 * @brief 		A manager for the GL texture.
 * 
 * @author		Longfei Wang
 * 
 * @version		2.0.0
 * 
 * @date		2021/10/09
 * 
 * @license		MIT
 * 
 * Copyright (C) 2021-Now Longfei Wang.
 * 
 * --------------------------------------------------------------------
 * Change History:                        
 * 
 * 2022.4.29 Refactor the codes.
 * * --------------------------------------------------------------------
 * References:
 * https://learnopengl-cn.github.io/01%20Getting%20started/06%20Textures/
 * -------------------------------------------------------------------*/
#ifndef GL_UTIL_TEXTURE_H_LF
#define GL_UTIL_TEXTURE_H_LF
#include <glad/glad.h>
#include "gl_util_ns.h"
#include <string>

GL_UTIL_BEGIN

/**
 * @brief A manager for GL 2D texture
 * 
 */
class Texture2D
{
public:
    /**
     * @brief Construct a new Texture2D object
     * 
     * @param texture_id  The texture unit. This class currently support  
     * 8 texture unit (with texture_id from 0-7) to facilate using, algthough 
     * OpenGL as least support 16 texture units(GL_TEXTURE0-GL_TEXTURE15). 
     */
    Texture2D(unsigned char texture_id = 0);
    ~Texture2D();


    /**
     * @brief Load an image as the texture
     * 
     * @param st_warp  Specify the wrapping mode in 's' and 't' dimension. GL
     * texture has 3 dimensions = [s,t,r]. The optional mode includes
     *  - GL_REPEAT
     *  - GL_MIRRORED_REPEAT
     *  - GL_CLAMP_TO_EDGE
     *  - GL_CLAMP_TO_BORDER
     * @param min_filter  Specify the filtering mode for minify
     * @param mag_filter  Specify the filtering mode for magnify
     * The optional filtering model includes
     *  - GL_LINEAR
     *  - GL_NEAREST
     *  - GL_NEAREST_MIPMAP_NEAREST
     *  - GL_LINEAR_MIPMAP_NEAREST
     *  - GL_NEAREST_MIPMAP_LINEAR
     *  - GL_LINEAR_MIPMAP_LINEAR
     */
    bool loadImage(const std::string& im_path, GLint st_warp = GL_LINEAR, GLint min_filter = GL_LINEAR_MIPMAP_LINEAR, GLint mag_filter = GL_LINEAR);


    /**
     * @brief Bind the texture refers to the texture index 
     */
    void bind();


    /**
     * @brief Get the texture index
     * 
     * @return Current texture index 
     */
    unsigned char ID() const;


    /**
     * @brief Delete current texture 
     */
    void release();

private:
    unsigned char   _texture_id;  //!< The index of current texture
    GLuint          _texture;     //!< The texture object created by GL
    bool            _has_texture; //!< The flag whether texture has been load
};


GL_UTIL_END
#endif // GL_UTIL_TEXTURE_H_LF