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
#include <spider/EastMoneySpider.h>
#include <spider/BaiduPolyphoneSpider.h>
#include <test/All.h>
#include <vector>

//(*InternalHeaders(sniperFrame)
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f ) {
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
const long sniperFrame::ID_LISTCTRL_STOCK = wxNewId();
const long sniperFrame::ID_MENUITEM1 = wxNewId();
const long sniperFrame::idMenuAbout = wxNewId();
const long sniperFrame::ID_SYNC_STOCK_LIST_MENUITEM = wxNewId();
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

    Create(0, wxID_ANY, _T("股票嗅探器"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(910,541));
    m_listCtrlStock = new wxListCtrl(this, ID_LISTCTRL_STOCK, wxPoint(184,192), wxDefaultSize, wxLC_REPORT|wxLC_HRULES|wxVSCROLL|wxHSCROLL|wxALWAYS_SHOW_SB, wxDefaultValidator, _T("ID_LISTCTRL_STOCK"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _T("Quit\tAlt-F4"), _T("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _T("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _T("About\tF1"), _T("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _T("Help"));
    Menu3 = new wxMenu();
    MenuItemSyncChinaStockList = new wxMenuItem(Menu3, ID_SYNC_STOCK_LIST_MENUITEM, _T("沪深股票列表\tF2"), _T("同步沪深股票列表"), wxITEM_NORMAL);
    Menu3->Append(MenuItemSyncChinaStockList);
    MenuBar1->Append(Menu3, _T("数据同步"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&sniperFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&sniperFrame::OnAbout);
    Connect(ID_SYNC_STOCK_LIST_MENUITEM,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&sniperFrame::OnMenuItemSyncChinaStockList);
    //*)

    this->initListCtrlStock();
    // create day k line control
//    KlineCtrl* pKlineCtrl = new KlineCtrl(wxT("600000"),this,wxID_ANY);
//    pKlineCtrl->Show();

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

// TODO: synchronize all stock quotes in China market
// format as: stock code | stock name | stack Pinyin abbreviation
// save file name: shares.csv
void sniperFrame::OnMenuItemSyncChinaStockList(wxCommandEvent& event)
{
    MenuItemSyncChinaStockList->Enable(false);
    IfengSpider spider;
    spider.Run();
    wxVector<ShareBrief> data = spider.GetAllShares();
    wxString path = getExecDir()+wxT("shares.csv");
    wxTextFile shareFile(path);
    if(!shareFile.Exists()) {
        shareFile.Create();
    }
    shareFile.Open();
    shareFile.Clear(); // clear old stock list data
    wxVector<ShareBrief>::const_iterator it;
    wxString line = wxT("");
    PinYin py;
    for(it = data.begin(); it!=data.end(); ++it) {
        line = it->code+wxT(",");
        line += it->name+wxT(",");
        line += py.FirstLetter(it->name);
        shareFile.AddLine(line);
        line = wxT("");
    }
    shareFile.Write();
    shareFile.Close();
    MenuItemSyncChinaStockList->Enable(true);
    wxMessageBox(wxT("同步沪深股票完成!"),wxT("数据同步"));
}


bool sniperFrame::initListCtrlStock()
{
    EastMoneySpider spiderEastMoney;
    bool bRet = spiderEastMoney.Run();
    std::vector<ShareDetail> allShares;
    if(bRet) {
        allShares= spiderEastMoney.GetAllShares();
    }

    std::vector<wxString> headers;
    headers.push_back(wxT("代码"));
    headers.push_back(wxT("名称"));
    headers.push_back(wxT("最新价"));
    headers.push_back(wxT("涨跌幅"));
    headers.push_back(wxT("涨跌额"));
    headers.push_back(wxT("成交量(手)"));
    headers.push_back(wxT("成交额"));
    headers.push_back(wxT("振幅"));
    headers.push_back(wxT("最高"));
    headers.push_back(wxT("最低"));
    headers.push_back(wxT("今开"));
    headers.push_back(wxT("量比"));
    headers.push_back(wxT("换手率"));
    headers.push_back(wxT("市盈率(动态)"));
    headers.push_back(wxT("市净率"));
    headers.push_back(wxT("总市值"));
    headers.push_back(wxT("流通市值"));
    for (unsigned i=0; i<headers.size(); i++) {
        m_listCtrlStock->InsertColumn(i,  headers[i]);
    }

    if(bRet) {
        m_listCtrlStock->Hide();
        for(unsigned i=0; i<allShares.size(); i++) {
            ShareDetail share = allShares[i];
            m_listCtrlStock->InsertItem(i,wxT(""));
            m_listCtrlStock->SetItem(i,0,share.code);
            m_listCtrlStock->SetItem(i,1,share.name);
            m_listCtrlStock->SetItem(i,2,wxString::Format("%.2f",share.price_now));
            m_listCtrlStock->SetItem(i,3,wxString::Format("%.2f",share.change_rate)+wxT("%"));
            m_listCtrlStock->SetItem(i,4,wxString::Format("%.2f",share.change_amount));
            m_listCtrlStock->SetItem(i,5,FormatDataWithUint(share.volume));
            m_listCtrlStock->SetItem(i,6,FormatDataWithUint(share.amount));
            m_listCtrlStock->SetItem(i,7,wxString::Format("%.2f",share.amplitude)+wxT("%"));
            m_listCtrlStock->SetItem(i,8,wxString::Format("%.2f",share.price_max));
            m_listCtrlStock->SetItem(i,9,wxString::Format("%.2f",share.price_min));
            m_listCtrlStock->SetItem(i,10,wxString::Format("%.2f",share.price_open));
            m_listCtrlStock->SetItem(i,11,wxString::Format("%.2f",share.qrr));
            m_listCtrlStock->SetItem(i,12,wxString::Format("%.2f",share.turnover_rate)+wxT("%"));
            m_listCtrlStock->SetItem(i,13,wxString::Format("%.2f",share.pe));
            m_listCtrlStock->SetItem(i,14,wxString::Format("%.2f",share.pb));
            m_listCtrlStock->SetItem(i,15,FormatDataWithUint(share.total_capital));
            m_listCtrlStock->SetItem(i,16,FormatDataWithUint(share.trade_capital));
        }
        m_listCtrlStock->Show();
    }

//    wxArrayInt order(3);
//    order[0] = 2;
//    order[1] = 0;
//    order[2] = 1;
//    m_listCtrlStock->SetColumnsOrder(order);

    return true;
}
