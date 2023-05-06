#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <conio.h>
#include <queue>

const long long  TIME_STOP_NANO_SECONDS = 600000000000;
using namespace std;


struct Edge {
    int source, dest, weight;
};

struct  Config{
    string numbersFilePath;
    string outputFile;
    string algorithmName;
    string timeResultPath;
    int numberOfElements;
    int maxWeight;
    int minWeight;
    bool generateGraph;
    bool deleteEges;



};
struct DisjointSet {
    vector<int> parent;
    vector<int> weight;

    DisjointSet(int n) {
        parent.resize(n);
        weight.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            weight[i] = 0;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int source, int dest) {
        int pu = find(source);
        int pv = find(dest);
        if (pu == pv) {
            return;
        }
        if (weight[pu] > weight[pv]) {
            parent[pv] = pu;
        } else if (weight[pu] < weight[pv]) {
            parent[pu] = pv;
        } else {
            parent[pu] = pv;
            weight[pv]++;
        }
    }
};
std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

Config readCfgFile(string fileName);
vector<int> readCsvFile(string fileName);
void startTimer();
long long stopTimer();
void progressAnimation();
void checkTime();
vector<Edge> kruskal(vector<Edge>& edges, int n, Config cfg);
vector<Edge> simmetricalToEdge(int **arr, int n);
int** createIntArrayFromVector(const std::vector<int>& vec, int n);
void MSTGraphGenerator(int n, int weightMin, int weightMax, string filename);
void saveResultsToCsv(Config config, vector<string> paths);
void saveTimeToScv(Config config, long long time, int MST);
bool isGraphValid(int **graph, const int n);
int** truncateEdges(int **graph,const  int edgeCount, const int n,const Config cfg);
bool isConnected(int** graph,const int  n);
void calcuateMSTWithKruskal(const Config cfg,int ** arr);

