#include <wx/wx.h>
#include "InputMgr.h"
#include "Logger.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame()
        : wxFrame(nullptr, wxID_ANY, "DeckRC", wxDefaultPosition, wxSize(400, 300),
                  wxDEFAULT_FRAME_STYLE) // Standard window with close/min/max buttons
    {
        // Add "Hello, World!" label
        new wxStaticText(this, wxID_ANY, "Hello, World!", wxPoint(20, 20));
    }
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    Input::InputMgr::InitInstance();
    LOG_INF("DeckRC started");
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}
