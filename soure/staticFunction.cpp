#ifndef STATICFUNCTION_
#define STATICFUNCTION_

namespace Project_1 {


//error function
static void ErrorInDynamicCommand(const std::string &ErrorMassage) {

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

  std::cout << "Error :" << ErrorMassage << '\n';

  SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED |
                                        FOREGROUND_GREEN | FOREGROUND_BLUE);
}


// Restart App
static void Restart(void) {

  char szPath[MAX_PATH];
  GetModuleFileNameA(NULL, szPath, MAX_PATH);

  // Create a new process
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb = sizeof(STARTUPINFO);

  MessageBoxA(NULL, "     Restart the Process :)       ", "System Restart",
              MB_OK | MB_ICONINFORMATION);

  if (CreateProcessA(szPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si,
                     &pi)) {
    // Wait for the new process to finish
    // WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Terminate the current process
    ExitProcess(0);
  }

  // Handle error

  MessageBoxA(NULL, "Failed to restart the process", "Error",
              MB_OK | MB_ICONERROR);
}

// Load Dynamic Command
static void LoadDLLFile(const std::string &DllFilePath,const std::vector<std::string>& CommandSet) {

  static HMODULE dllLoad;
  dllLoad = LoadLibraryA(DllFilePath.c_str());

  if (dllLoad == NULL) {
    ErrorInDynamicCommand("Dll Not Load In Memary.");
    return;
  }

  typedef void(__cdecl * FunCall)(const std::vector<std::string> &CammandThatIsExe);

  FunCall Command_exe = (FunCall)GetProcAddress(dllLoad, "CommandMain");

  if (Command_exe == NULL) {
    ErrorInDynamicCommand("Dll Function is invalid.");
    FreeLibrary(dllLoad);
    return;
  }
  try {
    Command_exe(CommandSet);
  } catch (const std::exception& a) {
    ErrorInDynamicCommand(a.what());  
  }
  FreeLibrary(dllLoad);
}


}

#endif