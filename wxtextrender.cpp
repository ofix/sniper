#include "wxtextrender.h"

wxTextRender::wxTextRender(wxDataViewCellMode mode): wxDataViewCustomRenderer(wxT("string"), mode, wxALIGN_CENTER)
{
    //ctor
}

wxTextRender::~wxTextRender()
{
    //dtor
}


bool wxTextRender::Render( wxRect rect, wxDC *dc, int state )
{
    dc->SetBrush( *wxBLACK_BRUSH );
    wxRect textRect = wxRect(dc->GetTextExtent(m_value)).CentreIn(rect);
    dc->SetTextForeground(wxColor(192,192,192));
    dc->DrawText(m_value,textRect.GetTopLeft());
    return true;
}

wxSize wxTextRender::GetSize() const
{
   return GetView()->GetBestVirtualSize();
}

bool wxTextRender::SetValue( const wxVariant &value )
{
    m_value = value.GetString();
    return true;
}
