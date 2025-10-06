#include "parent.h"
#include <iostream>
#include <string>

int main() {
    std::string filename;
    std::cout << "Parent[" << os::GetCurrentPID() << "]: Введите имя файла для дочернего процесса:" << std::endl;
    std::getline(std::cin, filename);

    if (filename.empty()) {
        std::cerr << "Parent: Имя файла не может быть пустым." << std::endl;
        return 1;
    }

    parent::Parent p;
    p.CreateChildProcess(filename);
    p.Input();
    p.EndChild();
    std::cout << "Parent[" << os::GetCurrentPID() << "]: Программа завершена." << std::endl;
    return 0;
}