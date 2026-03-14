#pragma once


#include <myheaders/scene_component.hpp>
#include <myheaders/utilis/read.hpp>
#include <myheaders/utilis/uv_atlas.hpp>


#include <moderngl/program_mesh.hpp>
#include <moderngl/textures.hpp>

struct InstanceData {
    glm::vec2 offset;
    glm::vec2 sprite_offset;
};



class IntroScene : public SceneComponent{
    public:
        SoLoud::Wav intro_sound;

        GLuint vao, vbo, ebo, ivbo, tex;
        Program* shader;

    
        glm::vec2 sprite_size = {8.0f / 512.0f, 8.0f / 502.0f};
        int handle_sound;
        float time = 0.0f;
        float fade_amp = 0.0f;

        IntroScene(Game* game) : SceneComponent(game) {}

        void onInit(const std::unordered_map<std::string,std::string>& data = {}) override {
            //intro_sound.load();
            

            tex = giveTexture(getAssetPath("fonts.png"));
            shader = new Program(readFile(getShaderPath("textures/text.vert")), readFile(getShaderPath("textures/text.frag")));


            
            std::vector<InstanceData> instances;
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            glGenBuffers(1, &ivbo);
            
            glBindVertexArray(vao);
            
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, game->vertices.size() * sizeof(float), game->vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, game->indices.size() * sizeof(float), game->indices.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);
            
            glBindBuffer(GL_ARRAY_BUFFER, ivbo);
            glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(InstanceData), instances.data(), GL_DYNAMIC_DRAW);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(InstanceData), (void*)(0 * sizeof(float)));
            glEnableVertexAttribArray(2);
            glVertexAttribDivisor(2, 1);

            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(InstanceData), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(3);
            glVertexAttribDivisor(3, 1);



            glBindVertexArray(0);
        }


        void onUpdate() override {
            time += game->delta;

            if (time >= 3.0f){
                
            }
        }

        void onEvent(SDL_Event e) override {

        }

        void onRender() override {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            
            shader->useProgram();

            shader->setMatrix4("projection", game->projection);
            shader->setVector2("sprite_size", sprite_size);

            shader->setFloat2("position", 0.0f, 0.0f);
            shader->setFloat2("scale", 80.0f, 80.0f);

            shader->setFloat("fade_amp", fade_amp);
            shader->setInt("z_layer", 1);
            shader->setInt("tex", 0);
            
            glBindVertexArray(vao);
            glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 1);
            glBindVertexArray(0);


        }

        void onDestroy() override {
            delete shader;
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ebo);
            glDeleteBuffers(1, &ivbo);
            glDeleteTextures(1, &tex);
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
                if (e.key.scancode == SDL_SCANCODE_K)
                    game->switchScene("intro");

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
