#include <windows.h>
#include <iostream>
#include <string>
#include <cctype>

void ConvertToUpperCase(std::string& str) {
    for (auto& ch : str) {
        ch = std::toupper(ch);
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
        ConvertToUpperCase(input);
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), input.c_str(), input.size(), &bytesRead, NULL);
    }
    return 0;
}
