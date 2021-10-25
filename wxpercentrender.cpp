#include "wxpercentrender.h"

wxPercentRender::wxPercentRender(wxDataViewCellMode mode): wxDataViewCustomRenderer(wxT("double"), mode, wxALIGN_CENTER)
{
    //ctor
}

wxPercentRender::~wxPercentRender()
{
    //dtor
}


bool wxPercentRender::Render( wxRect rect, wxDC *dc, int state )
{
    dc->SetBrush( *wxBLACK_BRUSH );
    wxColor textClr;
    if(m_value < 0.0f) {
        textClr.Set(0,255,0);
    } else {
        textClr.Set(255,0,0);
    }
    dc->DrawRectangle( rect.GetTopLeft(),rect.GetSize());
    wxString strData =wxString::Format("%.2f",m_value)+wxT("%");
    wxRect textRect = wxRect(dc->GetTextExtent(strData)).CentreIn(rect);
    dc->SetTextForeground(textClr);
    dc->DrawText(strData,textRect.GetTopLeft());
    return true;
}

wxSize wxPercentRender::GetSize() const
{
    return GetView()->GetBestVirtualSize();
}

bool wxPercentRender::SetValue( const wxVariant &value )
{
    if(value.IsType("double")) {
        m_value = value.GetDouble();
    } else {
        m_value = 0.0f;
    }

    return true;
}
