#include <iostream>
#include <thread>
#include <chrono>

// Simulate heavy tasks with equal sleep durations
void heavyTask1() {
    std::cout << "[Task1] Starting heavy work..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "[Task1] Finished heavy work!" << std::endl;
}

void heavyTask2() {
    std::cout << "[Task2] Starting heavy work..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "[Task2] Finished heavy work!" << std::endl;
}

int main() {
    auto start = std::chrono::steady_clock::now();

    std::thread t1(heavyTask1);
    std::thread t2(heavyTask2);

    t1.join();
    t2.join();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Both heavy tasks finished in " << elapsed.count() << " seconds." << std::endl;
    std::cout << "(If your CPU has multiple cores, elapsed time should be close to 2s, not 4s!)" << std::endl;
    return 0;
}
