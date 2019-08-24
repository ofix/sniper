#ifndef ThreadTask_H
#define ThreadTask_H
#include <wx/buffer.h>
#include "core/Global.h"
#include <wx/thread.h>

#define TASK_PRIORITY_HIGH 2
#define TASK_PRIORITY_NORMAL 1
#define TASK_PRIORITY_LOW 0

class ThreadTask
{
    public:
        ThreadTask();
        virtual ~ThreadTask();
        virtual void Execute();
    public:
        int priority; // task priority
        int type; // task type
        int bInterrupt; // can be suspend or not
        wxMemoryBuffer data;
};

#endif // ThreadTask_H
