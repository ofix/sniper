#ifndef TIMELINECTRL_H
#define TIMELINECTRL_H
#include <wx/vector.h>
#include <core/Stock.h>
#include <wx/dc.h>

class TimelineCtrl
{
    public:
        TimelineCtrl(wxVector& timeline,wxString code);

        virtual ~TimelineCtrl();
        void UpdateAveragePrice();
        void AddNewData(wxVector& timeline);
        void DrawTimeline(wxDC* pDC);
        void DrawAveragePriceLine(wxDC* pDC);

    protected:
        wxVector<TimelineItem> m_timeline;
        wxVector<double> m_average
        int m_offset; // helper for average price calculation
        int m_lastAverage;
        wxString m_shareCode;

};

#endif // TIMELINECTRL_H
