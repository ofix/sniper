#ifndef BossThread_H
#define BossThread_H
#include <wx/thread.h>
#include <wx/thread.h>
#include <wx/vector.h>

/*************************************************************************************************************
 * Following are some beneficial think-about for thread pool's implementation.
 * 1. A common application scenario *
 *    An I/O bound task need keep running in several fixed time spans periodically, typically a user's stock program
 * owns several background threads to pull newest stock price from remote server. the stock market
 * has a break during 11:30 am ~ 13:00 pm, above background threads should sleep during this period.
 * for saving CPU time. keep-alive TCP connections would be a good choice, but if all the prices come from HTTP
 * server, no TCP connection is available, what can we do?
 *
 *    Normally, we can create a timer in the UI main thread, to check if the sleep time for background
 * threads has arrived. if yes, keep them SLEEP and free the worker threads occupied.
 *
 * 2. Except above method, another possibility exist??? *
 *    The difficulty is how to pause periodically execute tasks if they want to sleep?
 * Calling the kernel function wxThread::Sleep() in its logic loop is absolutely useless and harmful,
 * because sleeping thread can not awake itself automatically.

 *    You may want to register a wake-up event to OS, let system to wake them up after time-out, but this
 * requires the worker thread not do any other task during sleeping period, because OS keep a copy of
 * all registers state before sleep and copy them back after awake.If during the sleeping time,worker thread's
 * task are exchanged, all register value would lost, we can not avoid this step.

 *    Now the only way we can choose is to mimic the OS kernel thread dispatch mechanism in our own code (the user mode),
 * As to our problem, the best place for it is the boss-thread main loop,
 *
 *    For example, if a worker thread want to sleep, the task callback function would return a number greater than 1,
 * and copy the return value to a mutex variable which are shared between boss thread and worker thread.
 * with the OS help, the boss thread would detect this change, and push a timer with thread's ID to the timer queue,
 * the boss thread would check the timer is time-out every one second(note: the minimal timer span in the boss thread).
 * Besides, we should be very careful with the task priority. we should avoid nested periodically tasks exist.
 * Just like MySQL doesn't support nested transaction, otherwise it would make the solution complexed.

 * 3. The security problem about timer queue in boss thread
 *    If a  higher priority task has the right to occupy other lower priority running worker thread's execution time.
 * We would encounter another hazardous situation: the higher priority task has not ended yet,but the lower priority thread
 * in the timer queue timed out and need to run immediately!!! If we let the lower priority thread awaits continually until the
 * higher priority thread end up, this would cause severe logic error.
 *
 *    How to solve this zigzag puzzle? If we want all the tasks have the opportunity to run fairly, we have an opt,
 * cut down every task execution time,just like the OS does. No matter its priority is higher or not, every task has the
 * opportunity be seize to occupy the worker thread, and it obviously keep the worker thread busy all the time.
 * This is not we want to see.
 *    In a word, thread pool is efficient most of time, but not omnipotent always. We should endure its backwards.
 * Most of time,a timer in UI main thread is a workable and better solution.
   *************************************************************************************************************/
class ThreadPool;
class BossThread:public wxThread
{
    public:
        BossThread(ThreadPool* pThreadPool,wxThreadKind kind=wxTHREAD_DETACHED);
        virtual ~BossThread();
        virtual void* Entry();
        void NewTaskNotify();
        void ThreadIdleNotify(int threadId); // must lock and sync

    protected:
        void AssignTask(ThreadTask* task); // must lock and sync

        ThreadPool* m_pThreadPool;
        int m_awake; // UI main thread or worker thread would modify this variable
        wxVector<int> m_threadsState; // worker thread state; worker threads would modify it
        wxCriticalSection m_criticalSection;
};

#endif // BossThread_H
