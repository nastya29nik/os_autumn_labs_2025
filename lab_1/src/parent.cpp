#include "parent.h"

namespace parent {

    Parent::Parent() {
#ifdef _WIN32
        pipe1.write_end = INVALID_HANDLE_VALUE;
        pipe1.read_end = INVALID_HANDLE_VALUE;
        child_process_handle.hProcess = NULL;
#else
        pipe1.write_end = -1;
        pipe1.read_end = -1;
        child_process_handle = -1;
#endif
    }

    void Parent::CreateChildProcess(const std::string& filename) {
        child_process_handle = os::CreateChildProcess("./child_process", pipe1);

#ifdef _WIN32
        bool success = child_process_handle.hProcess != NULL;
#else
        bool success = child_process_handle != -1;
#endif

        if (!success) {
            std::cerr << "Parent[" << os::GetCurrentPID() << "]: ОШИБКА! Не удалось создать дочерний процесс." << std::endl;
            exit(1);
        }
        
        std::cout << "Parent[" << os::GetCurrentPID() << "]: Дочерний процесс создан." << std::endl;

        std::string filename_with_newline = filename + "\n";
        if (!os::WriteToPipe(pipe1.write_end, filename_with_newline)) {
             std::cerr << "Parent[" << os::GetCurrentPID() << "]: ОШИБКА! Не удалось записать имя файла в pipe." << std::endl;
        }
    }

    void Parent::Input() {
        std::cout << "Введите строки с числами. Для выхода введите 'exit'." << std::endl;
        std::string input;

        while (std::getline(std::cin, input)) {
            if (input == "exit") {
                std::cout << "Parent[" << os::GetCurrentPID() << "]: Получена команда на выход." << std::endl;
                break;
            }
            if (input.empty()) continue;
            
            input += "\n";
            if (!os::WriteToPipe(pipe1.write_end, input)) {
                std::cerr << "Parent[" << os::GetCurrentPID() << "]: ОШИБКА! Запись в pipe не удалась." << std::endl;
                break;
            }
        }
    }

    void Parent::EndChild() {
        os::ClosePipeEnd(pipe1.write_end);
        os::WaitForChild(child_process_handle);
        std::cout << "Parent[" << os::GetCurrentPID() << "]: Дочерний процесс завершен." << std::endl;
    }

    Parent::~Parent() {
        os::ClosePipeEnd(pipe1.write_end);
        os::ClosePipeEnd(pipe1.read_end);
    }
}