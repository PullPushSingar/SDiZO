#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <conio.h>

std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
const long long  TIME_STOP_NANO_SECONDS = 600000000000;
using namespace std;



const int INF = numeric_limits<int>::max();

struct  Config{
    string numbersFilePath;
    string outputFile;
    string algorithmName;
    string timeResultPath;
    int numberOfElements;





};

struct Vertex {
    int distance;
    vector<int> path;
};
Config readCfgFile(string fileName);
void saveResultsToCsv(Config config, vector<string> paths);
void saveTimeToScv(Config config, long long time);
void progressAnimation();
void checkTime();
void startTimer();
long long stopTimer();
int **createIntArrayFromVector(const std::vector<int>& vec,const int n);
vector<int> readCsvFile(string fileName);
int findMinialCost(Vertex* Vertexs, bool* isVisited, int graphSize);
std::vector<string> printShortestPath(Vertex* Vertexs, int source, int graphSize);
Vertex*  dijkstra(int** graph, int source, int graphSize);


int main() {
    const Config cfg = readCfgFile(R"(..\Config.cfg)");
    long long time = 0;


    std::vector<int> vectorGrapg = readCsvFile(cfg.numbersFilePath);

    int ** graph = createIntArrayFromVector(vectorGrapg,cfg.numberOfElements);



    int source = 0;


    startTimer();
    std::thread animationThread(progressAnimation);
    std::thread timeStopThread(checkTime);
    Vertex* vertexs = dijkstra(graph, source, cfg.numberOfElements);

    std::vector<string> paths = printShortestPath(vertexs,source,cfg.numberOfElements);
    saveResultsToCsv(cfg,paths);
    time = stopTimer();
    saveTimeToScv(cfg,time);
    timeStopThread.detach();
    animationThread.detach();





    for (int i = 0; i < cfg.numberOfElements; ++i)
        delete[] graph[i];
    delete[] graph;

    delete[] vertexs;

    cout << "Zakończono program naciśnij aby kontynuować " << endl;
    cout << "Nacisnij dwukrotnie Enter aby zakonczyc program " << endl;
    ::getchar();

    return 0;
}

void saveResultsToCsv(Config config, vector<string> paths) {
    string path;

    path = config.outputFile + "\\" + config.algorithmName + "" + std::to_string(config.numberOfElements) + ".CSV";
    std::ofstream outfile;
    outfile.open(path,ios::app);
    for (string str : paths) {
        outfile << str << endl;
    }
    outfile.close();
}
void saveTimeToScv(Config config, long long time) {
    string path;

    path = config.timeResultPath + "\\TimeAndPaths.csv";
    std::ofstream outfile;
    outfile.open(path, ios::app);
    outfile  << config.algorithmName << " " << std::to_string(config.numberOfElements) << " " << std::to_string(time) << "ns" << "\n";
    outfile.close();

}

void progressAnimation() {


    int anime = 0;
    while (true){

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

        std::this_thread::sleep_for(std::chrono::seconds(10));


        anime +=1;


        system("cls");

    }
}
void checkTime() {
    long long checkTimer = stopTimer();
    while (checkTimer >= TIME_STOP_NANO_SECONDS) {
        cout << "Upłyneło 10 minut zatem program zostanie zatrzymany" << endl;
        exit(EXIT_FAILURE);


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

int **createIntArrayFromVector(const std::vector<int>& vec,const int n) {
    const int rows = n;
    const int cols = n;
    int ** arr = new int*[rows];
    for (int i = 0; i < rows; ++i){
        arr[i] = new int[cols];
    }

    for (int i = 0;  i < rows; i++){
        for (int j = 0;  j < cols; j++)
            arr[i][j] = vec[i * n + j];

    }


    return arr;
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


int findMinialCost(Vertex* Vertexs, bool* isVisited, int graphSize) {
    int minCost = INF;
    int minIndex = -1;

    for (int v = 0; v < graphSize; ++v) {
        if (!isVisited[v] && Vertexs[v].distance <= minCost) {
            minCost = Vertexs[v].distance;
            minIndex = v;
        }
    }

    return minIndex;
}


std::vector<string> printShortestPath(Vertex* Vertexs, int source, int graphSize) {
    std::vector<string> paths;
    string  path;
    string distance;
    string iterator;
     paths.emplace_back("Wierzcholek      Odleglosc od zrodla      Sciezka");
    for (int i = 0; i < graphSize; ++i) {

        distance = std::to_string(Vertexs[i].distance);
        iterator = std::to_string(i);


        for (int j = 0; j < Vertexs[i].path.size(); ++j)
            if (j < Vertexs[i].path.size() - 1) {

                path += std::to_string(Vertexs[i].path[j]);
                path += " -> ";


            }
            else {

                path += std::to_string(Vertexs[i].path[j]);

            }

        string result = iterator += "                " + distance += "                        " + path;
        paths.push_back(result);
        path = "";
        result = "";
    }
    return paths;
}

Vertex*  dijkstra(int** graph, int source, int graphSize) {
    Vertex* vertexs = new Vertex[graphSize];
    bool* isVisited = new bool[graphSize];


    for (int i = 0; i < graphSize; ++i) {
        vertexs[i].distance = INF;
        isVisited[i] = false;
    }


    vertexs[source].distance = 0;
    vertexs[source].path.push_back(source);

    for (int count = 0; count < graphSize - 1; ++count) {
        int u = findMinialCost(vertexs, isVisited, graphSize);


        isVisited[u] = true;


        for (int v = 0; v < graphSize; ++v) {
            if (!isVisited[v] && graph[u][v] && vertexs[u].distance != INF &&
                vertexs[u].distance + graph[u][v] < vertexs[v].distance) {
                vertexs[v].distance = vertexs[u].distance + graph[u][v];
                vertexs[v].path = vertexs[u].path;
                vertexs[v].path.push_back(v);
            }
        }
    }


    delete[] isVisited;

    return vertexs;
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
            if (linia.find("Wyliczona sciezka     :") != string::npos){
                string text = "Wyliczona sciezka     :";
                size_t pos = linia.find(text);
                string  path = linia.erase(pos,text.length());
                config.outputFile = path;
            }
            if (linia.find("Algorytm              :") != string::npos){
                string text = "Algorytm              :";
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






