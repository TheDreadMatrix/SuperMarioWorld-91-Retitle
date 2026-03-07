#pragma once
#include <myheaders/imports.hpp>
#include <myheaders/opengl/program.hpp>

#ifndef FPS
    #define FPS 1000
#endif

class SceneManager;


class Game{
    public:
        //OPENGL
        GLuint g_vao, g_vbo, g_ebo=0;
        GLuint texColorBuffer=0;
        GLuint fbo=0;
        GLuint rbo=0;
        Program *shader=nullptr;

        glm::mat4 projection;

        //SDL
        SDL_Window* window;
        SDL_GLContext gl_context;
        SDL_Surface* icon;
        SDL_Event e;

        //STD
        std::string scene = "scene-0";
        bool running = true;
        float delta, fps = 0.0f;

        //MY CLASS
        SceneManager* scenes;

        Game();

        void closeGame();

        void switchScene(std::string scene_name, bool reload=false);

        void updateGame();

        void renderGame();

        void runGame();

};