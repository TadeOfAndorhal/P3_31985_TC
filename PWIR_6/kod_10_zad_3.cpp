#pragma warning( disable : 4473 )
#include <thread>
#include <cstdio>
#include <windows.h>
#include <chrono>
#include <iostream>

//#include <mutex>
#include <atomic>

//std::mutex counter_mutex;
//unsigned int counter = 0;
std::atomic<unsigned int> counter;

void increment() {
    auto start = std::chrono::steady_clock::now();
    for (;;) {
        if (counter == 11)
            break;
        //counter_mutex.lock();
        counter++;
        //counter_mutex.unlock();
        Sleep(1000);
    }
    auto end = std::chrono::steady_clock::now();
    printf("Czas trwania 1: %llu\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    );
}
void parity() {
    auto start = std::chrono::steady_clock::now();
    for (;;) {
        if (counter == 11)
            break;
        //counter_mutex.lock();
        if (counter % 2) {
            std::cout << counter <<" jest nieparzyste \r\n";
        }
        else {
            std::cout << counter << " jest parzyste \r\n";
        }
        //counter_mutex.unlock();
        Sleep(1000);
    }
    auto end = std::chrono::steady_clock::now();
    printf("Czas trwania 2: %llu\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    );
}

int main() {
    std::thread inc(increment);
    std::thread par(parity);

    inc.join();
    par.join();

    printf("Done\r\n");

    return 0;
}
