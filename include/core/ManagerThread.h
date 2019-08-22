#ifndef MANAGERTHREAD_H
#define MANAGERTHREAD_H
#include <wx/thread.h>

class ManagerThread:public wxThread
{
    public:
        ManagerThread(wxThreadKind kind=wxTHREAD_DETACHED);
        virtual ~ManagerThread();
        virtual void* Entry();

    protected:
};

#endif // MANAGERTHREAD_H
