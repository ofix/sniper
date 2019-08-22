#include "ThreadPool.h"

ThreadPool::ThreadPool(uint16_t size):m_size(size),m_msgLocker(m_msgSection),m_bRun(false)
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
    try{
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
            if(pThread->Run() != wxTHREAD_NO_ERROR){
                Destroy();
                m_bRun = false;
                m_errorNo = ERROR_THREAD_POOL_CREATE_FAILURE;
                m_errorMsg = wxT("线程池创建失败!");
                return false;
            }else{
                m_idleThreads.push_back(pThread);
            }
        }
        m_bRun = true;
        return true;
    }catch(...){
        m_errorNo = ERROR_THREAD_SYSTEM_EXCEPTION;
        m_errorMsg = wxT("系统异常");
        return false;
    }
    return true;
}

bool ThreadPool::IsRunning()const
{
    return m_bRun;
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
    try{
        if(m_idleThreads.size() == 0){
            return false;
        }
        if(m_busyThreads.size() == 0){
            return false;
        }

    }catch(...){
        m_errorNo = ERROR_THREAD_SYSTEM_EXCEPTION;
        m_errorMsg = wxT("系统异常");
    }
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

bool ThreadPool::PostMessage(JobMessage& message)
{
    try{

        return true;
    }catch(...){
        return false;
    }
}

void ThreadPool::onTaskMsgPost(wxEvent& event)
{

}

void ThreadPool::onWorkerThreadPost(wxEvent& event)
{

}
