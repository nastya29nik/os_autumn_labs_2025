#include <iostream>

#include "exception.h"
#include "child.h"

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Child: Error! Shared memory name not provided." << std::endl;
            return 1;
        }
        std::string shm_name = argv[1];
        child::Child c(shm_name);
        c.Work();
    } catch (const except::ProcessExcept& e) {
        std::cerr << "Child Process Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Child Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}