#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <functional>


class Timer
{
    std::thread Thread;
    bool Alive = false;
    long CallNumber = -1L;
    long repeat_count = -1L;
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> funct = nullptr;

    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);
        if(Alive)
            Function()();
    }
    void ThreadFunc()
    {
        if(CallNumber == infinite)
            while(Alive)
                SleepAndRun();
        else
            while(repeat_count--)
                SleepAndRun();
    }
public:
    static const long infinite = -1L;
    Timer(){}
    Timer(const std::function<void(void)> &f) : funct(f) {}
    Timer(const std::function<void(void)> &f, const unsigned long &i, const long repeat = Timer::infinite): funct(f),
                                                                                                            interval(std::chrono::milliseconds(i)),
                                                                                                            CallNumber(repeat){}
    void Start(bool Async = true)
    {
        if(Alive)
            return ;
        Alive = true;
        repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc, this);
        else
            this->ThreadFunc();
    }

    void Stop()
    {
        Alive = false;
        Thread.join();
    }

    bool IsAlive() const {return Alive;}
    void RepeatCount(const long r)
    {
        if(Alive)
            return;
        CallNumber = r;
    }

    long GetLeftCount() const {return repeat_count;}
    long RepeatCount() const {return CallNumber;}
    void SetInterval(const unsigned long &i)
    {
        if(Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }
    unsigned long Interval() const {return interval.count();}

    const std::function<void(void)> &Function() const
    {
        return funct;
    }
    void SetFunction(const std::function<void(void)> &f)
{
    if (Alive)
        return;
    funct = f;
}
};

#endif // TIMER_H
