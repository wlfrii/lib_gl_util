/** -------------------------------------------------------------------------------------
 *																		
 *   				        OpenGL Utilities 					
 *																		
 * @file 		gl_shader.h 
 * 
 * @brief 		A manager for shader program object
 * 
 * @author		Longfei Wang
 * 
 * @version		2.0.1
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
 * 2022.4.29 V2.0.0. Refactor the codes:
 *   # Complete the doxygen comments;
 *   # Optimize the codes. The load() interface can be called once user want to change the
 * vertex and fragment shader files. The valid flag of the Shader Program Object will be 
 * checked before any calling related to Shader Program Object, ensuring safe call of 
 * interfaces.
 * -------------------------------------------------------------------------------------*/
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
class Shader {
public:
    /**
     * @brief Construct a new Shader object.
     */
    Shader();

    /**
     * @brief Destroy the Shader object.
     */
    ~Shader();

    /**
     * @brief Load vertex shader file and frament shader file.
     * 
     * @param vs_path  The path of vertex shader file
     * @param fs_path  The path of fragment shader file
     * @return 
     *   @retval true  Succeed to load the two files.
     *   @retval false Otherwise.
     * 
     * @note This function can be called once you want to change the vertex and 
     * fragment shader files.
     */
    bool load(const std::string &vs_path, const std::string &fs_path);

    /**
     * @brief Activate current shader program object before rendering.
     */
    void use();

    /**
     * @brief Delete current shader program object.
     */
    void release();

    /**
     * @brief Set the 'bool' object to Shader (GLSL).
     * 
     * @param name  The name of 'bool' object in GLSL.
     * @param value  The value to be set.
     */
    void setBool(const std::string &name, bool value) const;
   
    /**
     * @brief Set the 'int' object to Shader (GLSL).
     * 
     * @param name  The name of 'int' object in GLSL.
     * @param value  The value to be set.
     */
    void setInt(const std::string &name, int value) const;
    
    /**
     * @brief Set the 'float' object to Shader (GLSL).
     * 
     * @param name  The name of 'float' object in GLSL.
     * @param value  The value to be set.
     */
    void setFloat(const std::string &name, float value) const;

    /**
     * @brief Set 3 float objects to Shader (GLSL).
     * 
     * @param name  The name of 'float3' object in GLSL.
     * @param x  The value to be set.
     * @param y  The value to be set.
     * @param z  The value to be set.
     * 
     * @sa also gl_util::Shader::setVec3().
     */
    void setFloat3(const std::string &name, float x, float y, float z) const;

    /**
     * @brief Set 4 float objects to Shader (GLSL).
     * 
     * @param name  The name of 'float4' object in GLSL.
     * @param x  The value to be set.
     * @param y  The value to be set.
     * @param z  The value to be set.
     * @param w  The value to be set.
     * 
     * @sa also gl_util::Shader::setVec4().
     */
    void setFloat4(const std::string &name, float x, float y, float z, float w) const;

    /**
     * @brief Set the 'vec3f' object to Shader (GLSL).
     * 
     * @remark This is an overloaded function, provided for convenience. 
     * 
     * @param name  The name of 'vec3f' object in GLSL.
     * @param value  The value to be set.
     * 
     * @sa also gl_util::Shader::setFloat3().
     */
    void setVec3f(const std::string &name, const glm::vec3 &vec) const;

    /**
     * @brief Set 3 float objects to Shader (GLSL).
     * 
     * @remark This is an overloaded function, provided for convenience. 
     * 
     * @param name  The name of 'vec3f' object in GLSL.
     * @param x  The value to be set.
     * @param y  The value to be set.
     * @param z  The value to be set.
     * 
     * @sa also gl_util::Shader::setFloat3().
     */
    void setVec3f(const std::string &name, float x, float y, float z) const;

    /**
     * @brief Set the 'vec4f' object to Shader (GLSL).
     * 
     * @remark This is an overloaded function, provided for convenience. 
     * 
     * @param name  The name of 'vec4f' object in GLSL.
     * @param value  The value to be set.
     * 
     * @sa also gl_util::Shader::setFloat4().
     */
    void setVec4f(const std::string &name, const glm::vec4 &vec) const;

    /**
     * @brief Set the 4 float objects to Shader (GLSL).
     * 
     * @remark This is an overloaded function, provided for convenience. 
     * 
     * @param name  The name of 'vec4f' object in GLSL.
     * @param x  The value to be set.
     * @param y  The value to be set.
     * @param z  The value to be set.
     * @param w  The value to be set.
     * 
     * @sa also gl_util::Shader::setFloat4().
     */
    void setVec4f(const std::string &name, float x, float y, float z, float w) const;

    /**
     * @brief Set the 'mat4f' object to Shader (GLSL).
     * 
     * @details The common 'mat4f' includes the transform like model, view, projection 
     * matrix.
     * 
     * @param name  The name of 'mat4f' object in GLSL.
     * @param value  The value to be set.
     */
    void setMat4f(const std::string &name, const glm::mat4 &mat) const;

private:
    /**
     * @brief  Check whether shader files are successfully read.
     * 
     * @return 
     *   @retval true  Succeed to read shader files.
     *   @retval false Otherwise.
     */
    bool isShaderValid() const;

    /**
     * @brief The Shader Program Object.
     * To use the vertex shader and fragment shader, the two shaders should be linked to
     * the shader program object, and the shader program object will be activated when
     * render any object.
     */
    unsigned int _id;

    bool _has_created; ///< Whether the shader program object is created successfully.
};

/* ----------------------------------------------------------------------------------- */
/*                                     Shader utility                                  */
/* ----------------------------------------------------------------------------------- */

/**
 * @brief Check if there is any error when compile shader.
 * 
 * @param shader  The vertex shader, fragment shader or shader program object.
 * @param type  Specify the shader type, PROGRAM, VERTEX, or FRAGMENT.
 */
void checkShaderCompileErrors(unsigned int shader, std::string type);

GL_UTIL_END
#endif // GL_UTIL_SHADER_H_LF