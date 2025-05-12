#pragma once
#include "InputMgr.h"
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
    
    // Button state displays
    wxTextCtrl* m_buttonStates[static_cast<int>(Input::ButtonInputs::BUTTON_COUNT)];
    
    // Axis state displays
    wxTextCtrl* m_axisStates[static_cast<int>(Input::AxisInputs::AXIS_COUNT)];
    
    wxDECLARE_EVENT_TABLE();
};