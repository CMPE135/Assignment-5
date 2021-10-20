#ifndef __RPSAPP_H__
#define __RPSAPP_H__

#include <wx/wx.h>
#include "RPSFrame.hpp"

class RPSApp: public wxApp {
  public:
    bool OnInit() override;
};

#endif //__RPSAPP_H__