#include "TimerThreadTask.h"

TimerThreadTask::TimerThreadTask()
{
    //ctor
}

TimerThreadTask::~TimerThreadTask()
{
    //dtor
}

void TimerThreadTask::Execute()
{
    for(int i=0; i<100; i++){
        std::cout<<"thread_id: "<<wxThread::GetCurrentId()<<" output: "<<i<<std::endl;
        wxThread::Sleep(300);
    }
}
