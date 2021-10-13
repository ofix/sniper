#ifndef SHARELISTDIALOG_H
#define SHARELISTDIALOG_H

//(*Headers(shareListDialog)
#include <wx/dialog.h>
//*)

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
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
