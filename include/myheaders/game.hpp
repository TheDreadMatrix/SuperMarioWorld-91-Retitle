#pragma once
#include <myheaders/imports.hpp>
#include <myheaders/opengl/program.hpp>

#ifndef FPS
    #define FPS 1000
#endif

class SceneManager;


class Game{
    public:
        GLuint g_vao, g_vbo, g_ebo;
        GLuint texColorBuffer;
        GLuint fbo;
        GLuint rbo;
        Program *shader;

        glm::mat4 projection;
        SDL_Window* window;
        SDL_GLContext gl_context;
        SDL_Surface* icon;
        SDL_Event e;

        Uint64 freq = 0;
        Uint64 last = 0;
        float fps = 0.0f;
        float delta = 0.0f;

        bool running = true;
        std::string scene = "scene-0";

        SceneManager* scenes;

        Game();

        void closeGame();

        void switchScene(std::string scene_name, bool reload=false);

        void updateGame();

        void renderGame();

        void runGame();

};