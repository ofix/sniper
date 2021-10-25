#include "wxintrender.h"

wxIntRender::wxIntRender(wxDataViewCellMode mode): wxDataViewCustomRenderer(wxT("long"), mode, wxALIGN_CENTER)
{
    //ctor
}

wxIntRender::~wxIntRender()
{
    //dtor
}

bool wxIntRender::Render( wxRect rect, wxDC *dc, int state )
{
    dc->SetBrush( *wxBLACK_BRUSH);

    dc->DrawRectangle( rect.GetTopLeft(),rect.GetSize());
    wxString strData = wxString::Format("%d",m_value);
    wxRect textRect = wxRect(dc->GetTextExtent(strData)).CentreIn(rect);
    dc->SetTextForeground(wxColor(192,192,192));
    dc->DrawText(strData,textRect.GetTopLeft());
    return true;
}

//bool wxIntRender::ActivateCell(const wxRect& WXUNUSED(cell),
//                               wxDataViewModel *WXUNUSED(model),
//                               const wxDataViewItem &WXUNUSED(item),
//                               unsigned int WXUNUSED(col),
//                               const wxMouseEvent *mouseEvent)
//{
////    wxString position;
////    if ( mouseEvent )
////        position = wxString::Format("via mouse at %d, %d", mouseEvent->m_x, mouseEvent->m_y);
////    else
////        position = "from keyboard";
////    wxLogMessage("ShareRender ActivateCell() %s", position);
//    return true;
//}
wxSize wxIntRender::GetSize() const
{
    return GetView()->GetBestVirtualSize();
}

bool wxIntRender::SetValue( const wxVariant &value )
{
    m_value = value.GetInteger();
    return true;
}
