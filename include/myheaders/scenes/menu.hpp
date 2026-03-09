#pragma once


#include <soloud_wav.h>
#include <soloud_biquadresonantfilter.h>
#include <myheaders/scene_component.hpp>
#include <myheaders/utilis/read.hpp>


#include <moderngl/program_mesh.hpp>
#include <moderngl/textures.hpp>



class IntroScene : public SceneComponent{
    public:
        //ATTRIBUTES
        SoLoud::Wav gWave;
        SoLoud::BiquadResonantFilter lowpass;
        int h;

        GLuint vao, vbo, ebo, ivbo,  texture;
        Program *shader;

        glm::vec2 position = glm::vec2(0, 0);

        IntroScene(Game* game) : SceneComponent(game) {}

        void onInit() override {
            gWave.load("assets/soundtracks/n.wav");

            lowpass.setParams(SoLoud::BiquadResonantFilter::LOWPASS, 1500, 2);
            gWave.setFilter(0, &lowpass);
            gWave.setLooping(true);

            h = game->AEngine->play(gWave);

            std::vector<float>  vertices = {
                // positions       // uv_coords
                0.0f, 1.0f,       0.0f, 1.0f,
                1.0f, 1.0f,       1.0f, 1.0f,
                1.0f, 0.0f,       1.0f, 0.0f,
                0.0f, 0.0f,       0.0f, 0.0f

            };

            std::vector<unsigned int> indices = {
                0, 1, 2, 2, 3, 0
            };

            std::vector<glm::vec2> instanceOffsets;

            int amount = 100;

            for (int i = 0; i < amount; i++) {
                float x = (i % 10) * 100.0f;
                float y = (i / 10) * 100.0f;

                instanceOffsets.push_back(glm::vec2(x, y));
            }

            shader = new Program(readFile("assets/shaders/shader.vert"), readFile("assets/shaders/shader.frag"));
            texture = giveTexture("assets/icon.png", NEAREST, true, true, false, false, 0.0f);

            genVao(vao);
            genBuffer(vbo);
            genBuffer(ebo);
            genBuffer(ivbo);

            bindVao(vao);
            bindBuffer(GL_ARRAY_BUFFER, vbo, vertices);
            bindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo, indices);

            setShader(0, 2, 4, 0);
            setShader(1, 2, 4, 2);

            bindBuffer(GL_ARRAY_BUFFER, ivbo, instanceOffsets);
            setShader(2, 2, 2, 0, true);

            bindVao(0);

            
        }


        void onUpdate() override {
            const bool* keystate = SDL_GetKeyboardState(nullptr);
            if (keystate[SDL_SCANCODE_D])
                position.x += 200.0f * game->delta;
            else if (keystate[SDL_SCANCODE_A])
                position.x -= 200.0f * game->delta;

            if (keystate[SDL_SCANCODE_S])
                position.y += 200.0f * game->delta;
        }

        void onEvent(SDL_Event e) override {
            if (e.type == SDL_EVENT_KEY_DOWN){
                if (e.key.scancode == SDL_SCANCODE_W)
                    game->switchScene("menu");

                if (e.key.scancode == SDL_SCANCODE_I){
                    game->AEngine->setRelativePlaySpeed(h, 0.7);
                    game->AEngine->setVolume(h, 0.4);
                }else if (e.key.scancode == SDL_SCANCODE_K){
                    game->AEngine->setRelativePlaySpeed(h, 1.3);
                    game->AEngine->setVolume(h, 1.3);
                }
            }
        }

        void onRender() override {
            glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            activateTexture(texture);

            shader->useProgram();
            shader->setVector3("rgb", glm::vec3(1.0f, 1.0f, 1.0f));
            shader->setMatrix4("projection", game->projection);
            shader->setVector2("position", glm::round(position));
            shader->setVector2("scale", glm::vec2(100, 100));
            shader->setInt("tex", 0);

            renderDivisor(vao, 6, 100);

        }

        void onDestroy() override {
            delete shader;  
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ebo);
            glDeleteBuffers(1, &ivbo);
            glDeleteTextures(1, &texture);  
        }
};






class MainMenu : public SceneComponent{
    public:
        MainMenu(Game* game) : SceneComponent(game) {}
         ~MainMenu() override {}

        void onInit() override{
            std::cout << "MAIN CREATED" << std::endl;
            SDL_SetWindowTitle(game->window, "Main Menu");
        }

        void onUpdate() override{

        }

        void onEvent(SDL_Event e) override {
            if (e.type == SDL_EVENT_KEY_DOWN){
                if (e.key.scancode == SDL_SCANCODE_A)
                    game->switchScene("intro");
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
