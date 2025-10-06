#include "os.h"

namespace os {

ProcessHandle CreateChildProcess(const std::string& process_name, Pipe& pipe) {
    HANDLE hPipeRead, hPipeWrite;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hPipeRead, &hPipeWrite, &sa, 0)) {
        return {0};
    }

    if (!SetHandleInformation(hPipeWrite, HANDLE_FLAG_INHERIT, 0)) {
         return {0};
    }

    PROCESS_INFORMATION pi = {0};
    STARTUPINFOA si = {0};
    si.cb = sizeof(STARTUPINFOA);
    si.hStdInput = hPipeRead;
    si.dwFlags |= STARTF_USESTDHANDLES;

    std::string command = process_name;
    if (!CreateProcessA(NULL, &command[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(hPipeRead);
        CloseHandle(hPipeWrite);
        return {0};
    }

    pipe.write_end = hPipeWrite;
    pipe.read_end = hPipeRead; 

    CloseHandle(pi.hThread);

    return pi;
}

bool WriteToPipe(PipeHandle pipe, const std::string& data) {
    DWORD bytes_written;
    return WriteFile(pipe, data.c_str(), static_cast<DWORD>(data.length()), &bytes_written, NULL) && bytes_written == static_cast<DWORD>(data.length());
}

void ClosePipeEnd(PipeHandle& handle) {
    if (handle != INVALID_HANDLE_VALUE) {
        CloseHandle(handle);
        handle = INVALID_HANDLE_VALUE;
    }
}

void WaitForChild(ProcessHandle process) {
    if (process.hProcess) {
        WaitForSingleObject(process.hProcess, INFINITE);
        CloseHandle(process.hProcess);
    }
}

int GetCurrentPID() {
    return static_cast<int>(GetCurrentProcessId());
}

}