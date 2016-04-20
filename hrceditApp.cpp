/***************************************************************
 * Name:      hrceditApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2016-04-18
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "hrceditApp.h"
#include "hrceditMain.h"

IMPLEMENT_APP(hrceditApp);

bool hrceditApp::OnInit()
{
    hrceditFrame* frame = new hrceditFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    
    return true;
}
