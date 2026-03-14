#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aCoord;
layout(location = 2) in vec2 aiSpriteOffsets;
layout(location = 3) in vec2 aiOffsets;

out vec2 fCoord;

uniform mat4 projection;
uniform vec2 position;
uniform vec2 scale;
uniform int z_layer;

uniform vec2 sprite_size;


void main() {

    float FinalZLayer = -float(z_layer) * 0.01;
    vec2 FinalPosition = aPos * scale + position + aiOffsets; 

    gl_Position = projection * vec4(FinalPosition, FinalZLayer, 1);
    fCoord = aCoord * sprite_size + aiSpriteOffsets;
}