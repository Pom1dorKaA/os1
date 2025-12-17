#pragma once
#include <windows.h>

enum ProcessRole {
    IS_PARENT,
    IS_CHILD
};

ProcessRole ProcessCreate();
int PipeCreate(HANDLE& hReadPipe, HANDLE& hWritePipe);
int PipeRead(HANDLE hPipe, void* buf, size_t count);
int PipeWrite(HANDLE hPipe, const void* buf, size_t count);
void PipeClose(HANDLE hPipe);
