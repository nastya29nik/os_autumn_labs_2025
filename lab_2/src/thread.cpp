#include "thread.h"

namespace os {
    struct ThreadInfo {
        pthread_t thread;
    };

    Thread::Thread(ThreadFunc func): func_(func) {
        handle_ = new ThreadInfo();
    }

    Thread::Thread(Thread&& other): func_(other.func_), handle_(other.handle_) {
        other.func_ = nullptr;
        other.handle_ = nullptr;
    }

    Thread& Thread::operator=(Thread&& other) {
        if (this == &other) {
            return *this;
        }
        Thread temp = std::move(other);
        this->Swap(temp);
        return *this;
    }

    void Thread::Run (void* thread_data) {
        int res = pthread_create(&(handle_->thread), NULL, func_, thread_data);
        if (res != 0) {
            throw CreateException("Failed to create a thread.");
        }
    }

    void Thread::Join() {
        int res = pthread_join(handle_->thread, NULL);
        if (res != 0) {
            throw JoinException("Failed to join a thread.");
        }

    }

    void Thread::Swap(Thread& other) {
        std::swap(func_, other.func_);
        std::swap(handle_, other.handle_);
    }

    Thread::~Thread() noexcept {
        delete handle_;
    }
}