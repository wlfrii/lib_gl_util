/** -------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
 *																		
 * @file 		gl_shader.h 
 * 
 * @brief 		A manager for shader program object
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
 *   # Optimize the codes. The load() interface can be called once user
 * want to change the vertex and fragment shader files. The valid flag
 * of the Shader Program Object will be checked before any calling related
 * to Shader Program Object, ensuring safe call of interfaces.
 * -------------------------------------------------------------------*/
#ifndef GL_UTIL_SHADER_H_LF
#define GL_UTIL_SHADER_H_LF
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "gl_util_ns.h"

GL_UTIL_BEGIN

/**
 * @brief A manager for shader program object * 
 */
class Shader
{
public:
    Shader();
    ~Shader();

    /**
     * @brief Load vertex shader file and frament shader file
     * 
     * @param vs_path  The path of vertex shader file
     * @param fs_path  The path of fragment shader file
     * @return 
     *  - true, succeed to load the two files 
     *  - false, otherwise
     * 
     * This function can be called once you want to change the vertex and 
     * fragment shader files.
     */
    bool load(const std::string &vs_path, const std::string &fs_path);


    /**
     * @brief Activate current shader program object before rendering
     */
    inline void use();


    /**
     * @brief Delete current shader program object 
     */
    inline void release();


    /**
     * @brief Set the 'bool' object to Shader (GLSL)
     * 
     * @param name  The name of 'bool' object in GLSL
     * @param value  The value to be set
     */
    inline void setBool(const std::string &name, bool value) const;
   

    /**
     * @brief Set the 'int' object to Shader (GLSL)
     * 
     * @param name  The name of 'int' object in GLSL
     * @param value  The value to be set
     */
    inline void setInt(const std::string &name, int value) const;
    

    /**
     * @brief Set the 'float' object to Shader (GLSL)
     * 
     * @param name  The name of 'float' object in GLSL
     * @param value  The value to be set
     */
    inline void setFloat(const std::string &name, float value) const;


    /**
     * @brief Set the 3 float object to Shader (GLSL)
     * .See also setVec3()
     * 
     * @param name  The name of object in GLSL
     * @param x  The value to be set
     * @param y  The value to be set
     * @param z  The value to be set
     */
    inline void setFloat3(const std::string &name, float x, float y, float z) const;


    /**
     * @brief Set the 4 float object to Shader (GLSL)
     * .See also setVec4()
     * 
     * @param name  The name of object in GLSL
     * @param x  The value to be set
     * @param y  The value to be set
     * @param z  The value to be set
     * @param w  The value to be set
     */
    inline void setFloat4(const std::string &name, float x, float y, float z, float w) const;


    /**
     * @brief Set the 'vec3f' object to Shader (GLSL)
     * .The common 'vec3f' includes the position, the color, et al.
     * 
     * @param name  The name of 'vec3f' object in GLSL
     * @param value  The value to be set
     */
    inline void setVec3f(const std::string &name, const glm::vec3 &vec) const;


    /**
     * @brief Override: Set the 3 float object to Shader (GLSL)
     * .See also setFloat3(), setVec3()
     */
    inline void setVec3f(const std::string &name, float x, float y, float z) const;


    /**
     * @brief Set the 'vec4f' object to Shader (GLSL)
     * The common 'vec4f' includes the position, the color, et al.
     * 
     * @param name  The name of 'vec4f' object in GLSL
     * @param value  The value to be set
     */
    inline void setVec4f(const std::string &name, const glm::vec4 &vec) const;


    /**
     * @brief Override: Set the 4 float object to Shader (GLSL)
     * .See also setFloat4(), setVec4()
     */
    inline void setVec4f(const std::string &name, float x, float y, float z, float w) const;


    /**
     * @brief Set the 'mat4f' object to Shader (GLSL)
     * The common 'mat4f' includes the transform like model, view, projection 
     * matrix.
     * 
     * @param name  The name of 'mat4f' object in GLSL
     * @param value  The value to be set
     */
    inline void setMat4f(const std::string &name, const glm::mat4 &mat) const;


private:
    /**
     * @brief  Check whether shader files are successfully read
     * 
     * @return 
     *  - true, succeed to read shader files
     *  - false, otherwise
     */
    inline bool isShaderValid() const;


    /**
     * @brief The Shader Program Object.
     * To use the vertex shader and fragment shader, the two shaders should be
     * linked to the shader program object, and the shader program object will
     * be activated when render any object.
     */
    unsigned int _ID;

    // Whether the shader program object is created successfully
    bool _has_created; 
};

/* ------------------------------------------------------------------- */
/*                             Shader utility                          */
/* ------------------------------------------------------------------- */

/**
 * @brief Check if there is any error when compile shader
 * 
 * @param shader  The vertex shader, fragment shader or shader program object
 * @param type  Specify the shader type
 */
