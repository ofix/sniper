#ifndef ThreadTask_H
#define ThreadTask_H
#include <wx/buffer.h>
#include "core/Global.h"
#include <wx/thread.h>

class ThreadTask
{
    public:
        ThreadTask();
        virtual ~ThreadTask();
        virtual void Execute();
    protected:
        int m_type;
        wxMemoryBuffer m_data;
};

#endif // ThreadTask_H
