#ifndef CRAWLER_H
#define CRAWLER_H
#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/longlong.h>

class Spider
{
    public:
        Spider(wxString urlTarget);
        virtual ~Spider();
        virtual bool Run(); //spider begin to work
        wxLongLong GetUsedTime(); //used time for spider, in seconds
        virtual void* GetResult(); //Get all crawler data
    protected:
     wxString m_urlTarget; //target URL for spider
     bool m_bRun; //spider running or not
     wxDateTime m_timeStart; // crawler start time
     wxDateTime m_timeEnd; //crawler end time
};

#endif // CRAWLER_H
