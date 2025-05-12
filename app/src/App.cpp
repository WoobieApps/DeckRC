#include "App.h"
#include "InputMgr.h"
#include "Logger.h"
constexpr int k_MainFrameTimerID{wxID_HIGHEST + 1};

bool App::OnInit()
{
    LOG_INF("DeckRC started");
    Input::InputMgr::InitInstance();
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_TIMER(k_MainFrameTimerID, MainFrame::OnTimer)
wxEND_EVENT_TABLE()

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "DeckRC", wxDefaultPosition, wxSize(800, 600),
              wxDEFAULT_FRAME_STYLE)
{
    // Initialize the timer
    m_timer = new wxTimer(this, k_MainFrameTimerID);
    m_timer->Start(1, wxTIMER_CONTINUOUS);
    
    // Create main sizer with two columns
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    
    // Left panel for buttons
    wxStaticBoxSizer* buttonSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Buttons");
    
    // Button labels and their corresponding enum values
    const struct { const char* label; Input::ButtonInputs button; } buttonInfo[] = {
        {"A", Input::ButtonInputs::A},
        {"B", Input::ButtonInputs::B},
        {"X", Input::ButtonInputs::X},
        {"Y", Input::ButtonInputs::Y},
        {"LB", Input::ButtonInputs::LB},
        {"RB", Input::ButtonInputs::RB},
        {"L Stick", Input::ButtonInputs::L_STICK},
        {"R Stick", Input::ButtonInputs::R_STICK},
        {"D-Pad Up", Input::ButtonInputs::DPAD_UP},
        {"D-Pad Down", Input::ButtonInputs::DPAD_DOWN},
        {"D-Pad Left", Input::ButtonInputs::DPAD_LEFT},
        {"D-Pad Right", Input::ButtonInputs::DPAD_RIGHT},
        {"Start", Input::ButtonInputs::START},
        {"Select", Input::ButtonInputs::SELECT}
    };
    
    // Create button displays
    for (const auto& info : buttonInfo) {
        wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);
        row->Add(new wxStaticText(this, wxID_ANY, info.label), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        
        m_buttonStates[static_cast<int>(info.button)] = new wxTextCtrl(
            this, wxID_ANY, "False",
            wxDefaultPosition, wxSize(60, -1),
            wxTE_READONLY | wxTE_CENTER
        );
        row->Add(m_buttonStates[static_cast<int>(info.button)], 1, wxEXPAND);
        buttonSizer->Add(row, 0, wxEXPAND | wxALL, 2);
    }
    
    // Right panel for axes
    wxStaticBoxSizer* axisSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Axes");
    
    // Axis labels and their corresponding enum values
    const struct { const char* label; Input::AxisInputs axis; } axisInfo[] = {
        {"Left Stick X", Input::AxisInputs::L_STICK_X},
        {"Left Stick Y", Input::AxisInputs::L_STICK_Y},
        {"Right Stick X", Input::AxisInputs::R_STICK_X},
        {"Right Stick Y", Input::AxisInputs::R_STICK_Y},
        {"Left Trigger", Input::AxisInputs::L_TRIGGER},
        {"Right Trigger", Input::AxisInputs::R_TRIGGER}
    };
    
    // Create axis displays
    for (const auto& info : axisInfo) {
        wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);
        row->Add(new wxStaticText(this, wxID_ANY, info.label), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        
        m_axisStates[static_cast<int>(info.axis)] = new wxTextCtrl(
            this, wxID_ANY, "0",
            wxDefaultPosition, wxSize(80, -1),
            wxTE_READONLY | wxTE_CENTER
        );
        row->Add(m_axisStates[static_cast<int>(info.axis)], 1, wxEXPAND);
        axisSizer->Add(row, 0, wxEXPAND | wxALL, 2);
    }
    
    // Add both sizers to the main sizer
    mainSizer->Add(buttonSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(axisSizer, 1, wxEXPAND | wxALL, 5);
    
    SetSizer(mainSizer);
    Layout();
    
    // Set minimum size to prevent window from being too small
    SetMinSize(wxSize(400, 400));
}

void MainFrame::OnTimer(wxTimerEvent& event)
{
    auto inputMgr = Input::InputMgr::GetInstance();
    inputMgr->FetchInput();
    
    // Update button states
    for (int i = 0; i < static_cast<int>(Input::ButtonInputs::BUTTON_COUNT); ++i) {
        bool state = inputMgr->GetButtonState(static_cast<Input::ButtonInputs>(i));
        m_buttonStates[i]->SetValue(state ? "True" : "False");
    }
    
    // Update axis states
    for (int i = 0; i < static_cast<int>(Input::AxisInputs::AXIS_COUNT); ++i) {
        int value = inputMgr->GetAxisValue(static_cast<Input::AxisInputs>(i));
        m_axisStates[i]->SetValue(wxString::Format("%d", value));
    }
}