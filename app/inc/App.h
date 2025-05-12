#pragma once
#include <wx/wx.h>

class App : public wxApp
{
public:
    virtual bool OnInit() override;
};

class MainFrame : public wxFrame
{
public:
    MainFrame();
    void OnTimer(wxTimerEvent& event);
    
private:
    wxTimer* m_timer;
    wxDECLARE_EVENT_TABLE();
};