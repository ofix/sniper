#ifndef WXSHARERENDER_H
#define WXSHARERENDER_H

#include <wx/dataview.h>
#include <wx/dc.h>
#include <wx/log.h>

class wxShareRender : public wxDataViewCustomRenderer
{
public:
    wxShareRender(wxDataViewCellMode mode);
    virtual ~wxShareRender();
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

    virtual bool HasEditorCtrl() const wxOVERRIDE
    {
        return true;
    }

    virtual wxWindow* CreateEditorCtrl(wxWindow* parent, wxRect labelRect, const wxVariant& value) wxOVERRIDE;

    virtual bool GetValueFromEditorCtrl(wxWindow* ctrl, wxVariant& value) wxOVERRIDE;

protected:

private:
    wxString m_value;
};

#endif // WXSHARERENDER_H
