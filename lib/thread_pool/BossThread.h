#ifndef BossThread_H
#define BossThread_H
#include <wx/thread.h>
#include <wx/thread.h>
#include <wx/vector.h>

/*****************************************************
 * following are some beneficial think-about for thread-polling
 * If a task need keep running all the way for a fixed time span
 * ,these are many discrete, and the task is I/O bound.for such
 * program,keep the task running in UI main thread is not a good
 * idea,if only a timer used is not also a good opt,so create background
 * threads to running the task is a better way. how to pause such periodically
 * task if it wants to sleep?
 * call the system call wxThread::Sleep() in its logic loop is absolutely
 * harmful,because thread cannot awake itself if it need to run again after the
 * sleep period.
 * A wake-up mechanism needed for such situation. in the operating system kernel
 *  has a thread queue to keep trace of all thread's status, we can mimic
 * it in the user mode, for our discussion, we should make it come true in the boss-thread main loop,
 * For example,if a worker thread want to sleep, the callback
 * task function would return a number greater than 1,and copy the return value to a mutex variable
 * which are shared between boss thread and worker thread. in the meanwhile, boss thread would detect
 * this change, and push a timer to the timer-queue,the boss thread would check the timer is time-out
 * every one second(note: the minimal timer span in the boss thread).
 * Besides, we should be very careful the task priority.we should avoid a nested periodically task exist.
 * just for MySQL doesn't support nested transaction, otherwise it would make the answer complexed
 * at present.
 *
 *****************************************************/
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
