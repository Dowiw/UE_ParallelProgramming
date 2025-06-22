#include <iostream>
#include <thread>
#include <chrono>

// Simulate some work with varying sleep durations
void taskA() {
    for (int i = 1; i <= 5; ++i) {
        std::cout << "[A] Step " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 200ms
    }
}

void taskB() {
    for (int i = 1; i <= 5; ++i) {
        std::cout << "[B] Step " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(350)); // 350ms
    }
}

int main() {
    auto start = std::chrono::steady_clock::now();

    std::thread t1(taskA);
    std::thread t2(taskB);

    t1.join();
    t2.join();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Both tasks finished (concurrent, may be interleaved)." << std::endl;
    std::cout << "Total elapsed time: " << elapsed.count() << " seconds." << std::endl;
    return 0;
}
