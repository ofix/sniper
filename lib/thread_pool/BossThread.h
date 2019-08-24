#ifndef BossThread_H
#define BossThread_H
#include <wx/thread.h>
#include <wx/thread.h>
#include <wx/vector.h>

class ThreadPool;
class BossThread:public wxThread
{
    public:
        BossThread(ThreadPool* pThreadPool,wxThreadKind kind=wxTHREAD_DETACHED);
        virtual ~BossThread();
        virtual void* Entry();
        void NewTaskNotify();
        void ThreadIdleNotify(int threadId); // must lock and sync

    protected:
        void AssignTask(ThreadTask* task); // must lock and sync

        ThreadPool* m_pThreadPool;
        int m_awake; // UI main thread or worker thread would modify this variable
        wxVector<int> m_threadsState; // worker thread state; worker threads would modify it
        wxCriticalSection m_criticalSection;
};

#endif // BossThread_H
