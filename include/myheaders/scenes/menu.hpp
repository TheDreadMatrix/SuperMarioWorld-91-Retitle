#pragma once


#include <soloud_wav.h>
#include <soloud_biquadresonantfilter.h>
#include <myheaders/scene_component.hpp>
#include <myheaders/utilis/read.hpp>


#include <moderngl/program_mesh.hpp>
#include <moderngl/textures.hpp>



class IntroScene : public SceneComponent{
    public:
        ImageData atlas;

        IntroScene(Game* game) : SceneComponent(game) {}

        void onInit(const std::unordered_map<std::string,std::string>& data = {}) override {
            atlas = loadImage(getAssetPath("fonts.png"));

            std::cout << data.at("hello") << std::endl;
        }


        void onUpdate() override {
            std::cout << game->fps << std::endl;
        }

        void onEvent(SDL_Event e) override {
        }

        void onRender() override {
            glClearColor(1.0f, 0.5f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        }

        void onDestroy() override {
            delete[] atlas.data;
        }
};






class MainMenu : public SceneComponent{
    public:
        std::unordered_map<int, std::string> dict_state;
        int current_state;
        float timer_finish = 0.0f;
        bool finished = false;
        std::string mode = "menu";

        MainMenu(Game* game) : SceneComponent(game) {}
         ~MainMenu() override {}

        void onInit(const std::unordered_map<std::string,std::string>& data = {}) override{
            dict_state = {{1, "first"}, {2, "settings"}, {3, "quit"}};



        }

        void onUpdate() override{
            if (finished){
                timer_finish += game->delta;

                if (timer_finish >= 5.0f)
                    game->switchScene(dict_state[current_state]);
            }
        }   

        void onEvent(SDL_Event e) override {
            if (e.type == SDL_EVENT_KEY_DOWN){
                if (e.key.scancode == SDL_SCANCODE_W && e.key.repeat == 0)
                    current_state++;
                else if (e.key.scancode == SDL_SCANCODE_S && e.key.repeat == 0)
                    current_state--;

                else if (e.key.scancode == SDL_SCANCODE_W && e.key.repeat){
                    if (current_state != 1)
                        finished = true;
                    else
                        mode = "files";
                }
                
            }
        }

        void onRender() override{
            glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        }

        void onDestroy() override{
            std::cout << "MAIN DESTROYED" << std::endl;
        }


};
