#include "InputMgr.h"
#include "Logger.h"

Input::InputMgrPtr Input::InputMgr::m_Instance; 
std::mutex Input::InputMgr::m_InitMutex;

bool Input::InputMgr::InitInstance()
{
    std::lock_guard<std::mutex> lock(m_InitMutex);
    if (m_Instance == nullptr)
    {
        try
        {
            m_Instance = Input::InputMgrPtr{new InputMgr()};
        }
        catch (const std::exception& e)
        {
            LOG_ERR("Failed to initialize InputMgr: %s", e.what());
            m_Instance.reset();
            return false;
        }
    }
    return true;
}

Input::InputMgrPtr Input::InputMgr::GetInstance()
{
    return m_Instance;
}

bool Input::InputMgr::InitSDL()
{
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
    {
        LOG_ERR("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }
    else
    {
        LOG_INF("SDL initialized successfully.");
        return true;
    }
}

Input::InputMgr::~InputMgr()
{
    if (m_GameController)
    {
        m_GameController.reset();
    }
    SDL_Quit();
}

bool Input::InputMgr::InitGameController()
{
    m_GameController = SDLGameControllerPtr{SDL_GameControllerOpen(0)};
    if (m_GameController == nullptr)
    {
        LOG_ERR("SDL_GameController could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }
    else
    {
        LOG_INF("SDL_GameController initialized successfully.");
        return true;
    }
}

Input::InputMgr::InputMgr()
{
    if(!InitSDL())
    {
        throw std::runtime_error("SDL initialization failed");
    }
    if(!InitGameController())
    {
        throw std::runtime_error("Game Controller initialization failed");
    }
    LOG_INF("InputMgr initialized successfully.");
}

void Input::InputMgr::FetchInput()
{
    PollEvents();
    HandleAnalogInput();
}

void Input::InputMgr::HandleButton(uint8_t button, bool isPressed)
{
    std::lock_guard<std::mutex> lock(m_InputStatesMutex);
    switch (button)
    {
        case SDL_CONTROLLER_BUTTON_A:
            m_InputStates.button_A = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_B:
            m_InputStates.button_B = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_X:
            m_InputStates.button_X = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_Y:
            m_InputStates.button_Y = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
            m_InputStates.button_LB = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
            m_InputStates.button_RB = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_LEFTSTICK:
            m_InputStates.button_LStcik = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
            m_InputStates.button_RStcik = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            m_InputStates.button_DPadUp = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            m_InputStates.button_DPadDown = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            m_InputStates.button_DPadLeft = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            m_InputStates.button_DPadRight = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_START:
            m_InputStates.button_Start = isPressed;
            break;
        case SDL_CONTROLLER_BUTTON_BACK:
            m_InputStates.button_Select = isPressed;
            break;
        default:
            LOG_ERR("Unknown button pressed: %d", button);
            break;
    }
}

void Input::InputMgr::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {       
            case SDL_CONTROLLERBUTTONDOWN:
                HandleButton(event.cbutton.button, true);
                break;
                
            case SDL_CONTROLLERBUTTONUP:
                HandleButton(event.cbutton.button, false);
                break;
                
        }
    }
}

void Input::InputMgr::HandleAnalogInput()
{
    int readLeftX{SDL_GameControllerGetAxis(m_GameController.get(), SDL_CONTROLLER_AXIS_LEFTX)};
    int readLeftY{SDL_GameControllerGetAxis(m_GameController.get(), SDL_CONTROLLER_AXIS_LEFTY)};
    int readRightX{SDL_GameControllerGetAxis(m_GameController.get(), SDL_CONTROLLER_AXIS_RIGHTX)};
    int readRightY{SDL_GameControllerGetAxis(m_GameController.get(), SDL_CONTROLLER_AXIS_RIGHTY)};
    int readLeftTrigger{SDL_GameControllerGetAxis(m_GameController.get(), SDL_CONTROLLER_AXIS_TRIGGERLEFT)};
    int readRightTrigger{SDL_GameControllerGetAxis(m_GameController.get(), SDL_CONTROLLER_AXIS_TRIGGERRIGHT)};

    int correctedLeftX{abs(readLeftX) < Input::k_JoystickDeadzoone ? 0 : readLeftX};
    int correctedLeftY{abs(readLeftY) < Input::k_JoystickDeadzoone ? 0 : readLeftY};
    int correctedRightX{abs(readRightX) < Input::k_JoystickDeadzoone ? 0 : readRightX};
    int correctedRightY{abs(readRightY) < Input::k_JoystickDeadzoone ? 0 : readRightY};

    std::lock_guard<std::mutex> lock(m_InputStatesMutex);
    m_InputStates.axis_LeftX = correctedLeftX;
    m_InputStates.axis_LeftY = correctedLeftY;
    m_InputStates.axis_RightX = correctedRightX;
    m_InputStates.axis_RightY = correctedRightY;
    m_InputStates.axis_LeftTrigger = readLeftTrigger;
    m_InputStates.axis_RightTrigger = readRightTrigger;
}

Input::InputStates Input::InputMgr::GetInputStates()
{
    std::lock_guard<std::mutex> lock(m_InputStatesMutex);
    return m_InputStates;
}