#include <myheaders/imports.hpp>


void _flipX(unsigned char* data, int width, int height, int channels) {
    for (int y = 0; y < height; y++) {
        unsigned char* line = data + y * width * channels;
        for (int x = 0; x < width / 2; x++) {
            for (int c = 0; c < channels; c++) {
                std::swap(line[x * channels + c], line[(width - 1 - x) * channels + c]);
            }
        }
    }
}

void _flipY(unsigned char* data, int width, int height, int channels) {
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

void _rotateArbitrary(unsigned char* data, int width, int height, int channels, float angleDegrees) {
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


struct _TextureFilter{
    GLint min_filter;
    GLint mag_filter;
    bool use_mipmap;
};

struct _ImageData {
    unsigned char* data;
    int width;
    int height;
    int channels;
};

struct _FontData{
    unsigned char* data;
    int width, height;
    int xoff, yoff;
};


_TextureFilter _defineFilter(int filter){
    _TextureFilter Texfilter;
    switch (filter) {
        case 1: Texfilter.min_filter = GL_NEAREST; Texfilter.mag_filter = GL_NEAREST; Texfilter.use_mipmap = false; break;
        case 2: Texfilter.min_filter = GL_LINEAR; Texfilter.mag_filter = GL_LINEAR; Texfilter.use_mipmap = false; break;
        case 3: Texfilter.min_filter = GL_NEAREST_MIPMAP_NEAREST; Texfilter.mag_filter = GL_NEAREST; Texfilter.use_mipmap = true; break;
        case 4: Texfilter.min_filter = GL_LINEAR_MIPMAP_NEAREST; Texfilter.mag_filter = GL_LINEAR; Texfilter.use_mipmap = true; break;
        case 5: Texfilter.min_filter = GL_LINEAR_MIPMAP_LINEAR; Texfilter.mag_filter = GL_LINEAR; Texfilter.use_mipmap = true; break;
        case 6: Texfilter.min_filter = GL_NEAREST_MIPMAP_LINEAR; Texfilter.mag_filter = GL_NEAREST; Texfilter.use_mipmap = true; break;
        default: Texfilter.min_filter = GL_NEAREST; Texfilter.mag_filter = GL_NEAREST; Texfilter.use_mipmap = false; break;
    }
    return Texfilter;
}

_ImageData _loadImage(std::string image_path){
    _ImageData img;
    img.data = stbi_load(image_path.c_str(), &img.width, &img.height, &img.channels, STBI_rgb_alpha);
    if (!img.data) {
        throw std::runtime_error("Failed to load image: " + image_path);
    }

    return img;
}


// OPENGL TEXTURES



GLuint giveTexture(std::string image_path, int filter, bool repeat_x=false, bool repeat_y=false, bool flipx=false, bool flipy=false, float angle=0.0f){
    _ImageData img = _loadImage(image_path);
    if (flipx) _flipX(img.data, img.width, img.height, 4);
    if (flipy) _flipY(img.data, img.width, img.height, 4);
    if (angle != 0.0f) _rotateArbitrary(img.data, img.width, img.height, 4, angle);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat_x ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat_y ? GL_REPEAT : GL_CLAMP_TO_EDGE);

    _TextureFilter texfilter = _defineFilter(filter);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texfilter.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texfilter.mag_filter);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
    if (texfilter.use_mipmap) 
        glGenerateMipmap(GL_TEXTURE_2D);  

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(img.data);

    return texture;
}



GLuint giveTextureArray(std::vector<std::string>& images_path, std::vector<bool>& flips_x, std::vector<bool>& flips_y, std::vector<float>& angles, int filter, bool repeat_x = true, bool repeat_y = true){

    if (images_path.size() != flips_x.size() || images_path.size() != flips_y.size() || images_path.size() != angles.size())
        throw std::runtime_error("Arrays must be of the same size!");

    GLuint TextureArray;
    glGenTextures(1, &TextureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, TextureArray);

    int layers = images_path.size();
    _ImageData first = _loadImage(images_path[0]);
    int width = first.width;
    int height = first.height;
    bool flip_x = flips_x[0];
    bool flip_y = flips_y[0];
    float angle = angles[0];

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    
    if (flip_x) _flipX(first.data, width, height, 4);
    if (flip_y) _flipY(first.data, width, height, 4);
    if (angle != 0.0f) _rotateArbitrary(first.data, width, height, 4, angle);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, first.data);

    stbi_image_free(first.data);

    for (int i = 1; i < layers; i++)
    {
        _ImageData img = _loadImage(images_path[i]);
        bool flip_x = flips_x[i];
        bool flip_y = flips_y[i];
        float angle = angles[i];

        if (img.width != width || img.height != height)
            throw std::runtime_error("Texture size mismatch!");

        if (flip_x) _flipX(img.data, width, height, 4);
        if (flip_y) _flipY(img.data, width, height, 4);
        if (angle != 0.0f) _rotateArbitrary(img.data, width, height, 4, angle);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

        stbi_image_free(img.data);
    }

    _TextureFilter texfilter = _defineFilter(filter);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, texfilter.min_filter);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, texfilter.mag_filter);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, repeat_x ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, repeat_y ? GL_REPEAT : GL_CLAMP_TO_EDGE);

    if (texfilter.use_mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    }

    return TextureArray;

}


GLuint giveTextureCube(std::vector<std::string>& images_path, std::vector<bool>& flips_x, std::vector<bool>& flips_y, std::vector<float>& angles, int filter, bool repeat_x = true, bool repeat_y = true, bool repeat_z = true){
    if (images_path.size() != 6 || flips_x.size() != 6 || flips_y.size() != 6 || angles.size() != 6)
        throw std::runtime_error("Cubemap says that array must be 6 size of elements");
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

    _ImageData first = _loadImage(images_path[0]);

    int width = first.width;
    int height = first.height;

  
    if (flips_x[0]) _flipX(first.data, width, height, 4);
    if (flips_y[0]) _flipY(first.data, width, height, 4);
    if (angles[0] != 0.0f) _rotateArbitrary(first.data, width, height, 4, angles[0]);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, first.data);

    stbi_image_free(first.data);

    for (int i = 1; i < 6; i++)
    {
        _ImageData img = _loadImage(images_path[i]);

        if (img.width != width || img.height != height)
            throw std::runtime_error("Cubemap face size mismatch!");

        if (flips_x[i]) _flipX(img.data, width, height, 4);
        if (flips_y[i]) _flipY(img.data, width, height, 4);
        if (angles[i] != 0.0f) _rotateArbitrary(img.data, width, height, 4, angles[i]);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);

        stbi_image_free(img.data);
    }

    _TextureFilter texfilter = _defineFilter(filter);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, texfilter.min_filter);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, texfilter.mag_filter);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, repeat_x ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, repeat_y ? GL_REPEAT : GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, repeat_z ? GL_REPEAT : GL_CLAMP_TO_EDGE);


    if (texfilter.use_mipmap)
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    
    return texID;
}


GLuint giveTextureFrameBuffer(int width, int height){
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,texture, 0);

    return texture;
}
