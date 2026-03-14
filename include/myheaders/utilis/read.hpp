#pragma once

#include <myheaders/stdport/stdport.hpp>


using json = nlohmann::json;

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


class Johnson{
    public:
        std::string json_path; 

        Johnson(const std::string& json_path) : json_path(json_path){}

        json readData(){
            json data;
            std::ifstream file(json_path);
            if (!file) 
                throw std::runtime_error("Can not load Json path");

            file >> data;

            return data;
        }


        void saveData(json data){
            std::ofstream file(json_path);
            if (!file) 
                throw std::runtime_error("Can not load Json path");

            file << data.dump(4);
        }

};




std::string getDataPath(const std::string& path){ return "assets/datas/" + path;}

std::string getFontPath(const std::string& path){ return "assets/fonts/" + path;}

std::string getShaderPath(const std::string& path){ return "assets/shaders/" + path;}

std::string getMusicPath(const std::string& path){ return "assets/soundtracks/" + path;}

std::string getAssetPath(const std::string& path){ return "assets/atlas/" + path;}