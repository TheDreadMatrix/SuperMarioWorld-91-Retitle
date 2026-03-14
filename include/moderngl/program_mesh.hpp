#pragma once

#include <myheaders/stdport/stdport.hpp>


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


