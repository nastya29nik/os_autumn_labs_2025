#include <iostream>
#include <string>

#include "exception.h"
#include "os.h"
#include "parent.h"

int main() {
    try {
        std::string filename;
        std::cout << "Parent[" << os::GetCurrentPID() << "]: Enter output filename:" << std::endl;
        std::getline(std::cin, filename);

        if (filename.empty()) {
            std::cerr << "Error: Filename cannot be empty." << std::endl;
            return 1;
        }
        parent::Parent p;
        p.Run(filename);
    } catch (const except::ProcessExcept& e) {
        std::cerr << "Process Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Parent Error:" << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown Error." << std::endl;
        return 1;
    }
    return 0;
}