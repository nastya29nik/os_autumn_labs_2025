#pragma once

#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>
#endif

namespace os {

#ifdef _WIN32
    using ProcessHandle = PROCESS_INFORMATION;
    using PipeHandle = HANDLE;
#else
    using ProcessHandle = pid_t;
    using PipeHandle = int;
#endif

    struct Pipe {
        PipeHandle read_end;
        PipeHandle write_end;
    };

    ProcessHandle CreateChildProcess(const std::string& process_name, Pipe& pipe);
    bool WriteToPipe(PipeHandle pipe, const std::string& data);
    void ClosePipeEnd(PipeHandle& handle);
    void WaitForChild(ProcessHandle process);
    int GetCurrentPID();
}