#include <moderngl/textures.hpp>

void flipX(unsigned char* data, int width, int height, int channels) {
    for (int y = 0; y < height; y++) {
        unsigned char* line = data + y * width * channels;
        for (int x = 0; x < width / 2; x++) {
            for (int c = 0; c < channels; c++) {
                std::swap(line[x * channels + c], line[(width - 1 - x) * channels + c]);
            }
        }
    }
}

void flipY(unsigned char* data, int width, int height, int channels) {
    int rowBytes = width * channels;
    unsigned char* tempRow = new unsigned char[rowBytes];

    for (int y = 0; y < height / 2; y++) {
        unsigned char* rowTop = data + y * rowBytes;
        unsigned char* rowBottom = data + (height - 1 - y) * rowBytes;

        std::memcpy(tempRow, rowTop, rowBytes);
        std::memcpy(rowTop, rowBottom, rowBytes);
        std::memcpy(rowBottom, tempRow, rowBytes);
    }

    delete[] tempRow;
}

void rotateArbitrary(unsigned char* data, int width, int height, int channels, float angleDegrees) {
    float angleRad = angleDegrees * 3.14159265358979323846f / 180.0f;
    float cosA = cosf(angleRad);
    float sinA = sinf(angleRad);

    int cx = width / 2;
    int cy = height / 2;

    unsigned char* temp = new unsigned char[width * height * channels];
    std::memset(temp, 0, width * height * channels); 

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float fx = cosA * (x - cx) + sinA * (y - cy) + cx;
            float fy = -sinA * (x - cx) + cosA * (y - cy) + cy;

            int ix = (int)fx;
            int iy = (int)fy;
            float dx = fx - ix;
            float dy = fy - iy;

            if (ix >= 0 && ix < width - 1 && iy >= 0 && iy < height - 1) {
                for (int c = 0; c < channels; c++) {
                    unsigned char a = data[(iy * width + ix) * channels + c];
                    unsigned char b = data[(iy * width + (ix + 1)) * channels + c];
                    unsigned char d = data[((iy + 1) * width + ix) * channels + c];
                    unsigned char e = data[((iy + 1) * width + (ix + 1)) * channels + c];

                    float value = a * (1 - dx) * (1 - dy) +
                                  b * dx * (1 - dy) +
                                  d * (1 - dx) * dy +
                                  e * dx * dy;

                    temp[(y * width + x) * channels + c] = (unsigned char)(std::round(value));
                }
            }
        }
    }

    std::memcpy(data, temp, width * height * channels);
    delete[] temp;
}




TextureFilter defineFilter(int filter){
    TextureFilter Texfilter;
    switch (filter) {
        case 1: Texfilter.min_f = GL_NEAREST; Texfilter.mag_f = GL_NEAREST; Texfilter.use_mipmap = false; break;
        case 2: Texfilter.min_f = GL_LINEAR; Texfilter.mag_f = GL_LINEAR; Texfilter.use_mipmap = false; break;
        case 3: Texfilter.min_f = GL_NEAREST_MIPMAP_NEAREST; Texfilter.mag_f = GL_NEAREST; Texfilter.use_mipmap = true; break;
        case 4: Texfilter.min_f = GL_LINEAR_MIPMAP_NEAREST; Texfilter.mag_f = GL_LINEAR; Texfilter.use_mipmap = true; break;
        case 5: Texfilter.min_f = GL_LINEAR_MIPMAP_LINEAR; Texfilter.mag_f = GL_LINEAR; Texfilter.use_mipmap = true; break;
        case 6: Texfilter.min_f = GL_NEAREST_MIPMAP_LINEAR; Texfilter.mag_f = GL_NEAREST; Texfilter.use_mipmap = true; break;
        default: Texfilter.min_f = GL_NEAREST; Texfilter.mag_f = GL_NEAREST; Texfilter.use_mipmap = false; break;
    }
    return Texfilter;
}

