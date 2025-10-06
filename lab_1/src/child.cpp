#include "child.h"


namespace child {
    Child::Child(const std::string& filename_arg) : filename(filename_arg) {
        pid = os::GetCurrentPID();
        file.open(filename, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Child[" << pid << "]: Ошибка!!! Не удалось открыть файл: " << filename << std::endl;
        }
    }

    std::vector<float> Child::parse_floats(const std::string& s) {
        std::vector<float> numbers;
        std::stringstream ss(s);
        float number;
        while (ss >> number) {
            numbers.push_back(number);
        }
        return numbers;
    }

    void Child::SumFunc() {
        if (!file.is_open()) {
            return;
        }

        std::string line;
        while (std::getline(std::cin, line)) {
            if (line.empty()) continue;
            
            std::vector<float> numbers = parse_floats(line);
            if (numbers.empty()) continue;

            float sum = 0.0f;
            for (float num : numbers) {
                sum += num;
            }
            file << "Сумма чисел " << line << " = " << std::setprecision(7) << sum << std::endl;
            file.flush();
        }
    }

    Child::~Child() {
        if (file.is_open()) {
            file.close();
        }
    }
}