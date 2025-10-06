#pragma once

#include <iostream>
#include <string>
#include "os.h"

namespace parent {
    class Parent {
    private:
        os::Pipe pipe1;
        os::ProcessHandle child_process_handle;

    public:
        Parent();
        void CreateChildProcess(const std::string& filename);
        void Input();
        void EndChild();
        ~Parent();
    };
}