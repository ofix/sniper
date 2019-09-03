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

//#include "lib/thread_pool/ThreadPool.h"
#include "ui/KlineCtrl.h"

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
    // 5.map stock brief data to a trie tree for search
    // 6.check out if all shares day K line data has download? if not download from finance.163.com
    // 7.checkout the daytime,if it's week day, start start threads to monitor share real-time price from website
    // 8.create app data.
    // 9.listen and wait user's input, if double click,read day kline data from csv file and display it.
    // 10. different task use different class to implement.
    //wxOpen("config.ini");

//    ThreadPool* pThreadPool = new ThreadPool();
//    pThreadPool->Run();

    return wxOK;

}
