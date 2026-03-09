#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aCoord;
layout(location = 2) in vec2 aOffsets;

out vec2 ourCoord;

uniform mat4 projection;
uniform vec2 position;
uniform vec2 scale;


//just testing
int z_layer = 1;


void main() {

    float FinalZLayer = -float(z_layer) * 0.01;
    vec2 FinalPosition = aPos * scale + position + aOffsets; 

    gl_Position = projection * vec4(FinalPosition, FinalZLayer, 1);
    ourCoord = aCoord;
}