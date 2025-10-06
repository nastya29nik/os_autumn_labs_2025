#include "os.h"
#include <iostream>
#include <vector>
#include <cstring>

namespace os {
    ProcessHandle CreateChildProcess(const std::string& process_name, Pipe& pipe) {
        int pipe_fds[2];
        if (::pipe(pipe_fds) == -1) {
            perror("pipe");
            return -1;
        }

        pid_t pid = ::fork();
        if (pid == -1) {
            perror("fork");
            return -1;
        }

        if (pid == 0) {
            ::close(pipe_fds[1]); 
            if (::dup2(pipe_fds[0], STDIN_FILENO) == -1) {
                perror("dup2");
                _exit(1);
            }
            ::close(pipe_fds[0]);

            ::execl(process_name.c_str(), process_name.c_str(), nullptr);
            perror("execl");
            _exit(1);
        } else {
            ::close(pipe_fds[0]);
            pipe.write_end = pipe_fds[1];
            pipe.read_end = -1;
            return pid;
        }
    }

    bool WriteToPipe(PipeHandle pipe, const std::string& data) {
        ssize_t bytes_written = ::write(pipe, data.c_str(), data.length());
        return bytes_written == static_cast<ssize_t>(data.length());
    }

    void ClosePipeEnd(PipeHandle& handle) {
        if (handle != -1) {
            ::close(handle);
            handle = -1;
        }
    }

    void WaitForChild(ProcessHandle process) {
        if (process > 0) {
            int status;
            ::waitpid(process, &status, 0);
        }
    }

    int GetCurrentPID() {
        return ::getpid();
    }
}