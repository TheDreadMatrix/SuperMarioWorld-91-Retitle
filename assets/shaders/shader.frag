#version 330 core
out vec4 FragColor;
in vec2 ourCoord;

uniform vec3 rgb;
uniform int slot;
uniform sampler2DArray tex;

void main() {
    FragColor = vec4(rgb, 1.0) * texture(tex, vec3(ourCoord, slot));
}