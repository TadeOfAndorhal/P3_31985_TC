#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <vector>
#include <thread>

double piNiezrownoleglone() {
    const int num_points = 1000000;
    int num_inside_circle = 0;
    std::srand(std::time(nullptr));

    for (int i = 0; i < num_points; i++) {
        double x = ((double)std::rand() / RAND_MAX) * 2 - 1;
        double y = ((double)std::rand() / RAND_MAX) * 2 - 1;
        if (std::pow(x, 2) + std::pow(y, 2) <= 1) {
            num_inside_circle++;
        }
    }

    return 4.0 * num_inside_circle / num_points;
}

double piZrownoleglone(int num_threads) {
    const int num_points = 1000000;
    int num_inside_circle = 0;
    std::srand(std::time(nullptr));
    std::vector<std::thread> threads(num_threads);

    for (int t = 0; t < num_threads; t++) {
        threads[t] = std::thread([&] {
            int temp_points_circle = 0;
            for (int i = 0; i < num_points / num_threads; i++) {
                double x = ((double)std::rand() / RAND_MAX) * 2 - 1;
                double y = ((double)std::rand() / RAND_MAX) * 2 - 1;
                if (std::pow(x, 2) + std::pow(y, 2) <= 1) {
                    temp_points_circle++;
                }
            }
            num_inside_circle += temp_points_circle;
            });
    }
    for (int t = 0; t < num_threads; t++) {
        threads[t].join();
    }

    return 4.0 * num_inside_circle / num_points;
}

int main() {
    auto start = std::chrono::steady_clock::now();
    double pi1 = piNiezrownoleglone();
    auto end = std::chrono::steady_clock::now();
    printf("Czas trwania piNiezrownoleglone() [MS]: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "Approximate value of Pi (1) : " << pi1 << std::endl;

    start = std::chrono::steady_clock::now();
    double pi2 = piZrownoleglone(4);
    end = std::chrono::steady_clock::now();
    printf("Czas trwania piZrownoleglone() [MS]: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "Approximate value of Pi (2) : " << pi2 << std::endl;

    return 0;
}