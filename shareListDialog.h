#ifndef SHARELISTDIALOG_H
#define SHARELISTDIALOG_H

//(*Headers(shareListDialog)
#include <wx/dialog.h>
//*)

#include <wx/dataview.h>
#include <vector>
#include <spider/EastMoneySpider.h>
#include "wxchineseuintrender.h"
#include "wxdoublerender.h"
#include "wxpercentrender.h"
#include "wxintrender.h"

enum Identifiers {
    IDDATAVIEW = wxID_HIGHEST + 1
};

class shareListDialog: public wxDialog
{
public:

    shareListDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
    virtual ~shareListDialog();

    //(*Declarations(shareListDialog)
    //*)

protected:

    //(*Identifiers(shareListDialog)
    //*)

private:

    //(*Handlers(shareListDialog)
    void OnInit(wxInitDialogEvent& event);
    //*)

    wxDataViewListCtrl* m_pDataView;

    DECLARE_EVENT_TABLE()
};

#endif
