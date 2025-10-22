#pragma once

#include <pthread.h>
#include <stdexcept>
#include <string>

namespace os {
    class CreateException : public std::runtime_error {
    public:
        explicit CreateException(const std::string& message) : std::runtime_error(message) {}
    };

    class JoinException : public std::runtime_error {
    public:
        explicit JoinException(const std::string& message) : std::runtime_error(message) {}
    };

    using ThreadFunc = typeof(void*(void*))*;
    struct ThreadInfo;
    using ThreadHandle = ThreadInfo*;

    class Thread {
        private:
        ThreadFunc func_;
        ThreadHandle handle_;

        public:
        Thread(ThreadFunc func);

        Thread(const Thread&) = delete;

        Thread& operator=(const Thread&) = delete;

        Thread(Thread&& other);

        Thread& operator=(Thread&& other);

        void Run (void* thread_data);

        void Join();

        void Swap(Thread& other);

        ~Thread() noexcept;

    };
}