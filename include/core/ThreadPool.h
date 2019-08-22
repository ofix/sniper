#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <wx/vector.h>
#include <wx/thread.h>
#include <wx/msgqueue.h>
#include <wx/event.h>

#include "JobMessage.h"
#include "JobThread.h"
#include "ManagerThread.h"

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
        uint16_t GetSize() const;
        bool SetSize(uint16_t size);
        bool IsRunning()const;

        uint16_t GetBusyThreadsCount() const;
        uint16_t GetIdleThreadsCount() const;

        bool PauseThread();
        bool PostMessage(JobMessage& message);
        wxString GetLastError()const;

        void onTaskMsgPost(wxEvent& event);
        void onWorkerThreadPost(wxEvent& event);
    protected:
        uint16_t GetCpuCoreCount()const;
    protected:
        uint16_t m_size;
        uint16_t m_taskTodo;
        wxVector<JobThread*> m_busyThreads;
        wxVector<JobThread*> m_idleThreads;
        ManagerThread m_threadManager;
        wxMessageQueue<JobMessage> m_msgQueue;
        wxCriticalSectionLocker m_msgLocker;
        wxCriticalSection m_msgSection;
        bool m_bRun;
        int m_errorNo;
        wxString m_errorMsg;

};

#endif // THREADPOOL_H
