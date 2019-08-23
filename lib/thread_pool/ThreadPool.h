#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <wx/vector.h>
#include <wx/thread.h>
#include <wx/msgqueue.h>
#include <wx/event.h>

#include "ThreadTask.h"
#include "WorkerThread.h"
#include "BossThread.h"

/***********************************
 *@class ThreadPool
 *@todo a flexible implementation
 *@author tom song
 ***********************************/
 #define DEFAULT_THREAD_POOL_SIZE 8
 #define ERROR_THREAD_POOL_CREATE_FAILURE 201
 #define ERROR_THREAD_SYSTEM_EXCEPTION 202
class ThreadPool
{
    public:
        ThreadPool(uint16_t size = DEFAULT_THREAD_POOL_SIZE);
        virtual ~ThreadPool();
        bool Run();
        bool Destroy();
        uint16_t GetSize();
        bool ReSize(uint16_t size);
        bool IsRunning();

        uint16_t GetBusyThreadsCount();
        uint16_t GetIdleThreadsCount();

        bool PauseThread();
        bool PostTask(ThreadTask& task);
        wxString GetLastError();

        void onTaskMsgPost(wxEvent& event);
        void onWorkerThreadPost(wxEvent& event);
    private:
        bool m_bRun;
        uint16_t m_size;
        uint16_t m_taskTodo;
        int m_errorNo;
        wxString m_errorMsg;
        wxVector<WorkerThread*> m_busyThreads;
        wxVector<WorkerThread*> m_idleThreads;
        BossThread m_bossThread;
        wxMessageQueue<ThreadTask> m_taskQueue;
        wxCriticalSection m_section;
        wxMutex m_mutex;
};

#endif // THREADPOOL_H
