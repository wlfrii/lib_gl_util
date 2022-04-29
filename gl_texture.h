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
 * @license		
 * 
 * Copyright (C) 2021 Longfei Wang.
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
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
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
    inline unsigned char ID() const;


    /**
     * @brief Delete current texture 
     */
    inline void release();

private:
    unsigned char   _texture_id;  //!< The index of current texture
    GLuint          _texture;     //!< The texture object created by GL
    bool            _has_texture; //!< The flag whether texture has been load
};


/* ------------------------------------------------------------------- */
/*                       Texture2D Implementation                      */
/* ------------------------------------------------------------------- */

Texture2D::Texture2D(unsigned char texture_id)
    : _texture_id(texture_id)
    , _has_texture(false)
{
}


Texture2D::~Texture2D()
{
}


bool Texture2D::loadImage(const std::string& texture_path, GLint st_warp, GLint min_filter, GLint mag_filter)
{
    if(_has_texture){
        GL_UTIL_LOG("WARNING: Current shader program object will be replaced!\n");
        release();
    }

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, st_warp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, st_warp);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true); 
    
    // load image, create texture and generate mipmaps
    int width, height, channel;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &channel, 0);
    
    GLenum fmt = GL_RGB;
    if(channel == 4) fmt = GL_RGBA;

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        GL_UTIL_LOG("Failed to load texture: %s\n", texture_path.c_str());
        return false;
    }
    stbi_image_free(data);

    _has_texture = true;
    return true;
}


void Texture2D::bind()
{
    switch (_texture_id)
    {
    case 0:  glActiveTexture(GL_TEXTURE0);  break;
    case 1:  glActiveTexture(GL_TEXTURE1);  break;
    case 2:  glActiveTexture(GL_TEXTURE2);  break;
    case 3:  glActiveTexture(GL_TEXTURE3);  break;
    case 4:  glActiveTexture(GL_TEXTURE4);  break;
    case 5:  glActiveTexture(GL_TEXTURE5);  break;
    case 6:  glActiveTexture(GL_TEXTURE6);  break;
    case 7:  glActiveTexture(GL_TEXTURE7);  break;
    case 8:  glActiveTexture(GL_TEXTURE8);  break;
    default:
        GL_UTIL_LOG("Current version only support 8 texture.\n");
        return;
    }
    glBindTexture(GL_TEXTURE_2D, _texture);
}


inline unsigned char Texture2D::ID() const
{
    return _texture_id;
}


inline void Texture2D::release()
{
    _has_texture = false;
    glDeleteTextures(1, &_texture);
}

GL_UTIL_END
#endif // GL_UTIL_TEXTURE_H_LF