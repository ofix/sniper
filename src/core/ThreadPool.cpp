#include "ThreadPool.h"

ThreadPool::ThreadPool(uint16_t size = DEFAULT_THREAD_POOL_SIZE):m_size(size)
{

}

ThreadPool::~ThreadPool()
{

}

bool ThreadPool::Run()
{
    return false;
}

bool ThreadPool::Destroy()
{

}

uint16_t ThreadPool::GetSize() const
{
    return m_size;
}

bool ThreadPool::SetSize(uint16_t size)
{
    m_size = size;
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

bool ThreadPool::PushMessageToQueue(TaskMessage& message)
{
    return false;
}

void ThreadPool::onTaskMsgPost(wxEvent& event)
{

}

void ThreadPool::onWorkerThreadPost(wxEvent& event)
{

}
