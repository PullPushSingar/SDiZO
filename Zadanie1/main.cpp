#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>

std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
using namespace std;
vector<int> readCsvFile(string fileName);
void printIntArray(const int* arr, int n);
int* createIntArrayFromVector(const std::vector<int>& vec, int n);
void bubbleSort(int* arr, int n);
void startTimer();
long long stopTimer();
void saveArrayToCsv(const std::string& filename, int arr[], int n);

int main() {


    long long timer;
    vector<int> Numbers = readCsvFile(R"(C:\Users\huber\Desktop\0STUDIA\SDIZO\SDiZO\Zadanie1\liczby.txt)");
    int *arrayOfNumbers = createIntArrayFromVector(Numbers, 100000);
    startTimer();
  //  printIntArray(arrayOfNumbers,1000000);
    bubbleSort(arrayOfNumbers, 100000);
   // printIntArray(arrayOfNumbers,1000000);
    timer = stopTimer();
    cout << "Sortowanie zajelo " << timer << "ns" ;
    saveArrayToCsv("Wynik.csv",arrayOfNumbers,100000);


    delete[] arrayOfNumbers;
    return 0;
}
vector<int> readCsvFile(string fileName) {
    ifstream plik(fileName);
    vector<int> liczby;

    if (plik.is_open()) {
        string linia;
        while (getline(plik, linia)) {
            stringstream ss(linia);
            string wartosc;
            while (getline(ss, wartosc, ',')) {
                int liczba = stoi(wartosc);
                liczby.push_back(liczba);
            }
        }
    }   else {
        std::error_code ec = std::make_error_code(std::errc::io_error);
        cout << "Nie udało się otworzyć pliku. Kod błędu: " << ec.value() << ", komunikat: " << ec.message() << endl;
        exit(0);
    }
    plik.close();
    return liczby;
}

int* createIntArrayFromVector(const std::vector<int>& vec, int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = vec[i];
    }
    return arr;
}

void printIntArray(const int* arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void bubbleSort(int* arr, int n) {
    bool swapped;
    for (int i = 0; i < n-1; i++) {
        swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void startTimer() {
    start_time = std::chrono::high_resolution_clock::now();
}

long long stopTimer() {
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    return elapsed_time;
}

void saveArrayToCsv(const std::string& filename, int arr[], int n) {
    std::ofstream outfile(filename);

    for (int i = 0; i < n; i++) {
        outfile << arr[i];
        if (i < n - 1) {
            outfile << ",";
        }
    }

    outfile.close();
}
