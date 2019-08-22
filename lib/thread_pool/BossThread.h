#ifndef BossThread_H
#define BossThread_H
#include <wx/thread.h>

class BossThread:public wxThread
{
    public:
        BossThread(wxThreadKind kind=wxTHREAD_DETACHED);
        virtual ~BossThread();
        virtual void* Entry();

    protected:
};

#endif // BossThread_H
