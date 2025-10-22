#include "thread.h"

#include <algorithm>
#include <chrono>
#include <climits>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct PartialResult {
    int min = INT_MAX;
    int max = INT_MIN;
};

struct ThreadData {
    const std::vector<int>& data_ref;
    size_t start_index;
    size_t end_index;
    PartialResult result;
};

void* funcMinMax(void* arg) {
    auto* data = static_cast<ThreadData*>(arg);
    if (!data) return nullptr;

    int local_min = INT_MAX;
    int local_max = INT_MIN;
    for (size_t i = data->start_index; i < data->end_index; ++i) {
        if (data->data_ref[i] < local_min) local_min = data->data_ref[i];
        if (data->data_ref[i] > local_max) local_max = data->data_ref[i];
    }
    data->result = {local_min, local_max};
    return nullptr;
}

int threadCount(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::invalid_argument("Incorrect number of arguments.");
    }
    int num_threads = std::stoi(argv[1]);
    if (num_threads <= 0) {
        throw std::invalid_argument("The number of threads must be a positive number.");
    }
    return num_threads;
}

std::vector<int> createArray(size_t size) {
    std::vector<int> arr(size);
    std::mt19937 gen(std::time(0));
    std::uniform_int_distribution<> distrib(1, INT_MAX);
    for (auto& val : arr) {
        val = distrib(gen);
    }
    return arr;
}

PartialResult findParal(const std::vector<int>& data, int num_threads) {
    std::vector<os::Thread> threads;
    std::vector<ThreadData> tasks;
    tasks.reserve(num_threads);

    const size_t chunk_size = data.size() / num_threads;
    const size_t remainder = data.size() % num_threads;
    size_t current_start = 0;

    for (size_t i = 0; i < static_cast<size_t>(num_threads); ++i) {
        size_t block_size = chunk_size + (i < remainder ? 1 : 0);
        
        size_t start = current_start;
        size_t end = start + block_size;
        
        if (start >= data.size()) {
            break; 
        }

        tasks.emplace_back(ThreadData{data, start, end, {}});
        
        threads.emplace_back(funcMinMax);
        threads.back().Run(&tasks.back());

        current_start = end;
    }

    for (auto& t : threads) {
        t.Join();
    }

    PartialResult final_result;
    for (const auto& task : tasks) {
        final_result.min = std::min(final_result.min, task.result.min);
        final_result.max = std::max(final_result.max, task.result.max);
    }
    
    return final_result;
}

int main(int argc, char* argv[]) {
    try {
        int num_threads = threadCount(argc, argv);

        long long array_size = 0;
        std::cout << "Input the array size: ";
        std::cin >> array_size;

        if (std::cin.fail() || array_size <= 0) {
            throw std::runtime_error("Incorrect input. Array size must be a positive number.");
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Array size: " << array_size << ", Number of threads: " << num_threads << std::endl;
        std::vector<int> big_array = createArray(array_size);
        std::cin.get();
        auto start_time = std::chrono::high_resolution_clock::now();
        PartialResult final_result = findParal(big_array, num_threads);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time = end_time - start_time;

        std::cout << "Min element: " << final_result.min << std::endl;
        std::cout << "Max element: " << final_result.max << std::endl;
        std::cout << "Time: " << time.count() << "ms" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}