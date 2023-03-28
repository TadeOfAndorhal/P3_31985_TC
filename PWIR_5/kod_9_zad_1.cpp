#include <thread>
#include <cstdio>
#include <windows.h>
#include <time.h>

thread_local unsigned int counter = 0;

int* generowanie()
{
    srand(time(NULL));
    int* my_array = new int[100];
    for (size_t i = 0; i < 100; i++)
        my_array[i] = rand() % 10 + 1;
    return my_array;
}

void wypisywanie(int* my_array)
{
    for (size_t i = 0; i < 100; i++)
        printf("tablica %u -> %d\n",i,my_array[i]);
}

void increment(int id) {
    for (int i = 0; i < 10; i++) {
        counter++;
        Sleep(300);
    }

    //ten blok wykona się tylko raz mimo, że wątków jest więcej
    if (id == 1) {
        printf("%u\n", counter);
    }
}

int main() {
    int* tab = generowanie();
    wypisywanie(tab);

    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    delete[] tab;
    return 0;
}
