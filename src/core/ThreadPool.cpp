#include "ThreadPool.h"

ThreadPool::ThreadPool(uint16_t size):m_size(size),m_msgLocker(m_msgSection)
{

}

ThreadPool::~ThreadPool()
{

}

/******************************************
 *@func create all the threads at this time
    this is a good time point.
 ******************************************/
bool ThreadPool::Run()
{

    if(m_size<=0){
        m_size = DEFAULT_THREAD_POOL_SIZE;
    }
    uint16_t cpu_cores = GetCpuCoreCount();
    if(cpu_cores >= m_size)
    {
        m_size = cpu_cores;
    }
    for(uint16_t i =0; i<m_size; i++){
        JobThread* pThread = new JobThread(this);
        if(!pThread->Run() != wxTHREAD_NO_ERROR){
            m_idleThreads.push_back(pThread);
        }else{
            m_errorNo = ERROR_THREAD_POOL_CREATE_FAILURE;
            m_errorMsg = wxT("线程池创建失败!");
            return false;
        }
    }
    return true;
}

uint16_t ThreadPool::GetCpuCoreCount() const
{
    return DEFAULT_THREAD_POOL_SIZE;
}

wxString ThreadPool::GetLastError()const
{
    return m_errorMsg;
}

bool ThreadPool::Destroy()
{
    return false;
}

uint16_t ThreadPool::GetSize() const
{
    return m_size;
}

bool ThreadPool::SetSize(uint16_t size)
{
    if(size > m_size){
        uint16_t count = size - m_size;
        for(uint16_t i=0; i<count; i++){
            JobThread* pThread = new JobThread(this);
            if(pThread->Run() == wxTHREAD_NO_ERROR){
                m_idleThreads.push_back(pThread);
            }
        }
        return true;
    }
    return false;
}

uint16_t ThreadPool::GetBusyThreadsCount() const
{
    return m_busyThreads.size();
}

uint16_t ThreadPool::GetIdleThreadsCount() const
{
    return m_idleThreads.size();
}

bool ThreadPool::PauseThread()
{
    return false;
}

bool ThreadPool::PushMessageToQueue(JobMessage& message)
{
    return false;
}

void ThreadPool::onTaskMsgPost(wxEvent& event)
{

}

void ThreadPool::onWorkerThreadPost(wxEvent& event)
{

}
