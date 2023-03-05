#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Otwórz plik CSV do odczytu
    fstream plik("C:\\Users\\huber\\Desktop\\0STUDIA\\SDIZO\\SDiZO\\Zadanie1\\liczby.txt");

    // Sprawdź, czy plik został otwarty poprawnie
    if (!plik.is_open()) {
        std::error_code ec = std::make_error_code(std::errc::io_error);
        cout << "Nie udało się otworzyć pliku. Kod błędu: " << ec.value() << ", komunikat: " << ec.message() << endl;
        return 1;
    }

    // Utwórz wektor do przechowywania wierszy z pliku
    vector<vector<string>> wiersze;

    // Odczytaj wiersze z pliku
    string linia;
    int counter = 0;
    vector <int> liczby;
    while (getline(plik, linia)) {
        // Utwórz strumień z linii
        stringstream ss(linia);

        // Utwórz wektor do przechowywania pól z wiersza
        vector<string> pola;

        // Odczytaj pola z wiersza
        string pole;

        while (getline(ss, pole, ',')) {
            try {
                int  liczba = stoi(pole);
             //   cout << liczba << endl;
                counter +=1;
                liczby.push_back(liczba);
               // pola.push_back(pole);
            }catch (const invalid_argument& e){

            }
        }




    }
    cout << counter << endl;

    int rozmiar = liczby.size();
    int *tablicaLiczb = new int[rozmiar];
    copy(liczby.begin(),liczby.end(), tablicaLiczb);


    counter = 0;
    ofstream plik_wyjsciowy("C:\\Users\\huber\\Desktop\\0STUDIA\\SDIZO\\SDiZO\\Zadanie1\\wyjscie.csv");
    sort(tablicaLiczb,tablicaLiczb + rozmiar);
        for (int i = 0; i < rozmiar; i++) {
            plik_wyjsciowy << tablicaLiczb[i] << endl;
//            if (i != rozmiar - 1) {
//                plik_wyjsciowy << ",";
//            }
            counter += 1;
    }
    cout << counter << endl;
    plik_wyjsciowy.close();
    delete[] tablicaLiczb;

    plik.close();

    return 0;
}
