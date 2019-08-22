#include "ManagerThread.h"

ManagerThread::ManagerThread(wxThreadKind kind):wxThread(kind)
{
    //ctor
}

ManagerThread::~ManagerThread()
{
    //dtor
}

void* ManagerThread::Entry()
{
    return nullptr;
}
