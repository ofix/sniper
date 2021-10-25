#ifndef WXTEXTRENDER_H
#define WXTEXTRENDER_H

#include <wx/dataview.h>
#include <wx/dc.h>
#include <wx/log.h>
#include "util/Helper.h"


class wxTextRender : public wxDataViewCustomRenderer
{
    public:
    wxTextRender(wxDataViewCellMode mode);
    virtual ~wxTextRender();
    virtual bool Render( wxRect rect, wxDC *dc, int state ) wxOVERRIDE;
    virtual wxSize GetSize() const wxOVERRIDE;
    virtual bool GetValue( wxVariant &WXUNUSED(value) ) const wxOVERRIDE
    {
        return true;
    }

    virtual bool SetValue( const wxVariant &value ) wxOVERRIDE;
    protected:

    private:
        wxString m_value;
};

#endif // WXTEXTRENDER_H
