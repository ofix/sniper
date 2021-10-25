#include "wxchineseuintrender.h"

wxChineseUintRender::wxChineseUintRender(wxDataViewCellMode mode): wxDataViewCustomRenderer(wxT("ulonglong"), mode, wxALIGN_CENTER)
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

wxSize wxChineseUintRender::GetSize() const
{
    return GetView()->GetBestVirtualSize();
}

bool wxChineseUintRender::SetValue( const wxVariant &value )
{
    m_value = static_cast<uint64_t>(value.GetULongLong().GetValue());
    return true;
}

