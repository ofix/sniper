#include "WorkerThread.h"
#include "BossThread.h"

WorkerThread::WorkerThread(BossThread* pBossThread,wxThreadKind kind)
                    :wxThread(kind)
                    ,m_pBossThread(pBossThread)
                    ,m_pTask(nullptr)
                    ,m_status(WORKER_THREAD_IDLE)
{
    //ctor
}

WorkerThread::~WorkerThread()
{
    //dtor
}

void WorkerThread::SetTask(ThreadTask* pTask)
{
    m_pTask = pTask;
}

int WorkerThread::GetStatus()
{
    wxMutexLocker locker(m_mutex);
    return m_status;
}

void*  WorkerThread::Entry()
{
    while(1){
        wxMutexLocker locker(m_mutex);
        m_status = WORKER_THREAD_RUNNING;
        // wait on m_pBossThread.m_threadsState
        if(m_pTask->type == eTask::TIMER){
            int mSpan = 10; //m_pTask->timer;
            int iSeconds = m_pTask->Execute(); // Execute Task
            // normal is 1,exception is 0 ,>1 need sleep
            if(iSeconds == 0) // The thread should Sleep iRet seconds; task has finished
            {
                m_status = WORKER_THREAD_IDLE;
                break;
            }else if(iSeconds > 1){
                // need Sleep, ask for boss Thread wake up me iRet seconds
                wxMutexLocker locker(m_mutex);
                m_status = WORKER_THREAD_SLEEP;
            }

            //check for higher priority thread exist
            if(CHECK_FOR(SIGNAL_TASK_URGENT))
            {

            }
            if(CHECK_FOR(SIGNAL_DESTROY))
            {
                wxMutexLocker locker(m_mutex);
                m_status = WORKER_THREAD_DESTROY;
                break;
            }
            if(CHECK_FOR(SIGNAL_DISCARD_TASK)) // check for task can be discard
            {
                wxMutexLocker locker(m_mutex);
                m_status = WORKER_THREAD_IDLE;
                break;
            }
            wxThread::Sleep(iSeconds);
        }else{
            m_pTask->Execute();
            wxMutexLocker locker(m_mutex);
            if(CHECK_FOR(SIGNAL_DESTROY))
            {
                m_status = WORKER_THREAD_DESTROY;
                break;
            }
            if(CHECK_FOR(SIGNAL_DISCARD_TASK))
            {
                m_status = WORKER_THREAD_DESTROY;
                break;
            }
            m_status = WORKER_THREAD_IDLE;
            break;
        }
    }
    return nullptr;
}



