#ifndef WorkerThread_H
#define WorkerThread_H
#include <wx/thread.h>
#include "ThreadTask.h"

#define SIGNAL_DESTROY 0x00000001
#define SIGNAL_DISCARD_TASK 0x00000010
#define SIGNAL_SWAP_TASK 0x00001000
#define SIGNAL_BACKUP_TASK 0x00010000
#define SIGNAL_TASK_URGENT 0x00100000

#define SIGNALS (SIGNAL_DESTROY|SIGNAL_DISCARD_TASK \
                    |SIGNAL_SWAP_TASK|SIGNAL_BACKUP_TASK|SIGNAL_TASK_URGENT)
#define CHECK_FOR(SIGNAL) ((~SIGNALS) & SIGNAL)

#define WORKER_THREAD_SLEEP 2
#define WORKER_THREAD_RUNNING 1
#define WORKER_THREAD_IDLE 0
#define WORKER_THREAD_DESTROY -1

class BossThread;
class WorkerThread:public wxThread
{
    public:
        WorkerThread(BossThread* pBossThread,wxThreadKind kind=wxTHREAD_DETACHED);
        virtual ~WorkerThread();
        virtual void* Entry();
        int GetStatus();
        void SetTask(ThreadTask* pTask);

    protected:
        BossThread* m_pBossThread;
        ThreadTask* m_pTask;
        int m_status;
        wxMutex m_mutex;
};

#endif // WorkerThread_H
