#include "BossThread.h"
#include "ThreadPool.h"
BossThread::BossThread(ThreadPool* pThreadPool,wxCondition* pQueueCondition,wxThreadKind kind):wxThread(kind)
                        ,m_pThreadPool(pThreadPool)
                        ,m_pQueueCondition(pQueueCondition)
{
    //ctor
}

BossThread::~BossThread()
{
}

void* BossThread::Entry()
{
    while()
    {
        // 在thread pool 上等待
        m_pQueueCondition.Wait();
        //检查空闲线程
        m_threadsState::const_iterator it;
        for(it = m_threadsState.begin(); it != m_threadsState.end(); ++it)
        {
            for(int i=0; i<m_pThreadPool->m_busyThreads.size(); i++){
                    if(m_threadsState[i] == (*it)){
                        m_pThreadPool->m_busyThreads->erase(it); // remove worker thread id from busy thread vector
                        (*it) &= 0; //设置标志位 0
                    }
            }
            m_pThreadPool->m_idleThreads.push_back(m_threadsState[i]); // push worker thread id in idle thread vector
        }

        // a new task need to be process
        if(m_pThreadPool->m_taskQueue.IsOk()){
            if(m_pThreadPool->m_idleThreads.size() > 0) // idle thread exist?
            {
                ThreadTask* pTask = m_pThreadPool->m_taskQueue.ReceiveTimeout(1);
                AssignTask(pTask);
            }else{ // Notify interrupt worker thread suspend
                for(int i=0; i=m_pThreadPool->m_busyThreads.size();i++){
                    if(m_threadsState == -1){
                        m_threadsState == 0x0010; // notify worker thread to discard current job
                    }
                }
            }
        }
    }
}

void BossThread::ThreadIdleNotify()
{
    wxCriticalSectionLocker enter(m_criticalSection);
    m_awake |= 1;
}

 void BossThread::AssignTask(ThreadTask* task)
 {

 }
