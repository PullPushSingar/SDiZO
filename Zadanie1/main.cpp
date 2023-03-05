#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    // Otwórz plik CSV do odczytu
    fstream plik("C:\\Users\\huber\\Desktop\\0STUDIA\\SDIZO\\SDiZO\\Zadanie1\\liczby.csv");

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
               // pola.push_back(pole);
            }catch (const invalid_argument& e){

            }
        }



        // Dodaj wiersz do wektora wierszy
       // wiersze.push_back(pola);
    }
    cout << counter << endl;
//    int counter = 0;
//    // Wyświetl odczytane dane
//    for (const auto& wiersz : wiersze) {
//        for (const auto& pole : wiersz) {
//            cout << pole << " ";
//            counter +=1;
//        }
//        cout << endl;
//    }
//
//    cout  << counter;

    // Zamknij plik
    plik.close();

    return 0;
}
