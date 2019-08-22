#ifndef JOBTHREAD_H
#define JOBTHREAD_H
#include <wx/thread.h>

class ThreadPool;
class JobThread:public wxThread
{
    public:
        JobThread(ThreadPool* pThreadPool,wxThreadKind kind=wxTHREAD_DETACHED);
        virtual ~JobThread();
        virtual void* Entry();

    protected:
        ThreadPool* m_pThreadPool;
};

#endif // JOBTHREAD_H
