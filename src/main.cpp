#if defined(_WIN32)
    #include <windows.h>
    #include <mmsystem.h>
#else
    #error "That Game Support only Windows system!"
#endif

//OWN HEADERS
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include <myheaders/scene_manager.hpp>
#include <myheaders/game.hpp>






Game::Game(){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); 
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    window = SDL_CreateWindow("Super Mario World: 91 Retitle", 800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

    int width, height, channels;
    unsigned char* data = stbi_load("assets/icon.png", &width, &height, &channels, 4);
    SDL_Surface* icon = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, data, width * 4);
    SDL_SetWindowIcon(window, icon);
    SDL_DestroySurface(icon);
    stbi_image_free(data);

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    

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

    //FBO TEXTURE
    /*
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_width, window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window_width, window_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);*/


    //SCENES
    scenes = new SceneManager(this);

    /*
    std::vector<float> quadVertices = {
        // x, y,   u, v
        -1.0f,  1.0f,  0.0f, 1.0f,  
        -1.0f, -1.0f,  0.0f, 0.0f,  
        1.0f, -1.0f,  1.0f, 0.0f, 
        1.0f,  1.0f,  1.0f, 1.0f   
    };

    std::vector<unsigned int> quadIndices = {
        0, 1, 2,  
        0, 2, 3   
    };


    shader = new Program(readFile("assets/shaders/core/core.vert"), readFile("assets/shaders/core/core.frag"));
    genVao(g_vao);
    genBuffer(g_vbo);
    genBuffer(g_ebo);

    bindVao(g_vao);
    bindVbo(g_vbo, quadVertices);
    bindEbo(g_ebo, quadIndices);

    setShaderAttribute(0, 2, 4, 0);
    setShaderAttribute(1, 2, 4, 2);
    bindVao(0);*/


}

void Game::closeGame(){
    running = false;
}

void Game::switchScene(std::string scene_name, bool reload){
    scene = scene_name;
    if (reload)
        scenes->reloadScene(scene_name);
}


void Game::updateGame(){
    scenes->updateScene();

    while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
                scenes->eventScene(e);

            if (e.type == SDL_EVENT_WINDOW_RESIZED){
                int new_width, new_height;
                SDL_GetWindowSize(window, &new_width, &new_height);

                glViewport(0, 0, new_width, new_height);
                projection = glm::ortho(0.0f, static_cast<float>(new_width), static_cast<float>(new_height), 0.0f, -1.0f, 1.0f);
            }
        }
}


void Game::renderGame(){
    //glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scenes->renderScene();

    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //activateTexture(texColorBuffer, 1);
    //shader->useProgram();
    //shader->setInt("tex", 1);
    //shader->setFloat("time", SDL_GetTicks()/1000.0f);

    //Render(g_vao, 6);

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
        std::cout << fps << "\r";

    }

    SDL_DestroyWindow(window);
    SDL_GL_DestroyContext(gl_context);
    SDL_Quit();
    delete scenes;
}



int main(){
    std::cout << "OK RUN" << std::endl;
    timeBeginPeriod(1);

    Game game;

    game.runGame();

    timeEndPeriod(1);

    std::cout << "OK QUIT" << std::endl;

    return 0;
}
