#ifndef ThreadTask_H
#define ThreadTask_H
#include <wx/buffer.h>
#include "include/core/Global.h"
#include <wx/thread.h>

#define TASK_PRIORITY_HIGH 2
#define TASK_PRIORITY_NORMAL 1
#define TASK_PRIORITY_LOW 0

class ThreadTask
{
    public:
        ThreadTask();
        virtual ~ThreadTask();
        virtual int Execute();
    public:
        int priority; // task priority
        int type; // task type
        int id; // task id
        int bInterrupt; // can be suspend or not
        wxMemoryBuffer data;
};

class TaskStatus
{
    int task_id;
    int status; // wait,running,finished not in consideration
};

enum eTask
{
    TIMER,
};

#endif // ThreadTask_H
