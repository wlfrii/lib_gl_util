#include "../include/gl_util/gl_shader.h"

GL_UTIL_BEGIN

Shader::Shader()
    : _has_created(false)
    , _id(0) {
}

Shader::~Shader() {
    release();
}


bool Shader::load(const std::string &vs_path, const std::string &fs_path) {
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
    _id = glCreateProgram();
    glAttachShader(_id, vertex_shader);
    glAttachShader(_id, fragment_shader);
    glLinkProgram(_id);
    checkShaderCompileErrors(_id, "PROGRAM");
    
    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    _has_created = true;
    return true;
}

void Shader::use() { 
    if(!isShaderValid()) return;
    glUseProgram(_id); 
}

void Shader::release() {
    if(_has_created) {
        glDeleteProgram(_id);
        _has_created = false;
    }
}

void Shader::setBool(const std::string &name, bool value) const {     
    if(!isShaderValid()) return;
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const { 
    if(!isShaderValid()) return;
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const { 
    if(!isShaderValid()) return;
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value); 
}

void Shader::setFloat3(const std::string &name, float x, float y, float z) const {
    if(!isShaderValid()) return;
    glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z); 
}

void Shader::setFloat4(const std::string &name, float x, float y, float z, float w) const {
    if(!isShaderValid()) return;
    glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w); 
}

void Shader::setVec3f(const std::string &name, const glm::vec3 &vec) const {
    if(!isShaderValid()) return;
    glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setVec3f(const std::string &name, float x, float y, float z) const {
    if(!isShaderValid()) return;

    glm::vec3 vec(x,y,z);
    glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setVec4f(const std::string &name, const glm::vec4 &vec) const {
    if(!isShaderValid()) return;
    glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setVec4f(const std::string &name, float x, float y, float z, float w) const {
    if(!isShaderValid()) return;

    glm::vec4 vec(x,y,z,w);
    glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setMat4f(const std::string &name, const glm::mat4 &mat) const {
    if(!isShaderValid()) return;
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

bool Shader::isShaderValid() const {
    if(_has_created) return true;
    
    GL_UTIL_LOG("ERROR: Shader object is not valid!\n");
    return false;
}

/* ----------------------------------------------------------------------------------- */
/*                                     Shader utility                                  */
/* ----------------------------------------------------------------------------------- */

void checkShaderCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[512];
    if (type != "PROGRAM") {
        // Check whether failed to compile shader
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            GL_UTIL_LOG("ERROR: Shader compilation error of type: %s\n\t%s\n", type.c_str(), infoLog);
        }
    }
    else {
        // Check whether failed to compile shader program
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            GL_UTIL_LOG("ERROR: Shader program linking error of type: %s\n\t%s\n", type.c_str(), infoLog);
        }
    }
}

GL_UTIL_END