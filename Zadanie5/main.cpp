#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>


using namespace std;
std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
const long long  TIME_STOP_NANO_SECONDS = 600000000000;


struct  Config{
    string numbersFilePath;
    string outputFile;
    string structureName;
    string timeResultPath;

    int numberOfElements;



};
struct BSTNode
{
    BSTNode *up, *left, *right;
    int key;
};
string cr, cl, cp;
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
            if (linia.find("Struktura Danych      :") != string::npos){
                string text = "Struktura Danych      :";
                size_t pos = linia.find(text);
                string  dataStructure = linia.erase(pos, text.length());
                config.structureName = dataStructure;
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
void startTimer() {
    start_time = std::chrono::high_resolution_clock::now();
}
long long stopTimer() {
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    return elapsed_time;
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
int* allocateIntArray(int n) {
    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        array[i] = 0;
    }
    return array;
}
int* createIntArrayFromVector(const std::vector<int>& vec,const  int & n) {
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
void copyVectorToArray(const std::vector<int>& numbers, int* array, int &n) {
    for (int i = 0; i < n; i++) {
        array[i] = numbers[i];
    }
}
void printBT(string sp, string sn, BSTNode *v)
{
    string s;

    if (v)
    {
        s = sp;
        if (sn == cr)
            s[s.length() - 2] = ' ';
        printBT(s + cp, cr, v->right);

        s = s.substr(0, sp.length() - 2);
        cout << s << sn << v->key << endl;

        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printBT(s + cp, cl, v->left);
    }
}
void DFSRelease(BSTNode *v)
{
    if (v)
    {
        DFSRelease(v->left);
        DFSRelease(v->right);
        delete v;
    }
}
void insertBST(BSTNode *&root, int k)
{
    BSTNode *w, *p;

    w = new BSTNode;
    w->left = w->right = NULL;

    p = root;

    if (!p)
        root = w;
    else
        while (true)
            if (k < p->key)
            {
                if (!p->left)
                {
                    p->left = w;
                    break;
                }
                else
                    p = p->left;
            }
            else
            {
                if (!p->right)
                {
                    p->right = w;
                    break;
                }
                else
                    p = p->right;
            }

    w->up = p;
    w->key = k;
}
void rot_L(BSTNode *&root, BSTNode *A)
{
    BSTNode *B = A->right, *p = A->up;

    if (B)
    {
        A->right = B->left;
        if (A->right)
            A->right->up = A;

        B->left = A;
        B->up = p;
        A->up = B;

        if (p)
        {
            if (p->left == A)
                p->left = B;
            else
                p->right = B;
        }
        else
            root = B;
    }
}
void rot_R(BSTNode *&root, BSTNode *A)
{
    BSTNode *B = A->left, *p = A->up;

    if (B)
    {
        A->left = B->right;
        if (A->left)
            A->left->up = A;

        B->right = A;
        B->up = p;
        A->up = B;

        if (p)
        {
            if (p->left == A)
                p->left = B;
            else
                p->right = B;
        }
        else
            root = B;
    }
}
unsigned log2(unsigned x)
{
    unsigned y = 1;

    while ((x >>= 1) > 0)
        y <<= 1;

    return y;
}
void rebalanceDSW(BSTNode *&root)
{
    unsigned n, i, s;
    BSTNode *p;

    n = 0;
    p = root;
    while (p)
        if (p->left)
        {
            rot_R(root, p);
            p = p->up;
        }
        else
        {
            n++;
            p = p->right;
        }

    s = n + 1 - log2(n + 1);
   // cout<<s<<endl;

    p = root;
    for (i = 0; i < s; i++)
    {
        rot_L(root, p);
        p = p->up->right;
    }

    n -= s;
   // cout<<n<<endl;

    while (n > 1)
    {
        n >>= 1;
        p = root;
        for (i = 0; i < n; i++)
        {
            rot_L(root, p);
            p = p->up->right;
        }
    //    cout<<n<<endl;
    }
}
void addElement(BSTNode *&root)
{
    int key;
    cout << "Podaj klucz elementu do dodania: ";
    cin >> key;
    insertBST(root, key);
    cout << "Element dodany." << endl;
}
void removeElement(BSTNode *&root)
{
    int key;
    cout << "Podaj klucz elementu do usuniecia: ";
    cin >> key;

    BSTNode *node = root;
    BSTNode *parent = NULL;

    while (node)
    {
        if (node->key == key)
            break;
        parent = node;

        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    if (!node)
    {
        cout << "Element o podanym kluczu nie istnieje." << endl;
        return;
    }

    if (!node->left && !node->right)
    {
        if (parent)
        {
            if (parent->left == node)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else
        {
            root = NULL;
        }

        delete node;
    }
    else if (node->left && !node->right)
    {
        BSTNode *child = node->left;
        if (parent)
        {
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
        else
        {
            root = child;
        }
        child->up = parent;
        delete node;
    }
    else if (!node->left && node->right)
    {
        BSTNode *child = node->right;
        if (parent)
        {
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
        else
        {
            root = child;
        }
        child->up = parent;
        delete node;
    }
    else
    {
        BSTNode *successor = node->right;
        while (successor->left)
            successor = successor->left;

        node->key = successor->key;

        if (successor->up->left == successor)
            successor->up->left = successor->right;
        else
            successor->up->right = successor->right;

        if (successor->right)
            successor->right->up = successor->up;

        delete successor;
    }

    cout << "Element usuniety." << endl;
}
void searchElement(BSTNode *root)
{
    int key;
    cout << "Podaj klucz elementu do wyszukania: ";
    cin >> key;

    BSTNode *node = root;

    while (node)
    {
        if (node->key == key)
        {
            cout << "Element o podanym kluczu znajduje sie w drzewie." << endl;
            return;
        }
        else if (key < node->key)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }

    cout << "Element o podanym kluczu nie istnieje." << endl;
}
void displayMenu()
{
    cout << "1. Dodaj element" << endl;
    cout << "2. Usun element" << endl;
    cout << "3. Wyszukaj element" << endl;
    cout << "4. Wyswietl drzewo" << endl;
    cout << "5. Zrownowaz drzewo" << endl;
    cout << "6. Zakoncz program" << endl;
    cout << "Wybierz opcje: ";
}
void saveTimeToScv(Config config, long long time) {
    string path;

    path = config.timeResultPath + "\\TimeAndIteration.csv";
    std::ofstream outfile;
    outfile.open(path, ios::app);
    outfile  << config.structureName << " " << std::to_string(config.numberOfElements) << " " << std::to_string(time) << "ns "  << "\n";
    outfile.close();

}
int main()
{

    int choice;
    BSTNode *root = NULL;


    const Config config = readCfgFile(R"(..\Config.cfg)");
    long long timer;
    std::vector<int> numbers = readCsvFile(config.numbersFilePath);
    int* arr = createIntArrayFromVector(numbers,config.numberOfElements);
    std::thread animationThread(progressAnimation);
    std::thread timeStopThread(checkTime);
    startTimer();
    for (int i = 0; i < config.numberOfElements; i++) {
        insertBST(root, arr[i]);
    }
    timer = stopTimer();
    saveTimeToScv(config,timer);


//    int n = 100;
//
//    int* array = allocateIntArray(n);
//    array = createIntArrayFromVector(numbers,n);
//
//
//   for (int i = 0; i < n; i++) {
//       insertBST(root,array[i]);
//    }
//    rebalanceDSW(root);
    //searchElement(root);







//    cr = cl = cp = "  ";
//    cr[0] = 218;
//    cr[1] = 196;
//    cl[0] = 192;
//    cl[1] = 196;
//    cp[0] = 179;
//
//    srand(time(NULL));
//
//
//
//    while (true)
//    {
//        displayMenu();
//        cin >> choice;
//
//        switch (choice)
//        {
//            case 1:
//                addElement(root);
//                break;
//            case 2:
//                removeElement(root);
//                break;
//            case 3:
//                searchElement(root);
//                break;
//            case 4:
//                cout << endl;
//                printBT("", "", root);
//                cout << endl;
//                break;
//            case 5:
//                cout << endl;
//                rebalanceDSW ( root );
//                printBT("", "", root);
//                cout << endl;
//                break;
//            case 6:
//                DFSRelease(root);
//                return 0;
//            default:
//                cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
//                break;
//        }
//    }

    delete[] arr;
    return 0;
}
