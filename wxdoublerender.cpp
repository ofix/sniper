#include "wxdoublerender.h"

wxDoubleRender::wxDoubleRender(wxDataViewCellMode mode): wxDataViewCustomRenderer("double", mode, wxALIGN_CENTER)
{
    //ctor
}

wxDoubleRender::~wxDoubleRender()
{
    //dtor
}



bool wxDoubleRender::Render( wxRect rect, wxDC *dc, int state )
{
    dc->SetBrush( *wxBLACK_BRUSH );
    dc->DrawRectangle( rect.GetTopLeft(),rect.GetSize());
        wxString strData =wxString::Format("%.2f",m_value);
    wxRect textRect = wxRect(dc->GetTextExtent(strData)).CentreIn(rect);
    dc->SetTextForeground(wxColor(192,192,192));
    dc->DrawText(strData,textRect.GetTopLeft());
    RenderText(strData,
               0, // no offset
               wxRect(dc->GetTextExtent(strData)).CentreIn(rect),
               dc,
               state);
    return true;
}

bool wxDoubleRender::ActivateCell(const wxRect& WXUNUSED(cell),
                                  wxDataViewModel *WXUNUSED(model),
                                  const wxDataViewItem &WXUNUSED(item),
                                  unsigned int WXUNUSED(col),
                                  const wxMouseEvent *mouseEvent)
{
//    wxString position;
//    if ( mouseEvent )
//        position = wxString::Format("via mouse at %d, %d", mouseEvent->m_x, mouseEvent->m_y);
//    else
//        position = "from keyboard";
//    wxLogMessage("ShareRender ActivateCell() %s", position);
    return false;
}
wxSize wxDoubleRender::GetSize() const
{
    return GetView()->FromDIP(wxSize(160, 32));
}

bool wxDoubleRender::SetValue( const wxVariant &value )
{
    m_value = value.GetDouble();
    return true;
}
