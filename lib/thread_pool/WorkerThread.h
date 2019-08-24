#ifndef WorkerThread_H
#define WorkerThread_H
#include <wx/thread.h>

#define CHECK_FOR(SIGNAL) ((~SIGNALS) & SIGNAL)
#define SIGNAL_DESTROY 0x00000001
#define SIGNAL_DISCARD_TASK 0x00000010
#define SIGNAL_SWAP_TASK 0x00001000
#define SIGNAL_BACKUP_TASK 0x00010000

class BossThread;
class WorkerThread:public wxThread
{
    public:
        WorkerThread(BossThread* pBossThread,wxThreadKind kind=wxTHREAD_DETACHED);
        virtual ~WorkerThread();
        virtual void* Entry();

    protected:
        BossThread* m_pBossThread;
        ThreadTask* m_pTask;
};

#endif // WorkerThread_H
