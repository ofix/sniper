#include "wxchineseuintrender.h"

wxChineseUintRender::wxChineseUintRender(wxDataViewCellMode mode): wxDataViewCustomRenderer("long", mode, wxALIGN_CENTER)
{
    //ctor
}

wxChineseUintRender::~wxChineseUintRender()
{
    //dtor
}



bool wxChineseUintRender::Render( wxRect rect, wxDC *dc, int state )
{
    dc->SetBrush( *wxBLACK_BRUSH );
    dc->DrawRectangle( rect.GetTopLeft(),rect.GetSize());
    wxString strData = FormatDataWithUint(m_value);
    wxRect textRect = wxRect(dc->GetTextExtent(strData)).CentreIn(rect);
    dc->SetTextForeground(wxColor(192,192,192));
    dc->DrawText(strData,textRect.GetTopLeft());
    return true;
}

bool wxChineseUintRender::ActivateCell(const wxRect& WXUNUSED(cell),
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
wxSize wxChineseUintRender::GetSize() const
{
    return GetView()->FromDIP(wxSize(160, 32));
}

bool wxChineseUintRender::SetValue( const wxVariant &value )
{
    m_value = static_cast<uint64_t>(value.GetLong());
    return true;
}

