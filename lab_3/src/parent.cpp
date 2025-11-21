#include <cstring>
#include <iostream>

#include "exception.h"
#include "parent.h"

namespace parent {

Parent::Parent() {
    shm_name = "/shared_mem"; 
    shm = os::CreateShM(shm_name, os::SHM_SIZE);
    os::SetSignalHandler(os::CONFIRM, os::DefaultSignalHandler);
}

void Parent::Run(const std::string& filename) {
    child_pid = os::CreateChildProcess("./child_process", shm_name);
    std::cout << "Parent[" << os::GetCurrentPID() << "]: Waiting for child initialization." << std::endl;
    os::WaitSignal(); 
    std::memset(shm.ptr, 0, shm.size);
    std::strncpy(shm.ptr, filename.c_str(), shm.size - 1);
    std::cout << "Parent: Sending filename '" << filename << "'..." << std::endl;
    os::SendSignal(child_pid, os::WORK);
    os::WaitSignal(); 
    std::cout << "Parent: Enter numbers ('exit' to quit)." << std::endl;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line == "exit") {
            break;
        }
        if (line.empty()) {
            continue;
        }
        std::memset(shm.ptr, 0, shm.size);
        std::strncpy(shm.ptr, line.c_str(), shm.size - 1);
        os::SendSignal(child_pid, os::WORK);
        os::WaitSignal();
    }

    std::memset(shm.ptr, 0, shm.size); 
    os::SendSignal(child_pid, os::WORK);
    std::cout << "Parent: Waiting for child to exit." << std::endl;
    os::WaitForChild(child_pid);
    std::cout << "Parent: Child finished." << std::endl;
}

Parent::~Parent() {
    try {
        os::DestroyShM(shm);
    } catch (...) {
    }
}

}