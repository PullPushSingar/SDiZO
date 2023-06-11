#include <iostream>
#include <fstream>
#include <vector>

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

void KMP(const std::string& text, const std::string& pattern) {
    std::vector<int> lps(pattern.length());

    computeLPS(pattern, lps);

    int i = 0;
    int j = 0;
    int lineNum = 1;
    bool found = false;
    std::cout << "Znajduje wzorzec : \"" << pattern << "\" w pliku tekst.txt" << std::endl;
    while (i < text.length()) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == pattern.length()) {
            std::cout << "Znaleziono wzorzec w linii " << lineNum << std::endl;
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
        std::cout << "Wzorzec nie zostal odnaleziony w tekscie." << std::endl;
    }
}

int main() {
    std::ifstream file(R"(C:\Users\huber\Desktop\0STUDIA\SDIZO\SDiZO\Zadanie6\tekst.txt)");
    if (!file) {
        std::cerr << "Nie można otworzyć pliku." << std::endl;
        return 1;
    }

    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::cout << "Prosze podaj wzorzec jaki chcesz znalesc w pliku tekst.txt w tym samym folderze" << std::endl;

    std::string pattern;
    std::getline(std::cin,pattern);



    KMP(text, pattern);

    return 0;
}
