#pragma once

#include <myheaders/stdport/stdport.hpp>



using list_str = const std::vector<std::string>&;
using list_float = const std::vector<float>&;
using list_bool = const std::vector<bool>&;
using list_bytes = const std::vector<unsigned char*>&;



struct TextureFilter{
    GLint min_f, mag_f;
    bool use_mipmap;
};

struct ImageData{
    unsigned char* data;
    int width, height, channels;
};



ImageData loadImage(const std::string& image_path);



GLuint giveTexture(const std::string& image_path, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true, bool flip_x=false, bool flip_y=false, float angle=0.0f);


GLuint giveTextureFrame(int width, int height, int filter=NEAREST);


GLuint giveTextureArray(list_str images_path, list_bool flips_x, list_bool flips_y, list_float angles, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true);


GLuint giveTextureFromBytes(unsigned char* data, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true, bool flip_x=false, bool flip_y=false, float angle=0.0f);

GLuint giveTextureArrayFromBytes(list_bytes datas, list_bool flips_x, list_bool flips_y, list_float angles, int filter=NEAREST, bool repeat_x=true, bool repeat_y=true);





