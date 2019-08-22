#include "BossThread.h"

BossThread::BossThread(wxThreadKind kind):wxThread(kind)
{
    //ctor
}

BossThread::~BossThread()
{
    //dtor
}

void* BossThread::Entry()
{
    return nullptr;
}
