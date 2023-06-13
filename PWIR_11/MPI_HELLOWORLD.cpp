#include "mpi.h"
#include <cstdio>
#include <iostream>
#include <time.h>

void mainProcess(int size, int vectorSize) {
    srand(time(NULL));

    // obliczamy ile elementów przypada na każdy proces
    int partSize = vectorSize / (size - 1);

    // alokujemy wektory o rozmiarze (partSize (ilosc procesów-1))
    unsigned int* va = new unsigned int[partSize * (size - 1)];
    unsigned int* vb = new unsigned int[partSize * (size - 1)];
    unsigned int* vc = new unsigned int[partSize * (size - 1)];

    // wypełniamy a i b losowymi danymi, a vc zerujemy
    for (unsigned int i = 0; i < partSize* (size - 1); i++) {
        va[i] = rand() % 10;
        vb[i] = rand() % 10;
        vc[i] = 0;
    }

    // broadcastujemy rozmiar wektora i partSize do pozostałych procesów
    MPI_Bcast(&vectorSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&partSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // broadcastujemy wektor a do pozostałych procesów
    MPI_Bcast(va, partSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // broadcastujemy wektor b do pozostałych procesów
    MPI_Bcast(vb, partSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // odpalamy nasłuch
    MPI_Request* requests = new MPI_Request[size - 1];
    MPI_Status* statuses = new MPI_Status[size - 1];
    for (unsigned int i = 0; i < size - 1; i++) {
        MPI_Irecv(vc + i * partSize, partSize, MPI_UNSIGNED, i + 1, 0, MPI_COMM_WORLD, &requests[i]);
    }
    MPI_Waitall(size - 1, requests, statuses);

    // wypisujemy wyniki
    for (unsigned int i = 0; i < (partSize * (size - 1)); i++) printf("%d\t", va[i]);
    printf("\r\n");
    for (unsigned int i = 0; i < (partSize * (size - 1)); i++) printf("%d\t", vb[i]);
    printf("\r\n");
    for (unsigned int i = 0; i < (partSize * (size - 1)); i++) printf("%d\t", vc[i]);
    printf("\r\n");

    // zwalniamy pamięć
    delete[] va;
    delete[] vb;
    delete[] vc;
    delete[] requests;
    delete[] statuses;
}

void workerProcess(int id, int size) {
    int vectorSize, partSize;

    // broadcastujemy rozmiar wektora i partSize
    MPI_Bcast(&vectorSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&partSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // alokujemy buffor na moją część zadania
    unsigned int* v = new unsigned int[partSize];

    // alokujemy miejsce na wektor a oraz b
    unsigned int* va = new unsigned int[partSize * (size - 1)];
    unsigned int* vb = new unsigned int[partSize * (size - 1)];

    // nasłuchujemy bcasta wektora a
    MPI_Bcast(va, partSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // nasłuchujemy bcasta wektora b
    MPI_Bcast(vb, partSize * (size - 1), MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    // liczymyę
    for (unsigned int i = 0; i < partSize; i++) {
        v[i] = va[(id - 1) * partSize + i] + vb[(id - 1) * partSize + i];
    }

    // odsyłamy wynik    
    MPI_Send(v, partSize, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);

    // zwalniamy pamięć
    delete[] v;
    delete[] va;
    delete[] vb;
}

int main()
{
    int PID, PCOUNT;
    int vectorSize;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &PID);
    MPI_Comm_size(MPI_COMM_WORLD, &PCOUNT);

    if (PID == 0) { // jestem procesem głównym
        std::cout << "Podaj rozmiar wektora: ";
        std::cin >> vectorSize;
        mainProcess(PCOUNT, vectorSize);
    }
    else { // jestem procesem roboczym
        workerProcess(PID, PCOUNT);
    }

    MPI_Finalize();

    return 0;
}


