#include "wxpercentrender.h"

wxPercentRender::wxPercentRender(wxDataViewCellMode mode): wxDataViewCustomRenderer("double", mode, wxALIGN_CENTER)
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
    RenderText(strData,
               0, // no offset
               wxRect(dc->GetTextExtent(strData)).CentreIn(rect),
               dc,
               state);
    return true;
}

bool wxPercentRender::ActivateCell(const wxRect& WXUNUSED(cell),
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
wxSize wxPercentRender::GetSize() const
{
    return GetView()->FromDIP(wxSize(160, 32));
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
