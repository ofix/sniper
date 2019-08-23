#include "WorkerThread.h"
#include "ThreadPool.h"

WorkerThread::WorkerThread(ThreadPool* pThreadPool,wxThreadKind kind)
                    :wxThread(kind)
                    ,m_pThreadPool(pThreadPool)
{
    //ctor
}

WorkerThread::~WorkerThread()
{
    //dtor
}

void*  WorkerThread::Entry()
{
    return nullptr;
}
