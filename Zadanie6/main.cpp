#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <conio.h>
#include <sstream>

std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
const long long  TIME_STOP_NANO_SECONDS = 600000000000;
using namespace std;

struct  Config{
    string numbersFilePath;
    string outputFile;
    string algorithmName;
    string timeResultPath;
    string searchPattern;





};

void saveResultsToCsv(Config config, vector<string> paths);
void progressAnimation();
void checkTime();
void startTimer();
long long stopTimer();
Config readCfgFile(string fileName);
void computeLPS(const std::string& pattern, std::vector<int>& lps);
std::vector<string> KMP(const std::string& text, const std::string& pattern);
void saveTimeToScv(Config config, long long time);


void saveTimeToScv(Config config, long long time) {
    string path;

    path = config.timeResultPath + "\\TimeAndPaths.csv";
    std::ofstream outfile;
    outfile.open(path, ios::app);
    outfile  << config.algorithmName << " " <<config.searchPattern.length() << " " << std::to_string(time) << "ns" << "\n";
    outfile.close();

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
            if (linia.find("Znalezione wzorce     :") != string::npos){
                string text = "Znalezione wzorce     :";
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
            if (linia.find("Wzorzec do wyszukania :") != string::npos){
                string text = "Wzorzec do wyszukania :";
                size_t pos = linia.find(text);
                string  searchPattern = linia.erase(pos,text.length());
                config.searchPattern = searchPattern;
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

void computeLPS(const std::string& pattern, std::vector<int>& lps) {
    int len = 0;
    int i = 1;

    lps[0] = 0;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}



std::vector<string> KMP(const std::string& text, const std::string& pattern) {
    std::vector<int> lps(pattern.length());
    std::vector<string> patterns;

    computeLPS(pattern, lps);
    string str = "Znajduje wzorzec : " + pattern + " w wybranym pliku";
    int i = 0;
    int j = 0;
    int lineNum = 1;
    bool found = false;
    patterns.emplace_back(str);
    while (i < text.length()) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == pattern.length()) {
    //        std::cout << "Znaleziono wzorzec w linii " << lineNum << std::endl;
            str = "Znaleziono wzorzec w linii " + std::to_string(lineNum);
            patterns.push_back(str);
            j = lps[j - 1];
            found = true;
        }
        else if (i < text.length() && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }

        if (text[i] == '\n') {
            lineNum++;
        }
    }

    if (!found) {
    //    std::cout << "Wzorzec nie zostal odnaleziony w tekscie." << std::endl;
        str = "Wzorzec nie został odnaleziony w tekscie";
        patterns.push_back(str);
    }

    return patterns;
}

void saveResultsToCsv(Config config, vector<string> paths) {
    string path;

    path = config.outputFile + "\\" + config.algorithmName + "" + to_string(config.searchPattern.length()) + ".CSV";
    std::ofstream outfile;
    outfile.open(path,ios::app);
    for (string str : paths) {
        outfile << str << endl;
    }
    outfile.close();
}

int main() {
    const Config cfg = readCfgFile(R"(..\Config.cfg)");
    long long time = 0;
    std::vector<string> findLines;

    std::ifstream file(cfg.numbersFilePath);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku." << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    startTimer();
    std::thread animationThread(progressAnimation);
    std::thread timeStopThread(checkTime);
    findLines = KMP(text, cfg.searchPattern);
    time = stopTimer();
    saveResultsToCsv(cfg,findLines);
    saveTimeToScv(cfg,time);
    timeStopThread.detach();
    animationThread.detach();


    return 0;
}
