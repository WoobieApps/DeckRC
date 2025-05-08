#include <SDL2/SDL.h>
#include <memory>

struct SDLGameControllerDeleter {
    void operator()(SDL_GameController* controller) const {
        if (controller) {
            SDL_GameControllerClose(controller);
        }
    }
};

using SDLGameControllerPtr = std::unique_ptr<SDL_GameController, SDLGameControllerDeleter>;

class InputMgr
{
    public:
        InputMgr();
        
        bool InitSDL();
        bool InitGameController();
        void PollEvents();
    private:
        SDLGameControllerPtr m_GameController;
};