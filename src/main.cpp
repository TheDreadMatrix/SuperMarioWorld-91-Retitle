//OWN HEADERS
#define STB_IMAGE_IMPLEMENTATION

#include <myheaders/scene_manager.hpp>
#include <myheaders/game.hpp>






Game::Game(){
    SDL_Init(SDL_INIT_VIDEO);
    AEngine = new SoLoud::Soloud;
    AEngine->init();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); 
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    window = SDL_CreateWindow("Super Mario World: 91 Retitle", 800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_BORDERLESS);

    int width, height, channels;
    unsigned char* data = stbi_load("assets/icon.png", &width, &height, &channels, 4);
    SDL_Surface* icon = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, data, width * 4);
    SDL_SetWindowIcon(window, icon);
    SDL_DestroySurface(icon);  
    stbi_image_free(data);

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_HideCursor();
    SDL_SetWindowMouseGrab(window, true);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    

    gladLoadGL();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   
    
  
    //RESIZING
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    projection = glm::ortho(0.0f, static_cast<float>(window_width), static_cast<float>(window_height), 0.0f, 1.0f, -1.0f);
    glViewport(0, 0, window_width, window_height);

    vertices = {
        0.0f, 1.0f,       0.0f, 1.0f,
        1.0f, 1.0f,       1.0f, 1.0f,
        1.0f, 0.0f,       1.0f, 0.0f,
        0.0f, 0.0f,       0.0f, 0.0f
    };
    indices = {
        0, 1, 2, 2, 3, 0
    };


    //FBO RBO TEXTURE
    /*
    genFbo(fbo);
    genRbo(rbo);
    texColorBuffer = giveTextureFrame(window_width, window_height);

    bindFbo(fbo);
    bindRbo(rbo, window_width, window_height);
    attachTexFbo(texColorBuffer);

    bindFbo(0);

    //PROGRAM VAO EBO VBO
    std::vector<float> vertices = {
        // x, y,   u, v
        -1.0f, -1.0f,  0.0f, 0.0f, 
        1.0f, -1.0f,  1.0f, 0.0f, 
        1.0f,  1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  0.0f, 1.0f 
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };
    shader = new Program(readFile("assets/shaders/core/core.vert"), readFile("assets/shaders/core/core.frag"));
    genVao(g_vao);
    genBuffer(g_vbo);
    genBuffer(g_ebo);

    bindVao(g_vao);
    bindBuffer(GL_ARRAY_BUFFER, g_vbo, vertices);
    bindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebo, indices);

    setShader(0, 2, 4, 0);
    setShader(1, 2, 4, 2);

    bindVao(0);*/


    //SCENES
    scenes = new SceneManager(this);

}

void Game::closeGame(){
    running = false;
}

void Game::switchScene(std::string scene_name, bool reload){
    scene = scene_name;
}


void Game::updateGame(){
    scenes->updateScene();
    time += delta;
    while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
                scenes->eventScene(e);

            if (e.type == SDL_EVENT_KEY_DOWN){
                if (e.key.repeat == 0 && e.key.scancode == SDL_SCANCODE_ESCAPE)
                    running = false;
            }

            if (e.type == SDL_EVENT_WINDOW_RESIZED){
                int new_width, new_height;
                SDL_GetWindowSize(window, &new_width, &new_height);

                glViewport(0, 0, new_width, new_height);
                projection = glm::ortho(0.0f, static_cast<float>(new_width), static_cast<float>(new_height), 0.0f, -1.0f, 1.0f);
            }
        }
    
}


void Game::renderGame(){
    //bindFbo(fbo);

    scenes->renderScene();

    //bindFbo(0);
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //activateTexture(texColorBuffer);

    //shader->useProgram();
    //shader->setInt("tex", 0);
    //shader->setFloat("time", time);

    //render(g_vao, 6);

    SDL_GL_SwapWindow(window);
}



void Game::runGame(){
    const float targetFPS = FPS > 0.0f ? FPS : 0.0f;
    const float targetFrameTime = targetFPS > 0.0f ? 1.0f / targetFPS : 0.0f;

    Uint64 prevCounter = SDL_GetPerformanceCounter();
    while (running){
        Uint64 frameStart = SDL_GetPerformanceCounter();
        Uint64 now = SDL_GetPerformanceCounter();
        delta = (float)(now - prevCounter) / SDL_GetPerformanceFrequency();
        prevCounter = now;

        if(delta > 0.1f) delta = 0.1f;

        updateGame();
        renderGame();

        if(targetFrameTime > 0.0f){
            Uint64 frameEnd = SDL_GetPerformanceCounter();
            float frameTime = (float)(frameEnd - frameStart) / (float)SDL_GetPerformanceFrequency();

            if(frameTime < targetFrameTime){
                float delayMS = (targetFrameTime - frameTime) * 1000.0f;
                if(delayMS > 1.0f){
                    SDL_Delay((Uint32)(delayMS - 1));
                }
                while((float)(SDL_GetPerformanceCounter() - frameStart) / SDL_GetPerformanceFrequency() < targetFrameTime);
            }
        }

        fps = 1.0f / delta;

    }

    SDL_DestroyWindow(window);
    SDL_GL_DestroyContext(gl_context);
    SDL_Quit();
    AEngine->deinit();
    delete AEngine;
    delete scenes;
}



int main(){
    std::cout << "OK RUN" << std::endl;

    Game game;

    game.runGame();


    std::cout << "OK QUIT" << std::endl;

    return 0;
}
