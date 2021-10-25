#include "wxdoublerender.h"

wxDoubleRender::wxDoubleRender(wxDataViewCellMode mode): wxDataViewCustomRenderer(wxT("double"), mode, wxALIGN_CENTER)
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
    return true;
}

wxSize wxDoubleRender::GetSize() const
{
    return GetView()->GetBestVirtualSize();
}

bool wxDoubleRender::SetValue( const wxVariant &value )
{
    m_value = value.GetDouble();
    return true;
}
