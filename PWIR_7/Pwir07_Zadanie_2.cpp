#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

// funkcja do mno¿enia dwóch macierzy
void mnozenieMacierzowe(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int start, int koniec) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();

    for (int i = start; i < koniec; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = 0;
            for (int k = 0; k < p; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// funkcja do mno¿enia dwóch macierzy z u¿yciem wielu w¹tków
vector<vector<int>> zrownoleglenieMnozenia(const vector<vector<int>>& A, const vector<vector<int>>& B, int num_threads) {
    int n = A.size();
    int m = B[0].size();
    vector<vector<int>> C(n, vector<int>(m, 0)); // utwórz macierz wynikow¹
    int wiersze_na_thread = n / num_threads; // podziel macierz na równe bloki
    vector<thread> threads(num_threads);

    for (int t = 0; t < num_threads; t++) {
        int start = t * wiersze_na_thread;
        int koniec = (t == num_threads - 1) ? n : start + wiersze_na_thread;
        threads[t] = thread(mnozenieMacierzowe, ref(A), ref(B), ref(C), start, koniec);
    }

    for (int t = 0; t < num_threads; t++) {
        threads[t].join();
    }

    return C;
}

// funkcja do wyœwietlania macierzy
void wyswietlMacierz(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int main() {
    //vector<vector<int>> macierz_A = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    //vector<vector<int>> macierz_B = {{9, 8, 7},{6, 5, 4},{3, 2, 1}};
    vector<vector<int>> macierz_A = {{11, 22, 33},{44, 55, 66},{77, 88, 99}};
    vector<vector<int>> macierz_B = {{99, 88, 77},{66, 55, 44},{33, 22, 11}};
    auto start = chrono::steady_clock::now();
    vector<vector<int>> wynik = zrownoleglenieMnozenia(macierz_A, macierz_B, 4); // wykonaj mno¿enie macierzowe z u¿yciem 4 w¹tków
    auto end = chrono::steady_clock::now();
    printf("Czas trwania [MS] : %llu\n", chrono::duration_cast<chrono::milliseconds>(end - start).count());
    wyswietlMacierz(wynik); // wyœwietl macierz wynikow¹

    return 0;
}