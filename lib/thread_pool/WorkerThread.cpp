#include "WorkerThread.h"
#include "ThreadPool.h"

WorkerThread::WorkerThread(ThreadPool* pThreadPool,wxThreadKind kind):m_pThreadPool(pThreadPool),wxThread(kind)
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

