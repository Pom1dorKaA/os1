#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>

void RemoveExtraSpaces(std::string& str) {
    std::istringstream stream(str);
    std::string word;
    str.clear();

    while (stream >> word) {
        if (!str.empty()) {
            str += " ";
        }
        str += word;
    }
}

int main() {
    char buffer[1024];
    DWORD bytesRead;

    while (true) {
        if (!ReadFile(GetStdHandle(STD_INPUT_HANDLE), buffer, sizeof(buffer), &bytesRead, NULL) || bytesRead == 0) {
            break;
        }

        std::string input(buffer, bytesRead);
        RemoveExtraSpaces(input);
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), input.c_str(), input.size(), &bytesRead, NULL);
    }
    return 0;
}
