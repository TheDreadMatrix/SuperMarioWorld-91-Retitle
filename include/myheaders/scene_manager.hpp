#pragma once
#include <myheaders/imports.hpp>
#include <myheaders/scenes/menu.hpp>
#include <myheaders/scene_component.hpp>






class SceneManager{
    public:
        Game* game;

        std::unordered_map<std::string, std::function<SceneComponent*()>> scene_dict;
        std::string manager_state = "";

        SceneComponent* current_scene = nullptr;

        SceneManager(Game* game) : game(game){
            //registration
            game->scene = "intro";
            


            scene_dict["intro"] = [this](){return new IntroScene(this->game);};
            scene_dict["menu"] = [this](){return new MainMenu(this->game);};
            scene_dict["settings"] = [this](){return new SceneEmpty(this->game);};
            scene_dict["quit"] = [this](){return new SceneEmpty(this->game);};

            scene_dict["overworld-1"] = [this](){return new SceneEmpty(this->game);};
            scene_dict["level-1"] = [this](){return new SceneEmpty(this->game);};
            scene_dict["level-2"] = [this](){return new SceneEmpty(this->game);};
            scene_dict["level-3"] = [this](){return new SceneEmpty(this->game);};
            scene_dict["level-4"] = [this](){return new SceneEmpty(this->game);};
            scene_dict["level-b0"] = [this](){return new SceneEmpty(this->game);};

   
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
                    exit(1);
                }

                current_scene->onInit();
            }
            
            current_scene->onUpdate();
        
        }

        void eventScene(SDL_Event e){
            current_scene->onEvent(e);
        }

        void renderScene(){
            current_scene->onRender();
        }

        void reloadScene(std::string scene){
            if (scene_dict.find(scene) == scene_dict.end()){
                manager_state = scene;
                current_scene->onDestroy();
                delete current_scene;
                current_scene = scene_dict.at(scene)();
                current_scene->onInit();
            }
        }


};


