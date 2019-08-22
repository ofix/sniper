#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <wx/vector.h>
#include <wx/thread.h>
#include <wx/msgqueue.h>
#include "TaskMessage.h"

/***********************************
 *@class ThreadPool
 *@todo a flexible implementation
 *@author tom song
 ***********************************/
 #define DEFAULT_THREAD_POOL_SIZE 8
class ThreadPool
{
    public:
        ThreadPool(uint16_t size = DEFAULT_THREAD_POOL_SIZE);
        virtual ~ThreadPool();
        bool Run();
        bool Destroy();
        uint16_t GetSize() const;
        bool SetSize(uint16_t size);

        uint16_t GetBusyThreadsCount() const;
        uint16_t GetIdleThreadsCount() const;

        bool PauseThread();
        bool PushMessageToQueue(TaskMessage& message);

        void onTaskMsgPost(wxEvent& event);
        void onWorkerThreadPost(wxEvent& event);
    protected:
        uint16_t m_size;
        uint16_t m_taskTodo;
        wxList<wxThread> m_busyThreads;
        wxList<wxThread> m_idleThreads;
        wxThread m_threadManager;
        wxMessageQueue m_msgQueue;
        wxCriticalSectionLocker m_msgLocker;

};

#endif // THREADPOOL_H
