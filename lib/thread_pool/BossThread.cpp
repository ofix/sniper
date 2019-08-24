#include "BossThread.h"
#include "ThreadPool.h"
BossThread::BossThread(ThreadPool* pThreadPool,wxThreadKind kind):wxThread(kind)
                        ,m_pThreadPool(pThreadPool)
{
    //ctor
}

BossThread::~BossThread()
{
    //dtor
    //
    while(1){
        // 等待awake 醒来

    }
}

void* BossThread::Entry()
{
    while(1)
    {
        //检查空闲线程
        m_threadsState::const_iterator it;
        for(it = m_threadsState.begin(); it != m_threadsState.end(); ++it)
        {
            if(m_threadsState[i] == 1){
                m_pThreadPool.m_idleThreads.push_back(m_threadsState[i]);
            }
        }
    }
}

void BossThread::NewTaskNotify()
{
   wxCriticalSectionLocker enter(m_criticalSection);
   m_awake |= 8;
}

void BossThread::ThreadIdleNotify()
{
    wxCriticalSectionLocker enter(m_criticalSection);
    m_awake |= 1;
}

 void BossThread::AssignTask(ThreadTask* task)
 {

 }
