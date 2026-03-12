#pragma once

#include <myheaders/stdport/stdport.hpp>

#include <myheaders/scenes/menu.hpp>
#include <myheaders/scene_component.hpp>






class SceneManager{
    public:
        Game* game;

        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> init_dict;
        std::unordered_map<std::string, std::function<SceneComponent*()>> scene_dict;
        std::string manager_state = "";

        SceneComponent* current_scene = nullptr;

        SceneManager(Game* game) : game(game){
            //registration
            game->scene = "intro";

            init_dict["intro"] = {{"hello", "hello world"}};
            

            registerScene<IntroScene>("intro");
            registerScene<MainMenu>("menu");
            registerScene<SceneEmpty>("settings");
            registerScene<SceneEmpty>("quit");

            registerScene<SceneEmpty>("first");
            registerScene<SceneEmpty>("tutorial");
            registerScene<SceneEmpty>("ending");

            registerScene<SceneEmpty>("overworld-1");
            registerScene<SceneEmpty>("overworld-2");
            registerScene<SceneEmpty>("overworld-3");

            registerScene<SceneEmpty>("level-1");
            registerScene<SceneEmpty>("level-2");
            registerScene<SceneEmpty>("level-3");
            registerScene<SceneEmpty>("level-4");

            registerScene<SceneEmpty>("level-1b");
            registerScene<SceneEmpty>("level-2b");
            registerScene<SceneEmpty>("level-3b");
            registerScene<SceneEmpty>("level-4b");
            registerScene<SceneEmpty>("level-5b");
            
            registerScene<SceneEmpty>("level-1c");
            registerScene<SceneEmpty>("level-2c");
            registerScene<SceneEmpty>("level-3c");
            registerScene<SceneEmpty>("level-4c");
            registerScene<SceneEmpty>("level-5c");
            registerScene<SceneEmpty>("level-6c");

   
        }
        

        void updateScene(){
            std::string state = this->game->scene;

            if (state == "quit")
                game->closeGame();
        

            if (state != manager_state){
                manager_state = state;
                if (current_scene){
                    current_scene->onDestroy();
                    delete current_scene;
                }

                try{
                    current_scene = scene_dict.at(state)();
                }catch (std::out_of_range& e){
                    throw std::out_of_range("\033[31mThe scene '" + state + "' its not defined\033[0m");
                   
                }

                current_scene->onInit(init_dict.find(state) != init_dict.end() ? init_dict[state] : std::unordered_map<std::string,std::string>{});
            }
            
            if (current_scene)
                current_scene->onUpdate();
        
        }

        void eventScene(SDL_Event e){
            if (current_scene)
                current_scene->onEvent(e);
        }

        void renderScene(){
            if (current_scene)
                current_scene->onRender();
        }

    
    private:

        template<typename T>
        void registerScene(const std::string& name){
            scene_dict[name] = [this](){
                return new T(this->game);
            };
        }

};


