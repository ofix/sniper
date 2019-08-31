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

    // 1.define config default values in .exe
    // 2.create thread pool
    // 3.read config file, If not exist,create one
    // 4.get all stock brief information from stock.data.ini, if not exists,
    //   use a detached thread from thread pool to download from Ifeng Website.
    //
    wxOpen("config.ini",)

    ThreadPool* pThreadPool = new ThreadPool();
    pThreadPool->Run();
    return wxOK;

}
