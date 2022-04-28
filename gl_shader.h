#ifndef LEARN_OPENGL_SHADER_H_LF
#define LEARN_OPENGL_SHADER_H_LF
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <glm/glm.hpp>

namespace gll{

/**
 * @brief 
 * 
 * @param shader 
 * @param type 
 */
inline void checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[512];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n\t%s\n",
                type.c_str(), infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n\t%s\n",
                type.c_str(), infoLog);
        }
    }
}


class Shader
{
public:
    Shader() {}

    void load(const char* vs_path, const char* fs_path)
    {
        /* 1. retrieve the vertex/fragment source code from filePath */
        std::string vertex_code, fragment_code;
        std::ifstream vs_file, fs_file;
        // ensure ifstream objects can throw exceptions:
        vs_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fs_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vs_file.open(vs_path);
            fs_file.open(fs_path);
            std::stringstream vs_stream, fs_stream;
            // read file's buffer contents into streams
            vs_stream << vs_file.rdbuf();
            fs_stream << fs_file.rdbuf();
            // close file handlers
            vs_file.close();
            fs_file.close();
            // convert stream into string
            vertex_code   = vs_stream.str();
            fragment_code = fs_stream.str();
        }
        catch (std::ifstream::failure& e)
        {
            printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
        }
        const char* vs_code = vertex_code.c_str();
        const char* fs_code = fragment_code.c_str();
        
        /* 2. compile shaders */
        unsigned int vertex_shader, fragment_shader;
        // vertex shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vs_code, NULL);
        glCompileShader(vertex_shader);
        gll::checkCompileErrors(vertex_shader, "VERTEX");
        // fragment Shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fs_code, NULL);
        glCompileShader(fragment_shader);
        gll::checkCompileErrors(fragment_shader, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex_shader);
        glAttachShader(ID, fragment_shader);
        glLinkProgram(ID);
        gll::checkCompileErrors(ID, "PROGRAM");
        
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    // activate the shader
    void use() 
    { 
        glUseProgram(ID); 
    }

    // utility uniform functions
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
   
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void setMat4f(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setVec3f(const std::string &name, const glm::vec3 &vec) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
    }

    void release()
    {
        glDeleteProgram(ID);
    }

    unsigned int ID;
};

}
#endif // LEARN_OPENGL_SHADER_H_LF