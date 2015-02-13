/***************************************************************
 * Name:      lms_suiteApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Lime Microsystems ()
 * Created:   2014-09-08
 * Copyright: Lime Microsystems (limemicro.com)
 * License:
 **************************************************************/

#include "lms_suiteApp.h"

//(*AppHeaders
#include "lms_suiteMain.h"
#include <wx/image.h>
//*)
IMPLEMENT_APP(lms_suiteApp);

bool lms_suiteApp::OnInit()
{
    //AppInitialize
    bool wxsOK = true;
    //wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	lms_suiteFrame* Frame = new lms_suiteFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    return wxsOK;

}
