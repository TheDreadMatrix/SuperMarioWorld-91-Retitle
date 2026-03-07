#pragma once

#include <myheaders/imports.hpp>



void genVao(GLuint& vao){
    glGenVertexArrays(1, &vao);
}

void genBuffer(GLuint& buffer){
    glGenBuffers(1, &buffer);
}


void bindVao(GLuint vao){
    glBindVertexArray(vao);
}

void bindVbo(GLuint vbo, std::vector<float>& vertices){
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void bindEbo(GLuint ebo, std::vector<unsigned int>& indices){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void setShaderAttribute(int index, int component_size, int vertex_count, int start_at){
    glVertexAttribPointer(index, component_size, GL_FLOAT, GL_FALSE, vertex_count * sizeof(float), (void*)(start_at * sizeof(float)));
    glEnableVertexAttribArray(index);
}

void setShaderDivisor(){

}


void Render(GLuint& vao, int index_count, GLenum mode = GL_TRIANGLES){
    glBindVertexArray(vao);
    glDrawElements(mode, index_count, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}