#pragma once

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stb_truetype.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_biquadresonantfilter.h>

#define CLEAR_WINDOW GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT
#define TRUE 1
#define FALSE 0
#define BRUE true
#define BALSE false

#define NEAREST 1
#define LINEAR 2
#define NEAR_NEAREST 3
#define LINE_NEAREST 4
#define NEAR_LINEAR 5
#define LINE_LINEAR 6



//STANDART MODULES
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
