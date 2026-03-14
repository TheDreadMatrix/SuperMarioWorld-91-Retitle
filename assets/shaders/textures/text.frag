#version 330 core
out vec4 FragColor;
in vec2 fCoord;

const vec3 color_ignore = vec3(255, 128, 255) / vec3(255, 255, 255);
const vec3 color_change = vec3(0.9, 0, 0.8);

uniform sampler2D tex;
uniform float fade_amp;

bool defineColor(vec3 color_obj, vec3 color_reference){
    return all(greaterThanEqual(color_obj, color_reference));
}


void main() {
    vec4 Color = texture(tex, fCoord);

    if (defineColor(Color.rgb, color_ignore))
        discard;

    if (defineColor(Color.rgb, color_change))
        Color.rgb = color_change;

    FragColor = Color * vec4(0, 0, 0, fade_amp);
}