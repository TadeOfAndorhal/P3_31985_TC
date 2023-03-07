#include <chrono>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <iostream>

int main()
{
	std::fstream fs;
	auto start = std::chrono::steady_clock::now();
	fs.open("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	fs.close();
	auto end = std::chrono::steady_clock::now();
	printf("Czas trwania: %llu ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	return 0;
}