inline void checkShaderCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[512];
    if (type != "PROGRAM")
    {
        // Check whether failed to compile shader
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            GL_UTIL_LOG("ERROR: Shader compilation error of type: %s\n\t%s\n", type.c_str(), infoLog);
        }
    }
    else
    {
        // Check whether failed to compile shader program
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            GL_UTIL_LOG("ERROR: Shader program linking error of type: %s\n\t%s\n", type.c_str(), infoLog);
        }
    }
}


/* ------------------------------------------------------------------- */
/*                         Shader implementation                       */
/* ------------------------------------------------------------------- */

Shader::Shader()
    : _has_created(false)
    , _ID(0)
{
}

Shader::~Shader()
{
    release();
}


bool Shader::load(const std::string &vs_path, const std::string &fs_path)
{
    if(_has_created){
        GL_UTIL_LOG("WARNING: Current shader program object will be replaced!\n");
        release();
    }

    /** 1. Retrieve the vertex/fragment source code from filePath **/
    std::string vertex_code, fragment_code;
    std::ifstream vs_file, fs_file;
    // Ensure ifstream objects can throw exceptions:
    vs_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fs_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // Open files
        vs_file.open(vs_path);
        fs_file.open(fs_path);
        std::stringstream vs_stream, fs_stream;
        // Read file's buffer contents into streams
        vs_stream << vs_file.rdbuf();
        fs_stream << fs_file.rdbuf();
        // Close file handlers
        vs_file.close();
        fs_file.close();
        // Convert stream into string
        vertex_code   = vs_stream.str();
        fragment_code = fs_stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        GL_UTIL_LOG("ERROR: Files are not successfully read\n");
        return _has_created;
    }
    const char* vs_code = vertex_code.c_str();
    const char* fs_code = fragment_code.c_str();
    
    /** 2. Compile shaders **/
    unsigned int vertex_shader, fragment_shader;
    // Create vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vs_code, NULL);
    glCompileShader(vertex_shader);
    checkShaderCompileErrors(vertex_shader, "VERTEX");
    // Create fragment Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fs_code, NULL);
    glCompileShader(fragment_shader);
    checkShaderCompileErrors(fragment_shader, "FRAGMENT");
    // Create shader Program and link the vertex and fragment shader to it
    _ID = glCreateProgram();
    glAttachShader(_ID, vertex_shader);
    glAttachShader(_ID, fragment_shader);
    glLinkProgram(_ID);
    checkShaderCompileErrors(_ID, "PROGRAM");
    
    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    _has_created = true;
    return true;
}


inline void Shader::use() 
{ 
    if(!isShaderValid()) return;
    glUseProgram(_ID); 
}


inline void Shader::release()
{
    glDeleteProgram(_ID);
    _has_created = false;
}


inline void Shader::setBool(const std::string &name, bool value) const
{     
    if(!isShaderValid()) return;
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value); 
}


inline void Shader::setInt(const std::string &name, int value) const
{ 
    if(!isShaderValid()) return;
    glUniform1i(glGetUniformLocation(_ID, name.c_str()), value); 
}


inline void Shader::setFloat(const std::string &name, float value) const
{ 
    if(!isShaderValid()) return;
    glUniform1f(glGetUniformLocation(_ID, name.c_str()), value); 
}


inline void Shader::setFloat3(const std::string &name, float x, float y, float z) const
{
    if(!isShaderValid()) return;
    glUniform3f(glGetUniformLocation(_ID, name.c_str()), x, y, z); 
}


inline void Shader::setFloat4(const std::string &name, float x, float y, float z, float w) const
{
    if(!isShaderValid()) return;
    glUniform4f(glGetUniformLocation(_ID, name.c_str()), x, y, z, w); 
}


inline void Shader::setVec3f(const std::string &name, const glm::vec3 &vec) const
{
    if(!isShaderValid()) return;
    glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, glm::value_ptr(vec));
}


inline void Shader::setVec3f(const std::string &name, float x, float y, float z) const
{
    if(!isShaderValid()) return;

    glm::vec3 vec(x,y,z);
    glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, glm::value_ptr(vec));
}

inline void Shader::setVec4f(const std::string &name, const glm::vec4 &vec) const
{
    if(!isShaderValid()) return;
    glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, glm::value_ptr(vec));
}


inline void Shader::setVec4f(const std::string &name, float x, float y, float z, float w) const
{
    if(!isShaderValid()) return;

    glm::vec4 vec(x,y,z,w);
    glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, glm::value_ptr(vec));
}


inline void Shader::setMat4f(const std::string &name, const glm::mat4 &mat) const
{
    if(!isShaderValid()) return;
    glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}


inline bool Shader::isShaderValid() const
{
    if(_has_created) return true;
    
    GL_UTIL_LOG("ERROR: Shader object is not valid!\n");
    return false;
}


GL_UTIL_END
#endif // GL_UTIL_SHADER_H_LF