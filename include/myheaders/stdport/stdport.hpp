#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

#define NEAREST 1
#define LINEAR 2
#define NEAR_NEAREST 3
#define LINE_NEAREST 4
#define NEAR_LINEAR 5
#define LINE_LINEAR 6

#include <json.hpp>
#include <SDL3/SDL.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <soloud_wav.h>
#include <soloud_biquadresonantfilter.h>
