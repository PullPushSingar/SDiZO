#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <conio.h>



std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
using namespace std;

struct  Config{
    string numbersFilePath;
    string outputFile;
    string algorithmName;
    string timeResultPath;
    int numberOfElements;



};

Config readCfgFile(string fileName);
vector<int> readCsvFile(string fileName);



void printIntArray(const int* arr, int n);
int* createIntArrayFromVector(const std::vector<int>& vec, int n);
void startTimer();
long long stopTimer();
void saveArrayToCsv(Config config, int arr[], int n);
void saveTimeToScv(Config config, long long time, long long numberOfIteration);
long long bubbleSort(int *arr, int n);
long long insertSort(int  *arr, int n);
long long selectionSort( int  *arr, int n);
long long cocktailSort(int  *arr, int n);
long long bogoSort(int *arr, int n);
bool isSorted(const int *arr, int n);
void progressAnimation();
// Jeszcze nie zrealizowane
long long quickSort(int *arr, int n);
long long countingSort(int *arr, int n);
long long combSort(int  *arr, int n);




int main() {

    const Config config = readCfgFile(R"(C:\Users\huber\Desktop\0STUDIA\SDIZO\SDiZO\Zadanie1\Config.cfg)");
    long long timer;
    vector<int> Numbers = readCsvFile(config.numbersFilePath);
    int *arrayOfNumbers = createIntArrayFromVector(Numbers, config.numberOfElements);
    startTimer();
    long long numberOfIterations = 0;
    std::system("cls");
    cout << "Program sortuje algorytmem " << config.algorithmName <<endl;
    cout << "Porgram sortuje " << config.numberOfElements << " liczb" <<endl;
    std::thread t(progressAnimation);


    if (config.algorithmName == "bubbleSort"){
        numberOfIterations = bubbleSort(arrayOfNumbers,config.numberOfElements);
    }
    else if (config.algorithmName == "insertSort"){
        numberOfIterations = insertSort(arrayOfNumbers,config.numberOfElements);
    }
    else if (config.algorithmName == "selectionSort"){
        numberOfIterations = selectionSort(arrayOfNumbers,config.numberOfElements);
    }
    else if (config.algorithmName == "cocktailSort"){
        numberOfIterations = cocktailSort(arrayOfNumbers,config.numberOfElements);
    }
    else if (config.algorithmName == "bogoSort"){
        numberOfIterations = bogoSort(arrayOfNumbers,config.numberOfElements);
    }


    else {
        cout << "Podano zly algorytm";
        exit(100);
    }
    timer = stopTimer();
    if(numberOfIterations != 0){
        t.detach();

    }
    if (isSorted(arrayOfNumbers,config.numberOfElements)){
        cout << "Sortowanie Przebieglo prawidlowo" << endl;
    }else {
        cout << "Sortowanie przebieglo niepoprawnie" << endl;
    }
    cout << "Sortowanie zajelo " << timer << " ns " << endl;
    cout << "Sortowanie zajelo " << numberOfIterations << " iteracji" << endl;
    saveArrayToCsv(config,arrayOfNumbers,config.numberOfElements);
    saveTimeToScv(config,timer,numberOfIterations);
    delete[] arrayOfNumbers;
    return 0;
}
Config readCfgFile(string fileName) {
    ifstream configFile(fileName);
    Config config;
    string  linia;
    if (configFile.is_open())
    {
        while(getline(configFile,linia))
        {

            if (linia.find("Plik z danymi         :") != string::npos){
            string text = "Plik z danymi         :";
            size_t  pos = linia.find(text);
            string  path = linia.erase(pos,text.length());
            config.numbersFilePath = path;
            }
            if (linia.find("Posortowane elementy  :") != string::npos){
                string text = "Posortowane elementy  :";
                size_t pos = linia.find(text);
                string  path = linia.erase(pos,text.length());
                config.outputFile = path;
            }
            if (linia.find("Algorytm:             :") != string::npos){
                string text = "Algorytm:             :";
                size_t pos = linia.find(text);
                string  alghorithm = linia.erase(pos,text.length());
                config.algorithmName = alghorithm;
            }
            if (linia.find("Rozmiar danych        :") != string::npos){
                string text = "Rozmiar danych        :";
                size_t pos = linia.find(text);
                string  elements = linia.erase(pos,text.length());
                config.numberOfElements = stoi(elements);
            }
            if (linia.find("Wyniki czasowe        :") != string::npos){
                string text = "Wyniki czasowe        :";
                size_t pos = linia.find(text);
                string  path = linia.erase(pos,text.length());
                config.timeResultPath = path;

            }

        }
        }
    else {
        std::error_code ec = std::make_error_code(std::errc::io_error);
        cout << "Nie udało się otworzyć pliku. Kod błędu: " << ec.value() << ", komunikat: " << ec.message() << endl;
        exit(0);
    }
        configFile.close();
        return config;

}
vector<int> readCsvFile(string fileName) {
    ifstream csvFile(fileName);
    vector<int> numbersVector;

    if (csvFile.is_open()) {
        string line;
        while (getline(csvFile, line)) {
            stringstream ss(line);
            string value;
            while (getline(ss, value, ',')) {
                int number = stoi(value);
                numbersVector.push_back(number);
            }
        }
    }   else {
        std::error_code ec = std::make_error_code(std::errc::io_error);
        cout << "Nie udało się otworzyć pliku. Kod błędu: " << ec.value() << ", komunikat: " << ec.message() << endl;
        exit(0);
    }
    csvFile.close();
    return numbersVector;
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
long long insertSort(int *arr, int n) {
    long long iterations = 0;
    for (int i = 1 ; i < n; i++) {
        for (int j = i - 1; i >= 0 ; i --  ){
            iterations +=1;
            if (arr[j + 1] < arr[j]){
                std::swap(arr[j + 1],arr[j]);
            }else break;
        }
    }
    return iterations;
}
long long cocktailSort(int *arr, int n) {
    int bottom = 0;
    int top = n-1;
    bool change = true;
    long long iterations = 0;
    while(change) {
        change = false;
        for (int i = bottom; i < top; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                change = true;
                iterations +=1;
            }
        }
        top = top - 1;
        for (int i = top; i > bottom; i--) {
            if (arr[i] < arr[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
                change = true;
                iterations +=1;
            }
        }
        bottom += 1;
    }
    return iterations;
}
long long selectionSort(int *arr, int n) {
    long long iterations = 0;
    for (int k = 0; k < n - 2; k++){
        int bottom = k;
        for (int i = k; i < n; i ++){
            iterations +=1;
            if (arr[i] < arr[bottom]) {
                bottom = i;
            }
            std::swap(arr[k],arr[i]);

        }

    }
   return iterations;
}
long long quickSort(int *arr, int n) {
    return 0;
}
bool isSorted(const int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}
long long bogoSort(int *arr, int n) {
    long long iterations = 0;
    while (!isSorted(arr, n)) {
        iterations +=1;
        shuffle(arr, arr+n, std::mt19937(std::random_device()()));
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
void saveArrayToCsv( Config config, int arr[], int n) {
    string path;

    path = config.outputFile + "\\" + config.algorithmName + "" + std::to_string(config.numberOfElements) + ".csv";
    std::ofstream outfile(path);
    for (int i = 0; i < n; i++) {
        outfile << arr[i];
        if (i < n - 1) {
            outfile << ",";
        }
    }
    outfile.close();
}

void saveTimeToScv(Config config, long long time, long long numberOfIteration) {
    string path;

    path = config.timeResultPath + "\\TimeAndIteration.csv";
    std::ofstream outfile;
    outfile.open(path, ios::app);
    outfile  << config.algorithmName << " " << std::to_string(config.numberOfElements) << " " << std::to_string(time) << "ns " <<std::to_string(numberOfIteration) << " iteracji" << "\n";
    outfile.close();

}

void progressAnimation() {
    std::system("cls");
    int anime = 0;
    while (true){
        system("cls");
        if (anime == 0){
            cout << "    +---+  \n";
            cout << "        |  \n";
            cout << "        |  \n";
            cout << "        |  \n";
            cout << "       === \n";
        }
        else if (anime == 1){
            cout << "    +---+  \n";
            cout << "    O   |  \n";
            cout << "        |  \n";
            cout << "        |  \n";
            cout << "       === \n";
        }
        else if (anime == 2){
            cout << "    +---+  \n";
            cout << "    O   |  \n";
            cout << "    |   |  \n";
            cout << "        |  \n";
            cout << "       === \n";
        }
        else if (anime == 3){
            cout << "    +---+  \n";
            cout << "    O   |  \n";
            cout << "   /|   |  \n";
            cout << "        |  \n";
            cout << "       === \n";
        }
        else  if (anime == 4){
            cout << "    +---+  \n";
            cout << "    O   |  \n";
            cout << "   /|\\  |  \n";
            cout << "        |  \n";
            cout << "       === \n";
        }
        else if (anime == 5){
            cout << "    +---+  \n";
            cout << "    O   |  \n";
            cout << "   /|\\  |  \n";
            cout << "   /    |  \n";
            cout << "       === \n";
        }
        else if (anime == 6){
            cout << "    +---+  \n";
            cout << "    O   |  \n";
            cout << "   /|\\  |  \n";
            cout << "   / \\  |  \n";
            cout << "       === \n";
        }else if (anime > 6) {
            anime = 0;
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));


        anime +=1;

    }
}


