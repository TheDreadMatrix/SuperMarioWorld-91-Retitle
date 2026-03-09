#pragma once

#include <myheaders/stdport/stdport.hpp>


std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    file.close();

    return contents.str();
}

