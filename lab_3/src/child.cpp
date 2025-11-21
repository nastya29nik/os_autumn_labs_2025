#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "child.h"
#include "exception.h"

namespace child {

Child::Child(const std::string& shm_name) {
    os::SetSignalHandler(os::WORK, os::DefaultSignalHandler);
    shm = os::OpenShM(shm_name, os::SHM_SIZE);
}

void Child::Work() {
    os::SendSignal(os::GetParentPID(), os::CONFIRM);
    os::WaitSignal(); 
    std::string filename = shm.ptr;
    if (filename.empty()) {
        throw except::ProcessExcept("Child: Received empty filename.");
    }
    file.open(filename, std::ios::app);
    if (!file.is_open()) {
        throw except::ProcessExcept("Child: Failed to open file: " + filename);
    }
    os::SendSignal(os::GetParentPID(), os::CONFIRM);

    while (true) {
        os::WaitSignal();
        std::string line = shm.ptr;
        if (line.empty()) {
            break;
        }
        std::vector<float> numbers = parse_floats(line);
        if (numbers.empty()) {
            os::SendSignal(os::GetParentPID(), os::CONFIRM);
            continue;
        }
        float sum = 0.0f;
        for (float n : numbers) {
            sum += n;
        }
        file << "Sum (" << line << ") = " << std::setprecision(7) << sum << std::endl;
        file.flush();
        os::SendSignal(os::GetParentPID(), os::CONFIRM);
    }
}

std::vector<float> Child::parse_floats(const std::string& s) {
    std::vector<float> nums;
    std::stringstream ss(s);
    float n;
    while (ss >> n) {
        nums.push_back(n);
    }
    return nums;
}

Child::~Child() {
    if (file.is_open()) file.close();
    os::UnmapShM(shm);
}

}