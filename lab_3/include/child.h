#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "os.h"

namespace child {

class Child {
private:
    os::SharedMemory shm;
    std::ofstream file;
    
    std::vector<float> parse_floats(const std::string& s);

public:
    explicit Child(const std::string& shm_name);

    ~Child();
    
    void Work();
};

}