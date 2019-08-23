/***************************************************************
 * Name:      sniperApp.cpp
 * Purpose:   Code for Application Class
 * Author:    ofix (981326632@qq.com)
 * Created:   2019-08-12
 * Copyright: ofix (http://www.xiaocaihong.com.cn)
 * License:
 **************************************************************/

#include "sniperApp.h"
#include "core/Global.h"
#include "core/SpiderManager.h"

#include "lib/thread_pool/ThreadPool.h"

//(*AppHeaders
#include "sniperMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(sniperApp);

bool sniperApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        sniperFrame* Frame = new sniperFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    ThreadPool* pThreadPool = new ThreadPool();
    pThreadPool->Run();
    return wxOK;

}
