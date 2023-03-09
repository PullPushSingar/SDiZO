#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>


std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
using namespace std;

struct  Config{
    string numbersFilePath;
    string outputFile;
    string algorithmName;
    int numberOfElements;



};

Config readCfgFile(string fileName);



vector<int> readCsvFile(string fileName);
void printIntArray(const int* arr, int n);
int* createIntArrayFromVector(const std::vector<int>& vec, int n);
void startTimer();
long long stopTimer();
void saveArrayToCsv(const std::string& filename, int arr[], int n);
long long bubbleSort(int arr[], int n);



int main() {

    Config config = readCfgFile(R"(C:\Users\huber\Desktop\0STUDIA\SDIZO\SDiZO\Zadanie1\Config.cfg)");
//    cout << config.numberOfElements << endl;
//    cout << config.algorithmName << endl;

//    cout << config.numbersFilePath << endl;
//    cout << config.outputFile << endl;
//    cout << config.algorithmName << endl;
//    cout << config.numberOfElements << endl;



//    long long timer;
//    vector<int> Numbers = readCsvFile(R"(C:\Users\huber\Desktop\0STUDIA\SDIZO\SDiZO\Zadanie1\liczby.txt)");
//    int *arrayOfNumbers = createIntArrayFromVector(Numbers, 100000);
//    startTimer();
//  //  printIntArray(arrayOfNumbers,1000000);
//     long long  numberOfIterations =  bubbleSort(arrayOfNumbers, 100000);
//   // printIntArray(arrayOfNumbers,1000000);
//    timer = stopTimer();
//    cout << "Sortowanie zajelo " << timer << " ns " << " oraz " << numberOfIterations << " iteracji";
//    saveArrayToCsv(R"(C:\Users\huber\Desktop\0STUDIA\SDIZO\SDiZO\Zadanie1\Wynik.csv)",arrayOfNumbers,100000);
//
//
//    delete[] arrayOfNumbers;
//    return 0;
}

Config readCfgFile(string fileName) {
    ifstream configFile(fileName);
    Config config;
    if (configFile.is_open())
    {

        string linia;
        while(getline(configFile,linia))
        {

            if (linia.find("Plik z danymi    :") != string::npos){

            string text = "Plik z danymi    :";
            size_t pos = linia.find(text);

            string  path = linia.erase(pos,text.length());
            config.numbersFilePath = path;
            cout << path;
            }
            if (linia.find("Plik z wynikami  :") != string::npos){
                string text = "Plik z wynikami  :";
                size_t pos = linia.find(text);
                string  path = linia.erase(pos,text.length());
                config.outputFile = path;
            }
            if (linia.find("Algorytm:        :") != string::npos){
                string text = "Algorytm:        :";
                size_t pos = linia.find(text);
                string  alghorithm = linia.erase(pos,text.length());
                config.algorithmName = alghorithm;
            }
            if (linia.find("Rozmiar danych   :") != string::npos){
                string text = "Rozmiar danych   :";
                size_t pos = linia.find(text);
                string  elements = linia.erase(pos,text.length());
                config.numberOfElements = stoi(elements);
            }

        }

        }

//        cout << config.numbersFilePath << endl;
//        cout << config.outputFile << endl;
//        cout << config.algorithmName << endl;
//        cout << config.numberOfElements << endl;




        else{
        std::error_code ec = std::make_error_code(std::errc::io_error);
        cout << "Nie udało się otworzyć pliku. Kod błędu: " << ec.value()<< ", komunikat: " << ec.message()<<endl;
        exit(0);
        return config;

}


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


long long bubbleSort(int arr[], int n) {
    long long  iterations = 0;
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
            iterations++;
        }
        if (swapped == false) {
            break;
        }
    }

    return iterations;
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
