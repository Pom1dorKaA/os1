#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>

void CreateNamedPipe(HANDLE &hReadPipe, HANDLE &hWritePipe) {
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        std::cerr << "Error creating pipe" << std::endl;
        exit(-1);
    }
}

int main() {
    HANDLE hChild1Read, hChild1Write, hChild2Read, hChild2Write;
    CreateNamedPipe(hChild1Read, hChild1Write);
    CreateNamedPipe(hChild2Read, hChild2Write);

    PROCESS_INFORMATION piChild1, piChild2;
    STARTUPINFO siChild1, siChild2;

    ZeroMemory(&siChild1, sizeof(siChild1));
    siChild1.cb = sizeof(siChild1);
    ZeroMemory(&siChild2, sizeof(siChild2));
    siChild2.cb = sizeof(siChild2);

if (!CreateProcess(NULL, const_cast<LPSTR>("child1.exe"), NULL, NULL, TRUE, 0, NULL, NULL, &siChild1, &piChild1)) {
    std::cerr << "Error starting child1" << std::endl;
    exit(-1);
}

if (!CreateProcess(NULL, const_cast<LPSTR>("child2.exe"), NULL, NULL, TRUE, 0, NULL, NULL, &siChild2, &piChild2)) {
    std::cerr << "Error starting child2" << std::endl;
    exit(-1);
}

    std::string input;
    while (std::getline(std::cin, input)) {
        DWORD written;
        WriteFile(hChild1Write, input.c_str(), input.size(), &written, NULL);

        char buffer[1024];
        DWORD bytesRead;
        ReadFile(hChild1Read, buffer, sizeof(buffer), &bytesRead, NULL);
        WriteFile(hChild2Write, buffer, bytesRead, &written, NULL);

        ReadFile(hChild2Read, buffer, sizeof(buffer), &bytesRead, NULL);
        std::cout << "Processed Output: " << std::string(buffer, bytesRead) << std::endl;
    }

    CloseHandle(hChild1Read);
    CloseHandle(hChild1Write);
    CloseHandle(hChild2Read);
    CloseHandle(hChild2Write);

    return 0;
}
