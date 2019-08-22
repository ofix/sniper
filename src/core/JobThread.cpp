#include "JobThread.h"
#include "ThreadPool.h"

JobThread::JobThread(ThreadPool* pThreadPool,wxThreadKind kind):m_pThreadPool(pThreadPool),wxThread(kind)
{
    //ctor
}

JobThread::~JobThread()
{
    //dtor
}

void*  JobThread::Entry()
{
    return nullptr;
}

