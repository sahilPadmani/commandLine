#ifndef LISTOFPRO_H
#define LISTOFPRO_H
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C"
{
#endif
    __declspec(dllexport) void __cdecl CommandMain(void *a)
    {
        HANDLE hProcessSnap;
        PROCESSENTRY32 pe32;

        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            printf("CreateToolhelp32Snapshot failed.\n");
            return;
        }

        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hProcessSnap, &pe32))
        {
            CloseHandle(hProcessSnap);
            printf("Process32First failed.\n");
            return;
        }

        printf("List of Processes:\n");
        printf("%10s %35s %10s %10s\n", "Process ID:", "Executable File:", "Threads:", "ParentID:");
        do
        {
            printf("%-10d %36s %10d %10d\n", pe32.th32ProcessID, pe32.szExeFile, pe32.cntThreads, pe32.th32ParentProcessID);
        } while (Process32Next(hProcessSnap, &pe32));
        CloseHandle(hProcessSnap);
    }
#ifdef __cplusplus
}
#endif
#endif