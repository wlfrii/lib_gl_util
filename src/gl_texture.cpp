#include "../include/gl_util/gl_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GL_UTIL_BEGIN

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


unsigned char Texture2D::ID() const
{
    return _texture_id;
}


void Texture2D::release()
{
    _has_texture = false;
    glDeleteTextures(1, &_texture);
}


GL_UTIL_END