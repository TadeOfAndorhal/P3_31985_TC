#pragma warning( disable : 4473 )
#include <thread>
#include <cstdio>
#include <windows.h>
#include <mutex>
#include <chrono>
#include <iostream>

std::mutex counter_mutex;
unsigned int counter = 0;

void increment() {
    auto start = std::chrono::steady_clock::now();
    for (;;) {
        if (counter == 11)
            break;
        counter_mutex.lock();
        counter++;
        counter_mutex.unlock();
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
        counter_mutex.lock();
        if (counter % 2) {
            printf("%u jest nieparzyste\r\n", counter);
        }
        else {
            printf("%u jest parzyste\r\n", counter);
        }
        counter_mutex.unlock();
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
