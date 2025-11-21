#pragma once

#include <string>

#include "os.h"

namespace parent {

class Parent {
private:
    os::ProcessHandle child_pid;
    os::SharedMemory shm;
    std::string shm_name;

public:
    Parent();

    ~Parent();

    void Run(const std::string& filename);
};

}