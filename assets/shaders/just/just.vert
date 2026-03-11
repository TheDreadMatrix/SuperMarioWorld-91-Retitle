#version 330

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aCoord;


uniform mat4 projection;
uniform vec2 position;
uniform vec2 scale;


out vec2 fCoord;

void main(){


    gl_Position = projection * vec4(aPos * scale + position, 0.0, 1.0);
    fCoord = aCoord;

}
