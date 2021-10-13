#include "shareListDialog.h"

//(*InternalHeaders(shareListDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(shareListDialog)
//*)

BEGIN_EVENT_TABLE(shareListDialog,wxDialog)
	//(*EventTable(shareListDialog)
	//*)
END_EVENT_TABLE()

shareListDialog::shareListDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(shareListDialog)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(504,450));
	//*)
}

shareListDialog::~shareListDialog()
{
	//(*Destroy(shareListDialog)
	//*)
}

