#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aCoord;

out vec2 ourCoord;

uniform mat4 projection;
uniform vec2 position;


//just testing
int z_layer = 1;

vec2 Scale = vec2(100, 100);



void main() {

    float FinalZLayer = -float(z_layer) * 0.01;
    vec2 FinalPosition = aPos * Scale + position; 

    gl_Position = projection * vec4(FinalPosition, FinalZLayer, 1);
    ourCoord = aCoord;
}