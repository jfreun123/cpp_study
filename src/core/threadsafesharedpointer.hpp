#pragma once

#include <atomic>
#include <utility> // For std::exchange
#include <new>     // For std::destroy_at
#include <memory>

namespace core
{
    template <typename T>
    class shared_pointer
    {
    public:
        // Constructor
        explicit shared_pointer(T *raw_ptr = nullptr)
            : d_value(raw_ptr),
              d_refCount(raw_ptr ? new std::atomic<unsigned int>(1) : nullptr) {}

        // Copy Constructor
        shared_pointer(const shared_pointer &other)
            : d_value(other.d_value),
              d_refCount(other.d_refCount)
        {
            if (d_refCount)
            {
                d_refCount->fetch_add(1, std::memory_order_relaxed);
            }
        }

        // Assignment Operator
        shared_pointer &operator=(const shared_pointer &other)
        {
            if (this == &other) [[unlikely]]
            {
                return *this; // Self-assignment check
            }
            release(); // Release current resource
            d_value = other.d_value;
            d_refCount = other.d_refCount;
            if (d_refCount)
            {
                d_refCount->fetch_add(1, std::memory_order_relaxed);
            }
            return *this;
        }

        // Destructor
        ~shared_pointer()
        {
            release();
        }

        // get(): Returns the raw pointer
        T *get() const noexcept
        {
            return d_value;
        }

        // use_count(): Returns the reference count
        int use_count() const noexcept
        {
            return d_refCount ? d_refCount->load(std::memory_order_relaxed) : 0;
        }

        // reset(): Releases ownership of the managed object
        void reset(T *new_ptr = nullptr)
        {
            release();
            d_value = new_ptr;
            d_refCount = new_ptr ? new std::atomic<unsigned int>(1) : nullptr;
        }

        // Dereference operator
        T &operator*() const
        {
            return *d_value;
        }

        // Member access operator
        T *operator->() const noexcept
        {
            return d_value;
        }

    private:
        T *d_value;                            // Raw pointer to the managed object
        std::atomic<unsigned int> *d_refCount; // Atomic reference count for thread safety

        void release()
        {
            if (d_refCount)
            {
                if (d_refCount->fetch_sub(1, std::memory_order_acq_rel) == 1)
                {
                    delete d_value;
                    std::destroy_at(d_refCount); // Explicit destruction
                    delete d_refCount;
                }
            }
            d_value = nullptr;
            d_refCount = nullptr;
        }
    };

}
