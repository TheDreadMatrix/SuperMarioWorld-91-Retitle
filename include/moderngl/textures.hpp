#pragma once

#include <myheaders/stdport/stdport.hpp>
#include <glad/glad.h>
#include <stb_image.h>
#include <stb_truetype.h>


typedef std::vector<std::string> list_str;
typedef std::vector<bool> list_bool;
typedef std::vector<float> list_float;


struct TextureFilter{
    GLint min_f, mag_f;
    bool use_mipmap;
};

struct ImageData{
    unsigned char* data;
    int width, height, channels;
};

struct FontData{
    unsigned char* data;
    int width, height;
    int xoff, yoff;
};



GLuint giveTexture(std::string image_path, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true, bool flip_x=false, bool flip_y=false, float angle=0.0f);


GLuint giveTextureFrame(int width, int height, int filter=NEAREST);


GLuint giveTextureArray(list_str images_path, list_bool flips_x, list_bool flips_y, list_float angles, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true);


GLuint giveTextureText(std::string font_path, std::string text, float pixel_size=48.0f, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true);



//CUBEMAP IN JULE
//GLuint giveTextureCubeMap();



