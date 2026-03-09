#include <moderngl/program_mesh.hpp>




Program::Program(std::string vertex_src, std::string fragment_src){
    //VERTEX SHADER
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* src_v = vertex_src.c_str();
    glShaderSource(vertexShader, 1, &src_v, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
        throw std::runtime_error(std::string("[VERTEX SHADER ERROR]\n") + infoLog);
    }

    //FRAGMENT SHADER
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* src_f = fragment_src.c_str();
    glShaderSource(fragmentShader, 1, &src_f, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
        throw std::runtime_error(std::string("[FRAGMENT SHADER ERROR]\n") + infoLog);
    }

    //PROGRAM 
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        throw std::runtime_error(std::string("[SHADER LINK ERROR]\n") + infoLog);
    }
                
    //DELETE SHADERS
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Program::~Program(){
    if (program) glDeleteProgram(program);
}


void Program::useProgram(){
    glUseProgram(program);
}

//INT--------------------------------------
GLint Program::setInt(str name, int value){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform1i(Loc, value);
    return Loc;
}

GLint Program::setInt2(str name, int v_1, int v_2){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform2i(Loc, v_1, v_2);
    return Loc;
}

GLint Program::setInt3(str name, int v_1, int v_2, int v_3){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform3i(Loc, v_1, v_2, v_3);
    return Loc;
}

GLint Program::setInt4(str name, int v_1, int v_2, int v_3, int v_4){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform4i(Loc, v_1, v_2, v_3, v_4);
    return Loc;
}

//FLOAT----------------------------------------
GLint Program::setFloat(str name, float value){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform1f(Loc, value);
    return Loc;
}

GLint Program::setFloat2(str name, float v_1, float v_2){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform2f(Loc, v_1, v_2);
    return Loc;
}

GLint Program::setFloat3(str name, float v_1, float v_2, float v_3){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform3f(Loc, v_1, v_2, v_3);
    return Loc;
}

GLint Program::setFloat4(str name, float v_1, float v_2, float v_3, float v_4){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform4f(Loc, v_1, v_2, v_3, v_4);
    return Loc;
}

//VECTOR-------------------------------------
GLint Program::setVector2(str name, glm::vec2 vec2){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform2fv(Loc, 1, glm::value_ptr(vec2));
    return Loc;
}

GLint Program::setVector3(str name, glm::vec3 vec3){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform3fv(Loc, 1, glm::value_ptr(vec3));
    return Loc;
}

GLint Program::setVector4(str name, glm::vec4 vec4){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniform4fv(Loc, 1, glm::value_ptr(vec4));
    return Loc;
}

//MATRIX---------------------------------------
GLint Program::setMatrix2(str name, glm::mat2 mat2){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniformMatrix2fv(Loc, 1, GL_FALSE, glm::value_ptr(mat2));
    return Loc;
}

GLint Program::setMatrix3(str name, glm::mat3 mat3){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniformMatrix3fv(Loc, 1, GL_FALSE, glm::value_ptr(mat3));
    return Loc;
}

GLint Program::setMatrix4(str name, glm::mat4 mat4){
    GLint Loc = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(mat4));
    return Loc;
}



void genVao(GLuint& vao){
    glGenVertexArrays(1, &vao);
}

void genBuffer(GLuint& buffer){
    glGenBuffers(1, &buffer);
}

void genFbo(GLuint& fbo){
    glGenFramebuffers(1, &fbo);
}

void genRbo(GLuint& rbo){
    glGenRenderbuffers(1, &rbo);
}




void bindFbo(GLuint fbo){
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void bindVao(GLuint vao){
    glBindVertexArray(vao);
}  

void bindRbo(GLuint rbo, int width, int height){
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}


template<typename T>
void bindBuffer(GLenum type, GLuint buffer, const std::vector<T>& data){
    glBindBuffer(type, buffer);
    glBufferData(type, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
}

template void bindBuffer<float>(GLenum, GLuint, const std::vector<float>&);
template void bindBuffer<unsigned int>(GLenum, GLuint, const std::vector<unsigned int>&);
template void bindBuffer<glm::vec2>(GLenum, GLuint, const std::vector<glm::vec2>&);
template void bindBuffer<glm::vec3>(GLenum, GLuint, const std::vector<glm::vec3>&);



void setShader(int index, int size, int stride, int offset, bool divisor){
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(index);
    if (divisor) glVertexAttribDivisor(index, 1);
}

void render(GLuint vao, int index_count, GLenum mode){
    glBindVertexArray(vao);
    glDrawElements(mode, index_count, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void renderDivisor(GLuint vao, int index_count, int instance_count, GLenum mode){
    glBindVertexArray(vao);
    glDrawElementsInstanced(mode, index_count, GL_UNSIGNED_INT, nullptr, instance_count);
    glBindVertexArray(0);
}



void attachTexFbo(GLuint texture){
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
}

void activateTexture(GLuint texture, int slot){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void activateTextureArray(GLuint texture_array, int slot){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture_array);
}

void activateTextureCubeMap(GLuint texture_cubemap, int slot){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_cubemap);
}