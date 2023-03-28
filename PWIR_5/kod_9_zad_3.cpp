#include <thread>
#include <cstdio>
#include <windows.h>
#include <time.h>


thread_local unsigned int counter = 0;
//unsigned int counter = 0;


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
        printf("tablica %l -> %d\n",i,my_array[i]);
}

void increment(int id, int *tab) 
{
    int save_id = id;
    int start = id * 10;
    int end = 10*(id + 1);
    int help = 0;
    for (size_t i = start; i < end; i++) 
    {
        help = help + tab[i];
        Sleep(100);
    }

    counter += help;
    printf("ID: %u -> %d\n", save_id, counter);
}

int main() {
    int* tab = generowanie();
    //wypisywanie(tab);

    std::thread threads[10];
    for (size_t i = 0; i < 10; i++) {
        threads[i] = std::thread(increment, i, tab);
    }

    for (size_t i = 0; i < 10; i++) {
        threads[i].join();
    }

    delete[] tab;
    return 0;
}
