#include "ThreadPool.h"

ThreadPool::ThreadPool(uint16_t size):m_bRun(false),
                            m_size(size),
                            m_taskTodo(0)
{
    if(m_size <=0){
        m_size = wxThread::GetCPUCount();
    }
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
        wxCriticalSectionLocker locker(m_section);
        if(m_bRun){
            return false;
        }
        if(m_size<=0){
            m_size = DEFAULT_THREAD_POOL_SIZE;
        }
        uint16_t cpu_cores = wxThread::GetCPUCount();
        if(cpu_cores*2 <= m_size)
        {
            m_size = cpu_cores*2;
        }
        for(uint16_t i =0; i<m_size; i++){
            WorkerThread* pThread = new WorkerThread(this);
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
        return m_bRun;
    }catch(...){
        m_errorNo = ERROR_THREAD_SYSTEM_EXCEPTION;
        m_errorMsg = wxT("系统异常");
        return false;
    }
}

bool ThreadPool::IsRunning()
{
    wxCriticalSectionLocker locker(m_section);
    return m_bRun;
}

wxString ThreadPool::GetLastError()
{
    return m_errorMsg;
}

bool ThreadPool::Destroy()
{
    try{
        wxCriticalSectionLocker locker(m_section);
        if(m_idleThreads.size() != 0){
            for(size_t i=0; i<m_idleThreads.size(); i++){
                m_idleThreads[i]->Delete();
            }
        }
        if(m_busyThreads.size() != 0){
            for(size_t j=0;j<m_busyThreads.size();j++){
                m_busyThreads[j]->Delete();
            }
        }
    }catch(...){
        m_errorNo = ERROR_THREAD_SYSTEM_EXCEPTION;
        m_errorMsg = wxT("系统异常");
    }
    return true;
}

uint16_t ThreadPool::GetSize()
{
    wxMutexLocker locker(m_mutex);
    return m_size;
}

bool ThreadPool::ReSize(uint16_t size)
{
    if(size > m_size){
        uint16_t count = size - m_size;
        for(uint16_t i=0; i<count; i++){
            WorkerThread* pThread = new WorkerThread(this);
            if(pThread->Run() == wxTHREAD_NO_ERROR){
                m_idleThreads.push_back(pThread);
            }
        }
        return true;
    }
    return false;
}

uint16_t ThreadPool::GetBusyThreadsCount()
{
    wxMutexLocker locker(m_mutex);
    return m_busyThreads.size();
}

uint16_t ThreadPool::GetIdleThreadsCount()
{
    wxMutexLocker locker(m_mutex);
    return m_idleThreads.size();
}

bool ThreadPool::PauseThread()
{
    return false;
}

bool ThreadPool::PostTask(ThreadTask& task)
{
    try{
        wxCriticalSectionLocker enter(m_section);
        m_taskQueue.Post(task);
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
