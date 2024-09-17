#include "./header/CommandPromt.hpp"
#include "./soure/CreatAndDest.cpp"
#include "./soure/ScreenInput.cpp"
#include "./soure/JsonReader.cpp"
#include "./soure/CommandFinder.cpp"
#include "./soure/StaticCommand.cpp"
#include "./soure/staticFunction.cpp"

// using namespace std;
BOOL WINAPI consoleHandler(DWORD);

int main(int argc, char const *argv[])
{

    Project_1::CommandPromt Screen1;

    // SetConsoleCtrlHandler(&consoleHandler, true);        // heandle Ctrl + c signal
    
    static std::string command;
    do
    {
        Project_1::CommandPromt::Dirtory();
        Screen1.InputString(command); 

        if (!command.empty())
        Screen1.CommandHandler(command);
        
    } while (true);

    return 0;
}

BOOL WINAPI consoleHandler(DWORD signal){
    switch (signal)
    {
    case CTRL_C_EVENT:
        std::cin.clear();
        std::cout<<"^C\n";
        // ExitProcess(0);
        break;
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        break;
    }
    return TRUE;
}