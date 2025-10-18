#ifndef OBJECT_COUNTER_H
#define OBJECT_COUNTER_H

#include <cstddef>

#ifdef ENABLE_OBJECT_COUNTING

#define DECLARE_OBJECT_COUNTER() \
    private: \
        static ssize_t object_count_; \
        static ssize_t object_destroyed_count_; \
    public: \
        static ssize_t get_object_count() { return object_count_; } \
        static ssize_t get_destroyed_count() { return object_destroyed_count_; } \
        static ssize_t get_alive_count() { return object_count_ - object_destroyed_count_; } \
        static void reset_object_count() { object_count_ = 0; object_destroyed_count_ = 0; }

#define INCREMENT_OBJECT_COUNTER() ++object_count_
#define DECREMENT_OBJECT_COUNTER() ++object_destroyed_count_

// inline for header-only classes - requires C++17
#define DEFINE_OBJECT_COUNTER(ClassName) \
    inline ssize_t ClassName::object_count_ = 0; \
    inline ssize_t ClassName::object_destroyed_count_ = 0;

#else

#define DECLARE_OBJECT_COUNTER()
#define INCREMENT_OBJECT_COUNTER()
#define DECREMENT_OBJECT_COUNTER()
#define DEFINE_OBJECT_COUNTER(ClassName)

#endif

#endif
