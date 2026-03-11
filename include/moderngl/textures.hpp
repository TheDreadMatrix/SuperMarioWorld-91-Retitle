#pragma once

#include <myheaders/stdport/stdport.hpp>
#include <glad/glad.h>
#include <stb_image.h>
#include <stb_truetype.h>


using list_str = const std::vector<std::string>&;
using list_float = const std::vector<float>&;
using list_bool = const std::vector<bool>&;



struct TextureFilter{
    GLint min_f, mag_f;
    bool use_mipmap;
};

struct ImageData{
    unsigned char* data;
    int width, height, channels;
};

struct DynamicText {
    GLuint texture = 0;
    int width = 0;
    int height = 0;
};


GLuint giveTexture(const std::string& image_path, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true, bool flip_x=false, bool flip_y=false, float angle=0.0f);


GLuint giveTextureFrame(int width, int height, int filter=NEAREST);


GLuint giveTextureArray(list_str images_path, list_bool flips_x, list_bool flips_y, list_float angles, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true);


GLuint giveTextureText(const std::string& font_path, const std::string& text, float pixel_size=48.0f, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true);



//CUBEMAP IN JULE
//GLuint giveTextureCubeMap();



