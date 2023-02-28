#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>

int action(int id, int s) {
	printf("Uruchamiam watek %d\n", id);
	Sleep(s * 1000);
	printf("-> Koncze watek %d , uplynelo %d sekund\n", id, s);
	return 0;
}

int main() {
	//tworzenie wątku
	std::thread t1(action, 1, 1); //konstruktor klasy t1 przyjmuje minimum wskaźnik na funckje do wykonania
	std::thread t2(action, 2, 5); //funckja ta może coś zwracać, ale może zwaracać też void
	std::thread t3(action, 3, 10); //dalsze parametry zostaną przekazane do podanej funckji

	std::thread::id t1_id = t1.get_id();
	std::thread::id t2_id = t2.get_id();
	std::thread::id t3_id = t3.get_id();

	std::cout << "\nId watek nr 1: " << t1_id << "\n";
	std::cout << "Id watek nr 2: " << t2_id << "\n";
	std::cout << "Id watek nr 3: " << t3_id << "\n";

	t1.join();  //synchronizacja
	t2.join();  //wątek główny ma tu poczekać na te 3 wątki
	t3.join();  //inaczej program by się zakończył wcześniej bo wątki trwają minimum 10 sekund

	printf("Koniec programu \r\n");

	return 0;
}
