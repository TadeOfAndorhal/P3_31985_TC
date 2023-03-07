#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <thread>

#define SIZE 100

void add(int id, int* a, int* b, int* c)
{
	int i = id * 10;
	for (int j = i; j < i + 10; j++)
		c[j] = a[j] + b[j];
}

int main() {
	srand(time(NULL));
	int tmp = SIZE / 10;
	int a[SIZE];
	int b[SIZE];
	int c[SIZE];

	for (int i = 0; i < SIZE; i++) {
		a[i] = rand() % 100 + 1; //1 do 100
		b[i] = rand() % 100 + 1;
	}

	//wypisanie na ekranie A
	for (int i = 0; i < SIZE; i++) {
		printf("%u ", a[i]);
	}
	printf("\n");

	//wypisanie na ekranie B
	for (int i = 0; i < SIZE; i++) {
		printf("%u ", b[i]);
	}
	printf("\n");

	std::thread** threads = new std::thread*[10];
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < tmp; i++) {
		threads[i] = new std::thread(add, i, a, b, c); //wykorzystuje i jako id danego w¹tku
	}
	auto end = std::chrono::steady_clock::now();

	for (int i = 0; i < tmp; i++) {
		threads[i]->join();
	}

	for (int i = 0; i < tmp; i++) {
		delete threads[i];
	}
	delete[] threads;

	//wypisanie na ekranie C
	for (int i = 0; i < tmp; i++) {
		printf("%u ", c[i]);
	}

	printf("\nCzas trwania: %llu ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

	return 0;
}