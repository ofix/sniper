#include "TimelineCtrl.h"
#include <wx/dc.h>
#include <wx/dcbuffer.h>

TimelineCtrl::TimelineCtrl()
{

}

TimelineCtrl::TimelineCtrl(wxVector<TimelineItem>& timeline,wxString code)
                    :m_timeline(timeline)
                    ,m_shareCode(code)
                    ,m_offset(0)
                    ,m_lastAverage(0)
{
    //ctor
}

TimelineCtrl::~TimelineCtrl()
{
    //dtor
}

//以下函数实现必须写，否则会爆错误 undefined reference to 'vtable for TimelineCtrl'
wxBEGIN_EVENT_TABLE(TimelineCtrl, wxControl)
    EVT_PAINT(TimelineCtrl::OnPaint)
wxEND_EVENT_TABLE()
wxIMPLEMENT_DYNAMIC_CLASS(TimelineCtrl, wxControl)

void TimelineCtrl::UpdateAveragePrice()
{
    wxVector<TimelineItem>::const_iterator it;
    double total = 0;
    for(it = m_timeline.begin()+m_offset;it != m_timeline.end(); it++)
    {
        total+=it->price;
    }
    m_average = (m_lastAverage*m_offset+total)/m_timeline.size();
}

void TimelineCtrl::AddNewData(wxVector<TimelineItem>& timeline)
{
    wxVector<TimelineItem>::const_iterator it;
    for(it = timeline.begin(); it != timeline.end(); ++it){
        m_timeline.push_back(*it);
    }
}

void TimelineCtrl::OnPaint(wxPaintEvent& event)
{
     //自动双缓冲，如果系统默认支持双缓冲，会调用系统，否则使用位图实现，
     //必须在 Create之前调用 SetBackgroundStyle(wxBG_STYLE_PAINT);
    wxAutoBufferedPaintDC dc(this);
    //绘制黑色背景
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();
    DrawTimeline(&dc);
    DrawAveragePriceLine(&dc);
}

void TimelineCtrl::DrawTimeline(wxDC* pDC)
{

}

void TimelineCtrl::DrawAveragePriceLine(wxDC* pDC)
{

}


