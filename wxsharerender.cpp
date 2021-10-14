#include "wxsharerender.h"

wxShareRender::wxShareRender(wxDataViewCellMode mode): wxDataViewCustomRenderer("shareRender", mode, wxALIGN_CENTER)
{
    //ctor
}

wxShareRender::~wxShareRender()
{
    //dtor
}


bool wxShareRender::Render( wxRect rect, wxDC *dc, int state )
{
    dc->SetBrush( *wxLIGHT_GREY_BRUSH );
    dc->SetPen( *wxTRANSPARENT_PEN );

    rect.Deflate(2);
    dc->DrawRoundedRectangle( rect, 5 );

    RenderText(m_value,
               0, // no offset
               wxRect(dc->GetTextExtent(m_value)).CentreIn(rect),
               dc,
               state);
    return true;
}

bool wxShareRender::ActivateCell(const wxRect& WXUNUSED(cell),
                                 wxDataViewModel *WXUNUSED(model),
                                 const wxDataViewItem &WXUNUSED(item),
                                 unsigned int WXUNUSED(col),
                                 const wxMouseEvent *mouseEvent)
{
    wxString position;
    if ( mouseEvent )
        position = wxString::Format("via mouse at %d, %d", mouseEvent->m_x, mouseEvent->m_y);
    else
        position = "from keyboard";
    wxLogMessage("ShareRender ActivateCell() %s", position);
    return false;
}
wxSize wxShareRender::GetSize() const
{
    return GetView()->FromDIP(wxSize(120, 20));
}

bool wxShareRender::SetValue( const wxVariant &value )
{
    m_value = value.GetString();
    return true;
}