ImageData loadImage(std::string image_path){
    ImageData img;
    img.data = stbi_load(image_path.c_str(), &img.width, &img.height, &img.channels, STBI_rgb_alpha);
    if (!img.data) {
        throw std::runtime_error("Failed to load image: " + image_path);
    }

    return img;
}





GLuint giveTextureFrame(int width, int height, int filter){
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    TextureFilter TexFilter = defineFilter(filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexFilter.min_f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TexFilter.mag_f);
    if (TexFilter.use_mipmap) glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}



GLuint giveTexture(std::string image_path, int filter, bool repeat_x, bool repeat_y, bool flip_x, bool flip_y, float angle){
    ImageData img = loadImage(image_path);
    if (flip_x) flipX(img.data, img.width, img.height, 4);
    if (flip_y) flipY(img.data, img.width, img.height, 4);
    if (angle != 0.0f) rotateArbitrary(img.data, img.width, img.height, 4, angle);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat_x ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat_y ? GL_REPEAT : GL_CLAMP_TO_EDGE);

    TextureFilter texfilter = defineFilter(filter);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texfilter.min_f);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texfilter.mag_f);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
    if (texfilter.use_mipmap) 
        glGenerateMipmap(GL_TEXTURE_2D);  

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(img.data);

    return texture;
}



GLuint giveTextureArray(list_str images_path, list_bool flips_x, list_bool flips_y, list_float angles, int filter, bool repeat_x, bool repeat_y){
    if (images_path.size() != flips_x.size() || images_path.size() != flips_y.size() || images_path.size() != angles.size())
        throw std::runtime_error("Arrays must be of the same size!");

    GLuint TextureArray;
    glGenTextures(1, &TextureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, TextureArray);

    int layers = images_path.size();
    ImageData first = loadImage(images_path[0]);
    int width = first.width;
    int height = first.height;
    bool flip_x = flips_x[0];
    bool flip_y = flips_y[0];
    float angle = angles[0];

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    
    if (flip_x) flipX(first.data, width, height, 4);
    if (flip_y) flipY(first.data, width, height, 4);
    if (angle != 0.0f) rotateArbitrary(first.data, width, height, 4, angle);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, first.data);

    stbi_image_free(first.data);

    for (int i = 1; i < layers; i++)
    {
        ImageData img = loadImage(images_path[i]);
        bool flip_x = flips_x[i];
        bool flip_y = flips_y[i];
        float angle = angles[i];

        if (img.width != width || img.height != height)
            throw std::runtime_error("Texture size mismatch!");

        if (flip_x) flipX(img.data, width, height, 4);
        if (flip_y) flipY(img.data, width, height, 4);
        if (angle != 0.0f) rotateArbitrary(img.data, width, height, 4, angle);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

        stbi_image_free(img.data);
    }

    TextureFilter texfilter = defineFilter(filter);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, texfilter.min_f);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, texfilter.mag_f);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, repeat_x ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, repeat_y ? GL_REPEAT : GL_CLAMP_TO_EDGE);

    if (texfilter.use_mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    }

    return TextureArray;
}



GLuint giveTextureText(std::string font_path, std::string text, float pixel_size, int filter, bool repeat_x, bool repeat_y){
    std::ifstream file(font_path, std::ios::binary);
    if (!file) throw std::runtime_error("Can not load font path");

    std::vector<unsigned char> ttf_buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    stbtt_fontinfo font;
    int width, height, xoff, yoff;
    if (stbtt_InitFont(&font, ttf_buffer.data(), 0))
        throw std::runtime_error("Failed to init font");

    float scale = stbtt_ScaleForPixelHeight(&font, pixel_size);
    



    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, );

    TextureFilter texfilter = defineFilter(filter);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, texfilter.min_f);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, texfilter.mag_f);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, repeat_x ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, repeat_y ? GL_REPEAT : GL_CLAMP_TO_EDGE);

    if (texfilter.use_mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}