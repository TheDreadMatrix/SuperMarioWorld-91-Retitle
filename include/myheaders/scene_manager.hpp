#pragma once

#include <myheaders/stdport/stdport.hpp>

#include <myheaders/scenes/menu.hpp>
#include <myheaders/scene_component.hpp>






class SceneManager{
    public:
        Game* game;

        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> init_dict;
        std::unordered_map<std::string, std::function<std::unique_ptr<SceneComponent>()>> scene_dict;
        std::string manager_state = "";

        std::unique_ptr<SceneComponent> current_scene;

        SceneManager(Game* game) : game(game){
            game->scene = "intro";
            
            //SCENES-ATTRIBUTE
            init_dict["first"] = {{"biome", "valley"}};
            init_dict["tutorial"] = {{"biome", "valley"}};
            init_dict["ending"] = {{"biome", "ending"}};

            init_dict["overworld-1"] = {{"biome", "valley"}};
            init_dict["overworld-2"] = {{"biome", "mountain"}};
            init_dict["overworld-3"] = {{"biome", "magma"}};

            init_dict["level-1"] = {{"biome", "valley"}};
            init_dict["level-2"] = {{"biome", "valley"}};
            init_dict["level-3"] = {{"biome", "valley"}};
            init_dict["level-4"] = {{"biome", "valley"}};

            init_dict["level-1b"] = {{"biome", "mountain"}};
            init_dict["level-2b"] = {{"biome", "mountain"}};
            init_dict["level-3b"] = {{"biome", "mountain"}};
            init_dict["level-4b"] = {{"biome", "mountain"}};
            init_dict["level-5b"] = {{"biome", "mountain"}};

            init_dict["level-1c"] = {{"biome", "magma"}};
            init_dict["level-2c"] = {{"biome", "magma"}};
            init_dict["level-3c"] = {{"biome", "magma"}};
            init_dict["level-4c"] = {{"biome", "magma"}};
            init_dict["level-5c"] = {{"biome", "magma"}};
            init_dict["level-6c"] = {{"biome", "magma"}};


            //REGISTER
            registerScene<SceneEmpty>("test");

            registerScene<IntroScene>("intro");
            registerScene<MainMenu>("menu");
            registerScene<SceneEmpty>("settings");
            registerScene<SceneEmpty>("quit");

            registerScene<SceneEmpty>("game-over");
            registerScene<SceneEmpty>("bonus-game");
            registerScene<SceneEmpty>("time-out");

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
                return std::make_unique<T>(this->game);
            };
        }

};


