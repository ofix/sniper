/***************************************************************
 * Name:      sniperMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    ofix (981326632@qq.com)
 * Created:   2019-08-12
 * Copyright: ofix (http://www.xiaocaihong.com.cn)
 * License:
 **************************************************************/

#include "sniperMain.h"
#include <wx/msgdlg.h>
#include "ui/KlineCtrl.h"

#include <iostream>
#include <string>
#include <wx/strconv.h>
#include <wx/textfile.h>
#include <lib/pinyin/PinYin.h>
#include <spider/IfengSpider.h>
#include <spider/BaiduPolyphoneSpider.h>
#include <test/All.h>

//(*InternalHeaders(sniperFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(sniperFrame)
const long sniperFrame::ID_MENUITEM1 = wxNewId();
const long sniperFrame::idMenuAbout = wxNewId();
const long sniperFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(sniperFrame,wxFrame)
    //(*EventTable(sniperFrame)
    //*)
END_EVENT_TABLE()

sniperFrame::sniperFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(sniperFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(0, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&sniperFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&sniperFrame::OnAbout);
    //*)

    // create day k line control
    KlineCtrl* pKlineCtrl = new KlineCtrl(wxT("600000"),this,wxID_ANY);
    pKlineCtrl->Show();

//    #define DEBUG_SPIDER
//    #ifdef DEBUG_SPIDER
//        BaiduPolyphoneSpider spider;
//        spider.Run();
//    #endif // DEBUG_SPIDER
    // Test::RunAll();
    // wxString 测试
//    wxCSConv gbkConv(wxFONTENCODING_CP936);
//    std::string str_gbk(gbkConv.cWX2MB(_T("z国"))); //gbk格式
//    std::string str_utf8("z国"); // utf8格式
//    std::wstring str_unicode(gbkConv.cWX2WC(_T("z国")));// unicode格式
//
//
//
//    std::cout<<"[str_gbk         ] = "<<str_gbk<<std::endl;
//    //std::cout<<"[str_utf8        ] = "<<str_utf8<<std::endl;
//    std::cout<<"[str_unicode     ] = "<<str_unicode<<std::endl;
//    std::cout<<"[str_gbk size    ] = "<<str_gbk.size()<<" byte"<<std::endl;
//    std::cout<<"[str_utf8 size   ] = "<<str_utf8.size()<<" byte"<<std::endl;
//    std::cout<<"[str_unicode size] = "<<str_unicode.size()*2<<" byte"<<std::endl;
//    std::cout<<"[str_gbk HEX     ] = "<<stringToHex(str_gbk)<<std::endl;
//    std::cout<<"[str_utf8 HEX    ] = "<<stringToHex(str_utf8)<<std::endl;
//    std::wcout<<"[str_unicode HEX ] = "<<wstringToHex(str_unicode)<<std::endl;
    // generate gb2312 map
//    wxTextFile mapFile;
//    wxString fileName = getExecDir()+"gb2312.dat";
//    if(!mapFile.Open(fileName)){
//        mapFile.Create(fileName);
//    }
//    mapFile.Clear();
//    wxString sline = uint16ToHex(0xB0A0)+",";
//    for(uint16_t i=0xB0A1; i<=0xF7FF; i++){
//        sline += uint16ToHex(i)+",";
//        if(i%16 == 15){
//            mapFile.AddLine(sline.Left(sline.length()-1));
//            sline = "";
//        }
//    }
//    mapFile.Write();
//    mapFile.Close();
    //加载网络GB2312对照表

    //查询所有股票代码
    //获取股票代码的拼音首字母，并写入文件
    // 格式: 股票代号 股票名称 股票简写
//    IfengSpider spider;
//    spider.Run();
//    wxVector<ShareBrief> data = spider.GetAllShares();
//    //输出到文件
//    wxString path = getExecDir()+wxT("shares.csv");
//    wxTextFile shareFile(path);
//    if(!shareFile.Exists()){
//        shareFile.Create();
//    }
//    shareFile.Open();
//    wxVector<ShareBrief>::const_iterator it;
//    wxString line = wxT("");
//    PinYin py;
//    for(it = data.begin(); it!=data.end(); ++it){
//        line = it->code+wxT(",");
//        line += it->name+wxT(",");
//        line += py.FirstLetter(it->name);
//        shareFile.AddLine(line);
//        line = wxT("");
//    }
//    shareFile.Write();
//    shareFile.Close();
}

sniperFrame::~sniperFrame()
{
    //(*Destroy(sniperFrame)
    //*)
}

void sniperFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void sniperFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
