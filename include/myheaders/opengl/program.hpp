#pragma once

#include <myheaders/imports.hpp>



class Program{
    public:
        GLuint program;
        GLint success;
        char infoLog[1024];

        Program(std::string vertex_src, std::string fragment_src){
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

            //CREATE FRAGMENT SHADER
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

            //CREATE PROGRAM 
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

        ~Program(){
            if (program) glDeleteProgram(program);
        }

        void useProgram(){
            glUseProgram(program);
        }


        void setInt(std::string name, int value){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform1i(Loc, value);
        }

        void setInt2(std::string name, int v_1, int v_2){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform2i(Loc, v_1, v_2);
        }

        void setInt3(std::string name, int v_1, int v_2, int v_3){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform3i(Loc, v_1, v_2, v_3);
        }

        void setInt4(std::string name, int v_1, int v_2, int v_3, int v_4){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform4i(Loc, v_1, v_2, v_3, v_4);
        }


        void setFloat(std::string name, float value){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform1f(Loc, value);
        }

        void setFloat2(std::string name, float v_1, float v_2){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform2f(Loc, v_1, v_2);
        }

        void setFloat3(std::string name, float v_1, float v_2, float v_3){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform3f(Loc, v_1, v_2, v_3);
        }

        void setFloat4(std::string name, float v_1, float v_2, float v_3, float v_4){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform4f(Loc, v_1, v_2, v_3, v_4);
        }


        void setVector2(std::string name, glm::vec2 vec2){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform2fv(Loc, 1, glm::value_ptr(vec2));
        }

        void setVector3(std::string name, glm::vec3 vec3){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform3fv(Loc, 1, glm::value_ptr(vec3));
        }
        void setVector4(std::string name, glm::vec4 vec4){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniform4fv(Loc, 1, glm::value_ptr(vec4));
        }

        void setMatrix2(std::string name, glm::mat2 mat2){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniformMatrix2fv(Loc, 1, GL_FALSE, glm::value_ptr(mat2));
        }

        void setMatrix3(std::string name, glm::mat3 mat3){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniformMatrix3fv(Loc, 1, GL_FALSE, glm::value_ptr(mat3));
        }

        void setMatrix4(std::string name, glm::mat4 mat4){
            GLint Loc = glGetUniformLocation(program, name.c_str());
            glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(mat4));
        }


};