int main() {
    const Config cfg = readCfgFile(R"(..\Config.cfg)");

    if (cfg.generateGraph){
        MSTGraphGenerator(cfg.numberOfElements,cfg.minWeight,cfg.maxWeight,R"(..\liczby.csv)");
    }
    cout << "Program szuka MST  algorytmem " << cfg.algorithmName << endl;
    cout << "Wielkosc danych to  " << cfg.numberOfElements << " liczb" << endl;
    vector<int> Numbers = readCsvFile(cfg.numbersFilePath);
    int **arr = createIntArrayFromVector(Numbers,cfg.numberOfElements);

    if(!isGraphValid(arr,cfg.numberOfElements)){
        cout << "Zakończono program z powodwu odczytania grafu w złek postaci !!!"<< endl;
    }

    if (cfg.deleteEges) {
        srand(time(0));
        int random = rand() % 9 + 1;

        arr = truncateEdges(arr, random * cfg.numberOfElements, cfg.numberOfElements,cfg);
        cout << "Program usunal " <<  random * 10 << " % krawedzi grafu" << endl;
        if (!isGraphValid(arr, cfg.numberOfElements)) {
            cout << "Zakończono program z powodwu odczytania grafu w złek postaci !!!" << endl;
        }
        calcuateMSTWithKruskal(cfg, arr);
    }else {
        calcuateMSTWithKruskal(cfg,arr);
    }



    delete[] arr;
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
            if (linia.find("Wyliczone MST         :") != string::npos){
                string text = "Wyliczone MST         :";
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
            if (linia.find("Maksymlana Waga       :") != string::npos){
                string text = "Maksymlana Waga       :";
                size_t pos = linia.find(text);
                string  maxWeight = linia.erase(pos,text.length());
                config.maxWeight = stoi(maxWeight);
            }
            if (linia.find("Minimalna Waga        :") != string::npos) {
                string text = "Minimalna Waga        :";
                size_t pos = linia.find(text);
                string minWeight = linia.erase(pos, text.length());
                config.minWeight = stoi(minWeight);
            }
            if (linia.find("Wyniki czasowe        :") != string::npos){
                string text = "Wyniki czasowe        :";
                size_t pos = linia.find(text);
                string  path = linia.erase(pos,text.length());
                config.timeResultPath = path;

            }
            if (linia.find("Generowanie Grafu     :") != string::npos){
                string text = "Generowanie Grafu     :";
                size_t pos = linia.find(text);
                string  generateGraph = linia.erase(pos,text.length());
                if (generateGraph == "Tak"){
                    config.generateGraph = true;
                }
                else if (generateGraph == "Nie"){
                    config.generateGraph = false;
                }

            }
            if (linia.find("Usuwanie krawedzi     :") != string::npos){
                string text = "Usuwanie krawedzi     :";
                size_t pos = linia.find(text);
                string  deleteEdges = linia.erase(pos,text.length());
                if (deleteEdges == "Tak"){
                    config.deleteEges = true;
                }
                else if (deleteEdges == "Nie"){
                    config.deleteEges = false;
                }

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

void startTimer() {
    start_time = std::chrono::high_resolution_clock::now();
}
long long stopTimer() {
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    return elapsed_time;
}


vector<Edge> kruskal(vector<Edge>& edges, int n, Config cfg) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    vector<string> removePaths;
    vector<string> correctlyPaths;

    DisjointSet ds(n);

    vector<Edge> mst;

    for (Edge& e : edges) {
        if (ds.find(e.source) != ds.find(e.dest)) {
            mst.push_back(e);
            ds.merge(e.source, e.dest);

            string esourceToString = std::to_string(e.source + 1);
            string edestToString = std::to_string(e.dest + 1);
            string eweightToString = std::to_string(e.weight + 1);
            string  correctPath = "Zaakceptowano ścieżke " + esourceToString += " - " + edestToString + " : " += eweightToString;
            correctlyPaths.push_back(correctPath);
        }
        else{
            string esourceToString = std::to_string(e.source + 1);
            string edestToString = std::to_string(e.dest + 1);
            string eweightToString = std::to_string(e.weight + 1);
            string  removePath = "Odrzucono sciezke " + esourceToString += " - " + edestToString + " : " += eweightToString;
            removePaths.push_back(removePath);
        }



    }

    for (string str : correctlyPaths){
        removePaths.push_back(str);
    }

    saveResultsToCsv(cfg,removePaths);

    return mst;
}
vector<Edge> simmetricalToEdge(int** arr , int n){
    vector<Edge> edges;
    for(int i = 0; i < n; i++){
        for(int j = 0;j < n; j++){
            if(arr[i][j]!=0 && j != i){
                edges.push_back({i,j,arr[i][j]});
            }

        }
    }
    return edges;
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
void MSTGraphGenerator(int n, int weightMin, int weightMax, string filename){
    int matrix[n][n];  //


    srand(time(0));


    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                int weight = rand() % (weightMax - weightMin + 1) + weightMin;
                matrix[i][j] = weight;
                matrix[j][i] = weight;
            }
        }
    }

    // Save the adjacency matrix to a CSV file
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j == n-1) {
                    file << matrix[i][j];
                } else {
                    file << matrix[i][j] << ",";
                }
            }
            file << endl;
        }
        file.close();
        cout << "Plik zostal zapisany z powodzeninem !!!" << endl;
    } else {
        cout << "Nie mozna otworzyc pliku !!!" << endl;
    }
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
void saveTimeToScv(Config config, long long time, int MST) {
    string path;

    path = config.timeResultPath + "\\TimeAndMST.csv";
    std::ofstream outfile;
    outfile.open(path, ios::app);
    outfile  << config.algorithmName << " " << std::to_string(config.numberOfElements) << " MST wynosi << " << MST  <<" " << std::to_string(time) << " ns " << "\n";
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

bool isGraphValid(int **graph, const int n) {


    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != graph[j][i]) {
                cout << "Graf nie jest w poprawnej postaci - macierz nie jest symetryczna." << endl;
                return false;
            }
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && graph[i][j] <= 0) {
                cout << "Graf nie jest w poprawnej postaci - waga krawędzi (" << i << ", " << j << ") jest niepoprawna." << endl;
                return false;
            }
        }
    }


    cout << "Graf jest w poprawnej postaci." << endl;
    return true;
}

int** truncateEdges(int **graph,const  int edgeCount, const int n,const Config cfg) {
    srand(time(0));


    for (int i = 0; i < edgeCount; i++) {
        int row = rand() % n;
        int col = rand() % n;
        graph[row][col] = 0;
        graph[col][row] = 0;

        if (isConnected(graph,n)) {
            int random = rand() + 5 % cfg.maxWeight;
            graph[row][col] = random;
            graph[col][row] = random;
        }



    }



    return graph;
}

bool isConnected(int** graph,const int  n) {
    bool* visited = new bool[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (graph[curr][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            delete[] visited;
            return false;
        }
    }

    delete[] visited;
    return true;
}

void calcuateMSTWithKruskal(const Config cfg,int ** arr){
    long long timer = 0;

    startTimer();
    std::thread animationThread(progressAnimation);
    std::thread timeStopThread(checkTime);
    vector<Edge> edges = simmetricalToEdge(arr,cfg.numberOfElements);
    vector<Edge> mst = kruskal(edges, cfg.numberOfElements,cfg);
    timer = stopTimer();

    timeStopThread.detach();
    animationThread.detach();


    cout << "Szukanie MST o wielkosci danych " << cfg.numberOfElements << " zajelo " << timer << "ns" << endl;

    int sum = 0;
    for (Edge& e : mst) {
        sum +=e.weight;
    }
    saveTimeToScv(cfg,timer,sum);
    cout << "MST : " << sum << endl;


    cout << "Nacisnij dwukrotnie Enter aby zakonczyc program " << endl;
    ::getchar();
}