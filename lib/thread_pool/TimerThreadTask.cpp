#include "TimerThreadTask.h"

TimerThreadTask::TimerThreadTask()
{
    //ctor
}

TimerThreadTask::~TimerThreadTask()
{
    //dtor
}

int TimerThreadTask::Execute()
{
    for(int i=0; i<100; i++){
        std::cout<<"thread_id: "<<wxThread::GetCurrentId()<<" output: "<<i<<std::endl;
        return 300; // task schedule.
    }
    return 0;
}
