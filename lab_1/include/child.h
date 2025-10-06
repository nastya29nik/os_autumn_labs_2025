#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "os.h"

namespace child {
    class Child {
    private:
        std::string filename;
        std::ofstream file;
        int pid;
        std::vector<float> parse_floats(const std::string& s);

    public:
        explicit Child(const std::string& filename);
        void SumFunc();
        ~Child();
    };
}