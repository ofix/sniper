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
    while(1)
    {
        // 在thread pool 上等待
        //m_pQueueCondition.Wait();
        //检查空闲线程
        wxVector<int>::const_iterator it;
        for(it = m_threadsState.begin(); it != m_threadsState.end(); ++it)
        {
            wxVector<WorkerThread*>::const_iterator ii;
            wxVector<WorkerThread*> busyThreads = m_pThreadPool->GetBusyThreads();
            for(ii=busyThreads.begin() ; ii != busyThreads.end(); ++ii){
//                    if(1){
//                        m_pThreadPool->GetBusyThreads().erase(i,1); // remove worker thread id from busy thread vector
//                        m_threadsState[i] &= 0; //设置标志位 0
//                    }
            }
           // m_pThreadPool->GetIdleThreads().push_back(m_threadsState[i]); // push worker thread id in idle thread vector
        }

        // a new task need to be process
//        if(m_pThreadPool->m_taskQueue.IsOk()){
//            if(m_pThreadPool->GetIdleThreads().size() > 0) // idle thread exist?
//            {
//                ThreadTask* pTask = m_pThreadPool->m_taskQueue.ReceiveTimeout(1);
//                AssignTask(pTask);
//            }else{ // Notify interrupt worker thread suspend
//                for(int i=0; i=m_pThreadPool->m_busyThreads.size();i++){
//                    if(m_threadsState == -1){
//                        m_threadsState == 0x0010; // notify worker thread to discard current job
//                    }
//                }
//            }
//        }
    }
}
