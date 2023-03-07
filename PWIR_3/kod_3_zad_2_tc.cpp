#include <chrono>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <iostream>

int* fibbo(int n)
{
	int* tab = new int[n];
	tab[0] = 1;
	tab[1] = 1;
	for (int i = 2; i < n; i++)
		tab[i] = tab[i - 1] + tab[i - 2];
	return tab;
}

int main()
{
	int n = 40000;
	auto start = std::chrono::steady_clock::now();
	int * fibbonaci_ciag = fibbo(n);
	Sleep(2000);
	auto end = std::chrono::steady_clock::now();
	printf("Czas trwania generowania %d liczb ciagu fibbonacciego: %llu ms\n", n, std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	printf("Wygenerowane liczby: \n");
	for (int i = 0; i < n; i++)
		printf(" %d ,", fibbonaci_ciag[i]);
	delete[] fibbonaci_ciag;
	return 0;
}