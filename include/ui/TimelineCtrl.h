#ifndef TIMELINECTRL_H
#define TIMELINECTRL_H
#include <wx/vector.h>
#include <core/Stock.h>

class TimelineCtrl
{
    public:
        TimelineCtrl(wxVector& timeline,wxString code);

        virtual ~TimelineCtrl();
        void

    protected:
        wxVector<TimelineItem> m_timeline;
        wxVector<double> m_average
        int m_offset; // helper for average price calculation
        wxString m_shareCode;

};

#endif // TIMELINECTRL_H
