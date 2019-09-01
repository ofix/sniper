#ifndef TIMELINECTRL_H
#define TIMELINECTRL_H
#include <wx/vector.h>
#include <core/Stock.h>
#include <wx/dc.h>
#include <wx/control.h>

class TimelineCtrl:public wxControl
{
    public:
        wxDECLARE_DYNAMIC_CLASS(TimelineCtrl);
        wxDECLARE_EVENT_TABLE();
        wxDECLARE_NO_COPY_CLASS(TimelineCtrl);

        TimelineCtrl();
        TimelineCtrl(wxVector<TimelineItem>& timeline,wxString code);

        virtual ~TimelineCtrl();
        void UpdateAveragePrice();
        void AddNewData(wxVector<TimelineItem>& timeline);
        void DrawTimeline(wxDC* pDC);
        void DrawAveragePriceLine(wxDC* pDC);
        //event callback functions
        void OnPaint(wxPaintEvent& event);
    protected:
        wxVector<TimelineItem> m_timeline;
        wxVector<double> m_average;
        int m_offset; // helper for average price calculation
        int m_lastAverage;
        wxString m_shareCode;
};

#endif // TIMELINECTRL_H
