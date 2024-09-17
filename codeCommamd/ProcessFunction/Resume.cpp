#ifndef PUSE_H
#define PUSE_H
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <string>
#ifdef __cplusplus

DWORD ProcessIdfinder(const char *process_name) {

  HANDLE hSnapshot;
  PROCESSENTRY32 pe;
  DWORD pid = 0;
  BOOL hResult;

  hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (INVALID_HANDLE_VALUE == hSnapshot) return 0;

  pe.dwSize = sizeof(PROCESSENTRY32);

  hResult = Process32First(hSnapshot, &pe);

  while (hResult) {
    if (strcmp(process_name, pe.szExeFile) == 0) {
      pid = pe.th32ProcessID;
      break;
    }
    hResult = Process32Next(hSnapshot, &pe);
  }
  CloseHandle(hSnapshot);
  return pid;
}

extern "C" 
{
#endif
    __declspec(dllexport) void __cdecl CommandMain(std::vector<std::string>& ProcessName)
    {
        DWORD processId = ProcessIdfinder(ProcessName.at(0).c_str());
        if(0 == processId)
        {
            printf("Check Process Name It is Corrrct : \"%s\" ?\n",ProcessName.at(0).c_str());
            return;
        }
        
        HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

        typedef LONG(NTAPI* NtResumeProcess)( IN HANDLE ProcessHandle );

        NtResumeProcess  pfnNtResumeProcess = (NtResumeProcess)GetProcAddress(GetModuleHandleA("ntdll"), "NtResumeProcess");

        pfnNtResumeProcess(processHandle);

        CloseHandle(processHandle);
    }

#ifdef __cplusplus
}
#endif
#endif