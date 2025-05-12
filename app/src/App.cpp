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
    : wxFrame(nullptr, wxID_ANY, "DeckRC", wxDefaultPosition, wxSize(400, 300),
              wxDEFAULT_FRAME_STYLE)
{
    // Initialize the timer
    m_timer = new wxTimer(this, k_MainFrameTimerID);
    m_timer->Start(1, wxTIMER_CONTINUOUS);
    
    // Set up the main frame
    new wxStaticText(this, wxID_ANY, "Hello, World!", wxPoint(20, 20));
    
}

void MainFrame::OnTimer(wxTimerEvent& event)
{
    Input::InputMgr::GetInstance()->FetchInput();
}