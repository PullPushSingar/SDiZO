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

struct Bucket {
    int* Data;
    int Count;
};

const long long  TIME_STOP_NANO_SECONDS = 600000000000;

Config readCfgFile(string fileName);
vector<int> readCsvFile(string fileName);
void printIntArray(const int* arr, int n);
int* createIntArrayFromVector(const std::vector<int>& vec, int n);
void startTimer();
long long stopTimer();
void saveArrayToCsv(Config config, int arr[], int n);
void saveTimeToScv(Config config, long long time, long long numberOfIteration);
// O(N^2) sort
long long bubbleSort(int *arr, int n);
long long insertSort(int  *arr, int n);
long long selectionSort( int  *arr, int n);
long long cocktailSort(int  *arr, int n);
// O(nlgn) sort
long long heapSort(int *arr, int n);
long long quickSort(int *arr, int low , int high);
long long combSort(int  *arr, int n);
long long bucketSort(int *arr, int *bucket, int n);
long long bogoSort(int *arr, int n);
bool isSorted(const int *arr, int n);
void progressAnimation();
void checkTime();
void heapify(int *arr, int n , int i);
int partition( int arr[], int low, int high);
int getNextGap(int gab);
int getMax(int* arr, int n);
int getMin(int* arr, int n);
long long countSort(int *arr, int n);
long long bucketSort(int* arr, int n , int counter){
    int max = getMax(arr,n);
    int min = getMin(arr,n);

    int i,j,lw[max - min + 1];

    for (i = 0; i < n ;i++){
        lw[arr[i] - min]++;
    }

    j = 0;
    for (i = min; i < max; i++){

        while(lw[i - min]--){
            arr[j++] = i;
        }
        counter ++;

    }

    return  counter;
}



int main() {


        const Config config = readCfgFile(R"(..\Config.cfg)");
        long long timer;
        std::thread main_thread((std::this_thread::get_id());
        vector<int> Numbers = readCsvFile(config.numbersFilePath);
        int *arrayOfNumbers = createIntArrayFromVector(Numbers, config.numberOfElements);
        startTimer();
        long long numberOfIterations = 0;
        cout << "Program sortuje algorytmem " << config.algorithmName << endl;
        cout << "Porgram sortuje " << config.numberOfElements << " liczb" << endl;
        std::thread animationThread(progressAnimation);
        std::thread timeStopThread(checkTime);
        if (config.algorithmName == "bubbleSort") {
            numberOfIterations = bubbleSort(arrayOfNumbers, config.numberOfElements);
        } else if (config.algorithmName == "insertSort") {
            numberOfIterations = insertSort(arrayOfNumbers, config.numberOfElements);
        } else if (config.algorithmName == "selectionSort") {
            numberOfIterations = selectionSort(arrayOfNumbers, config.numberOfElements);
        } else if (config.algorithmName == "cocktailSort") {
            numberOfIterations = cocktailSort(arrayOfNumbers, config.numberOfElements);
        } else if (config.algorithmName == "bogoSort") {
            numberOfIterations = bogoSort(arrayOfNumbers, config.numberOfElements);
        } else if (config.algorithmName == "heapSort") {
            numberOfIterations = heapSort(arrayOfNumbers, config.numberOfElements);
        } else if (config.algorithmName == "quickSort") {
            int n = sizeof(int) * config.numberOfElements / sizeof(arrayOfNumbers[0]);
            numberOfIterations = quickSort(arrayOfNumbers, 0, n - 1);
        } else if (config.algorithmName == "combSort") {
            numberOfIterations = combSort(arrayOfNumbers, config.numberOfElements);
        } else if (config.algorithmName == "countingSort") {
            numberOfIterations = countSort(arrayOfNumbers, config.numberOfElements);
        } else if (config.algorithmName == "bucketSort") {
            numberOfIterations = bucketSort(arrayOfNumbers,config.numberOfElements,10);
        } else {
            cout << "Podano zly algorytm";
            exit(100);
        }
        timer = stopTimer();
        timeStopThread.detach();
        animationThread.detach();

        if (isSorted(arrayOfNumbers, config.numberOfElements)) {
            cout << "Sortowanie Przebieglo prawidlowo" << endl;
        } else {
            cout << "Sortowanie przebieglo niepoprawnie" << endl;
        }


        cout << "Sortowanie zajelo " << timer << " ns " << endl;
        cout << "Sortowanie zajelo " << numberOfIterations << " iteracji" << endl;
        saveArrayToCsv(config, arrayOfNumbers, config.numberOfElements);
        saveTimeToScv(config, timer, numberOfIterations);
        if (timer <= TIME_STOP_NANO_SECONDS/300){
            cout << "Sortowanie zajeło bardzo krótko" << endl;
            cout << "Nacisnij jaki kolwiek przycisk na klawiaturze aby kontynuowac" << endl;
            ::getchar();

        }
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
        exit(50);
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
        if (!swapped) {
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
long long quickSort(int *arr, int low, int high) {

    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
    return 2137;
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
void checkTime() {
    long long checkTimer = stopTimer();
    while (checkTimer >= TIME_STOP_NANO_SECONDS) {
            cout << "Upłyneło 10 minut zatem program zostanie zatrzymany" << endl;
            exit(EXIT_FAILURE);


    }

}
void heapify(int *arr, int n, int i) {
    int largest = i;
    int left =  2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i){
        swap(arr[i],arr[largest]);
        heapify(arr,n,largest);
    }


}
long long heapSort(int *arr, int n) {
    long long iteration = 0;

    for (int i = (n/2) - 1; i >= 0; i--) {
        heapify(arr, n, i);
        iteration +=1;

    }
    for (int i = n - 1; i >= 0; i--){
        swap(arr[0],arr[i]);
        heapify(arr,i,0);
        iteration +=1;
    }
    return  iteration;
}
int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i + 1],arr[high]);
    return (i + 1);
}
int getNextGap(int gap) {
    gap = (gap * 10)/13;

    if (gap < 1){
        return  1;
    }
    return  gap;
}
long long combSort(int *arr, int n) {
    long long iterations = 0;
    int gap = n;
    bool swapped = true;


    while ( gap != 1 || swapped == true){
        gap = getNextGap(gap);
        swapped = false;

        for (int i = 0; i < n - gap; i++){
            if (arr[i] > arr[i + gap]){
                swap(arr[i],arr[i + gap]);
                swapped = true;
                iterations +=1;
            }

        }

    }
    return iterations;
}
int getMax(int* arr, int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
int getMin(int *arr, int n) {
    int min = arr[0];

    for (int i = 1; i < n; i ++){
        if (arr[i] < min){
            min = arr[i];
        }
    }
    return  min;
}
long long countSort(int *arr, int n) {
    int min = getMin(arr,n);
    int max = getMax(arr,n);

    int size = max-min+1;
    int * tab =new int[size];
    for (int i = 0; i < size; i++)
        tab[i] = 0;
    int shift;
    if (min<0){
        shift=min;
    }else{
        shift=0;
    }
    for (int i = 0; i < n; ++i)
        tab[arr[i] - shift]++;

    for (int i = 1; i < size; ++i)
        tab[i] += tab[i-1];

//    int sortedArr[size];
    int * sortedArr =new int[n];

    for (int i = 0; i < n; ++i) {
        sortedArr[--tab[arr[i] - shift]] = arr[i];
    }

    for (int i=0; i<n;i++) {
        arr[i] = sortedArr[i];
    }

    return 2000;
}






