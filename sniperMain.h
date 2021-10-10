/***************************************************************
 * Name:      sniperMain.h
 * Purpose:   Defines Application Frame
 * Author:    ofix (981326632@qq.com)
 * Created:   2019-08-12
 * Copyright: ofix (http://www.xiaocaihong.com.cn)
 * License:
 **************************************************************/

#ifndef SNIPERMAIN_H
#define SNIPERMAIN_H

//(*Headers(sniperFrame)
#include <wx/frame.h>
class wxMenu;
class wxMenuBar;
class wxStatusBar;
//*)

class sniperFrame: public wxFrame
{
public:

    sniperFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~sniperFrame();

private:

    //(*Handlers(sniperFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnMenuItemSyncChinaStockList(wxCommandEvent& event);
    //*)

    //(*Identifiers(sniperFrame)
    static const long ID_MENUITEM1;
    static const long idMenuAbout;
    static const long ID_SYNC_STOCK_LIST_MENUITEM;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(sniperFrame)
    wxMenu* Menu3;
    wxMenuItem* MenuItemSyncChinaStockList;
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // SNIPERMAIN_H
