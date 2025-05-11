#include <SDL2/SDL.h>
#include <memory>
#include <mutex>

namespace Input
{
    constexpr int k_JoystickDeadzoone{5000};
    class InputMgr;
    
    struct SDLGameControllerDeleter {
        void operator()(SDL_GameController* controller) const {
            if (controller) {
                SDL_GameControllerClose(controller);
            }
        }
    };

    using InputMgrPtr = std::shared_ptr<InputMgr>;
    using SDLGameControllerPtr = std::unique_ptr<SDL_GameController, SDLGameControllerDeleter>;

    struct InputStates
    {
        bool button_A{false};
        bool button_B{false};
        bool button_X{false};
        bool button_Y{false};
        bool button_LB{false};
        bool button_RB{false};
        bool button_LStick{false};
        bool button_RStick{false};
        bool button_DPadUp{false};
        bool button_DPadDown{false};
        bool button_DPadLeft{false};
        bool button_DPadRight{false};
        bool button_Start{false};
        bool button_Select{false};
        int axis_LStickX{0};
        int axis_LStickY{0};
        int axis_RStickX{0};
        int axis_RStickY{0};
        int axis_LTrigger{0};
        int axis_RTrigger{0};
    };

    class InputMgr
    {
        public:
            static bool InitInstance();
            static InputMgrPtr GetInstance();
            void FetchInput();
            InputStates GetInputStates();

            InputMgr(const InputMgr&) = delete;
            InputMgr& operator=(const InputMgr&) = delete;
            InputMgr(InputMgr&&) = delete;
            ~InputMgr();
            
        private: 
            InputMgr();
            bool InitSDL();
            bool InitGameController();
            void HandleButton(uint8_t button, bool isPressed);
            void PollEvents();
            void HandleAnalogInput();
            static InputMgrPtr m_Instance;
            static std::mutex m_InitMutex;
            SDLGameControllerPtr m_GameController;
            InputStates m_InputStates;
            std::mutex m_InputStatesMutex;
    };
}