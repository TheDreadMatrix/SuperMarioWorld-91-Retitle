#pragma once

#include <myheaders/stdport/stdport.hpp>

#include <myheaders/game.hpp>



class SceneComponent{  
    public:
        Game* game;
        SceneComponent(Game* game) : game(game){}

        virtual ~SceneComponent() = default;

        virtual void onInit(const std::unordered_map<std::string,std::string>& data = {}){}

        virtual void onUpdate(){}

        virtual void onEvent(SDL_Event e){}

        virtual void onRender(){}

        virtual void onDestroy(){}
};


class SceneEmpty : public SceneComponent{
    public:
        SceneEmpty(Game* game) : SceneComponent(game) {}
        ~SceneEmpty() override = default;
        void onInit(const std::unordered_map<std::string,std::string>& data = {}) override {std::cout << "SCENE CREATED" << std::endl;}
        void onUpdate() override {}
        void onEvent(SDL_Event e) override {
            if (e.type == SDL_EVENT_KEY_DOWN){
                if (e.key.scancode == SDL_SCANCODE_A)
                    game->switchScene("menu");
            }
        }
        void onRender() override {glClearColor(0.0f, 0.0f, 1.0f, 1.0f); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}
        void onDestroy() override {std::cout << "EMPTY DESTROYED" << std::endl;}
};
