#ifndef WorkerThread_H
#define WorkerThread_H
#include <wx/thread.h>

class ThreadPool;
class WorkerThread:public wxThread
{
    public:
        WorkerThread(ThreadPool* pThreadPool,wxThreadKind kind=wxTHREAD_DETACHED);
        virtual ~WorkerThread();
        virtual void* Entry();

    protected:
        ThreadPool* m_pThreadPool;
};

#endif // WorkerThread_H
