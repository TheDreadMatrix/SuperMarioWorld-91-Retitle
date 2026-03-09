#pragma once


#include <myheaders/imports.hpp>

typedef std::string str;

class Program{
    public:
        GLuint program;
        GLint success;
        char infoLog[1024];

        Program(std::string vertex_src, std::string fragment_src);
        ~Program();

        void useProgram();

        GLint setInt(str name, int value);
        GLint setInt2(str name, int v_1, int v_2);
        GLint setInt3(str name, int v_1, int v_2, int v_3);
        GLint setInt4(str name, int v_1, int v_2, int v_3, int v_4);

        GLint setFloat(str name, float value);
        GLint setFloat2(str name, float v_1, float v_2);
        GLint setFloat3(str name, float v_1, float v_2, float v_3);
        GLint setFloat4(str name, float v_1, float v_2, float v_3, float v_4);

        GLint setVector2(str name, glm::vec2 vec2);
        GLint setVector3(str name, glm::vec3 vec3);
        GLint setVector4(str name, glm::vec4 vec4);

        GLint setMatrix2(str name, glm::mat2 mat2);
        GLint setMatrix3(str name, glm::mat3 mat3);
        GLint setMatrix4(str name, glm::mat4 mat4);

};



void genVao(GLuint& vao);
void genFbo(GLuint& fbo);
void genRbo(GLuint& rbo);
void genBuffer(GLuint& buffer);

void bindVao(GLuint vao);
void bindFbo(GLuint fbo);
void bindRbo(GLuint rbo);
void bindVbo(GLuint vbo, std::vector<float>& vertices);
void bindEbo(GLuint ebo, std::vector<unsigned int>& indices);

void setShader(int index, int size, int stride, int offset, bool divisor=false);
void render(GLuint vao, int index_count, GLenum mode=GL_TRIANGLES);
void renderDivisor(GLuint vao, int index_count, int instance_count, GLenum mode=GL_TRIANGLES);


void activateTexture(GLuint texture, int slot=0);
void activateTextureArray(GLuint texture_array, int slot=0);
void activateTextureCubeMap(GLuint texture_cubemap, int slot=0);