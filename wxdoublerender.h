#ifndef WXDOUBLERENDER_H
#define WXDOUBLERENDER_H


#include <wx/dataview.h>
#include <wx/dc.h>
#include <wx/log.h>
#include "util/Helper.h"

class wxDoubleRender : public wxDataViewCustomRenderer
{
public:
    wxDoubleRender(wxDataViewCellMode mode);
    virtual ~wxDoubleRender();
    virtual bool Render( wxRect rect, wxDC *dc, int state ) wxOVERRIDE;
    virtual bool ActivateCell(const wxRect& WXUNUSED(cell),
                              wxDataViewModel *WXUNUSED(model),
                              const wxDataViewItem &WXUNUSED(item),
                              unsigned int WXUNUSED(col),
                              const wxMouseEvent *mouseEvent) wxOVERRIDE;
    virtual wxSize GetSize() const wxOVERRIDE;
    virtual bool GetValue( wxVariant &WXUNUSED(value) ) const wxOVERRIDE
    {
        return true;
    }

    virtual bool SetValue( const wxVariant &value ) wxOVERRIDE;
protected:

private:
    double m_value;
};

#endif // WXDOUBLERENDER_H
