#include "WorkerThread.h"
#include "BossThread.h"

WorkerThread::WorkerThread(BossThread* pBossThread,wxThreadKind kind)
                    :wxThread(kind)
                    ,m_pBossThread(pBossThread)
                    ,m_pTask(nullptr)
{
    //ctor
}

WorkerThread::~WorkerThread()
{
    //dtor
}

void WorkThread::SetTask(ThreadTask* pTask)
{
    m_pTask = pTask;
}

void*  WorkerThread::Entry()
{
    while(1){
        // wait on m_pBossThread.m_threadsState
        if(m_pTask->type == eTask::TIMER){
            int mSpan = m_pTask->timer;
            int iRet = m_pTask->Execute(); // Execute Task
            // normal is 1,exception is 0 ,>1 need sleep
            if(iRet == 0) // The thread should Sleep iRet seconds;
            {

            }else if(iRet > 1){
                // need Sleep, ask for boss Thread wake up me iRet seconds
            }

            //check for higher priority thread exist
            if(CHECK_FOR(SIGNAL_TASK_URGENT))
            {

            }
            if(CHECK_FOR(SIGNAL_DESTROY))
            {

            }
            if(CHECK_FOR(SIGNAL_DISCARD_TASK))
            {

            }
            if(CHECK_FOR(SIGNAL_BACKUP_TASK))
            {

            }
            wxThread::Sleep(m_pTask->timer)
        }else{
            //check for higher priority thread exist
            if(CHECK_FOR(SIGNAL_TASK_URGENT))
            {

            }
            if(CHECK_FOR(SIGNAL_DESTROY))
            {

            }
            if(CHECK_FOR(SIGNAL_DISCARD_TASK))
            {

            }
            if(CHECK_FOR(SIGNAL_BACKUP_TASK))
            {

            }
        }
        break;
    }
}



