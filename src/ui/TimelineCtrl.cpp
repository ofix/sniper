#include "TimelineCtrl.h"

TimelineCtrl::TimelineCtrl(wxVector& timeline,wxString code),
                    m_timeline(timeline),m_shareCode(code),m_offset(0)
                    ,m_lastAverage(0)
{
    //ctor
}

TimelineCtrl::~TimelineCtrl()
{
    //dtor
}

void TimelineCtrl::UpdateAveragePrice()
{
    wxVector<TimelineItem>::const_iterator it;
    double total = 0;
    for(it = m_timeline.begin()+m_offset,it != m_timeline.end(); it++)
    {
        total+=it->price;
    }
    m_average = (m_lastAverage*m_offset+total)/m_timeline.size();
}

void TimelineCtrl::AddNewData(wxVector& timeline)
{
    wxVector<TimelineItem>::const_iterator it;
    for(it = timeline.begin(); it != timeline.end(); ++it){
        m_timeline.push_back(*it);
    }
}


