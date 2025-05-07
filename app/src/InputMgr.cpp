#include <iostream>
#include "InputMgr.h"


bool InputMgr::InitSDL()
{
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        std::cout << "SDL initialized successfully." << std::endl;
        return true;
    }
}

bool InputMgr::InitGameController()
{
    SDLGameControllerPtr controller(SDL_GameControllerOpen(0));
    // m_GameController = std::unique_ptr<SDL_GameController>(controller);
    if (controller == nullptr)
    {
        std::cout << "SDL_GameController Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        std::cout << "SDL_GameController initialized successfully." << std::endl;
        return true;
    }
}

InputMgr::InputMgr()
{
    if(!InitSDL())
    {
        std::cout << "Failed to initialize SDL." << std::endl;
        throw std::runtime_error("SDL initialization failed");
    }
    if(!InitGameController())
    {
        std::cout << "Failed to initialize Game Controller." << std::endl;
        throw std::runtime_error("Game Controller initialization failed");
    }
    std::cout << "InputMgr initialized successfully." << std::endl;
}