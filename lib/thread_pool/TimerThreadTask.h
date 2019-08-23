#ifndef TIMERTHREADTASK_H
#define TIMERTHREADTASK_H
#include "ThreadTask.h"

class TimerThreadTask:public ThreadTask
{
    public:
        TimerThreadTask();
        virtual ~TimerThreadTask();
        virtual void Execute();
};

#endif // TIMERTHREADTASK_H
