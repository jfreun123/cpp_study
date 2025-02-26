// STD
#include <atomic>

// C functions
#include <stdio.h>
#include <time.h>

// false is unlocked
// true is locked
class SpinLock
{
private:
    std::atomic<bool> flag;

public:
    SpinLock() : flag(false) {}
    void lock()
    {
        static const std::size_t _MAX_TRYS{8};
        static const timespec ns = {0, 1};
        // keep looping forever but eventually sleep to give context back to some thread that can make progress
        // before trying to write and syncronize which is expensive, first (in a relaxed way) see if the lock if is even unlocked
        // here, our acquire gets updates from some other threads release in unlock

        // if flag.load returns false => lock is unlocked => flag.exchange is called
        // => if flag.exchange() succeeds in this thread we return the value of the atomic variable before the call
        // (which is false for unlocked) here.  So, on acquisition, we return false on the inner loop.
        for (int i{}; flag.load(std::memory_order_relaxed) || flag.exchange(true, std::memory_order_acquire); i++)
        {
            if (_MAX_TRYS == i)
            {
                i = 0;
                nanosleep(&ns, NULL);
            }
        }
    }
    void unlock()
    {

        flag.store(false, std::memory_order_release);
    }
};