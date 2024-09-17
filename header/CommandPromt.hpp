#ifndef PROMT_h
#define PROMT_h

#include <array>
#include <conio.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>


#define cleanCommand(Command)                                                  \
  Command.erase(0, Command.find_first_not_of(" \t"));                          \
  Command.erase(Command.find_last_not_of(" \t") + 1);


namespace Project_1 {

    static const HANDLE PhConsole =  GetStdHandle(STD_OUTPUT_HANDLE);

    static void Restart(void);
    static void LoadDLLFile(const std::string &, const std::vector<std::string> &);
    static void ErrorInDynamicCommand(const std::string &); // display error in Program

    class CommandPromt {
        enum class FlagType { NORMAL_MOD, CUSTEM_MOD };

        typedef void (Project_1::CommandPromt::*CmdProtoType)(const std::string &);
        CmdProtoType CmdType;

        // typedef void (Project_1::cammandPromt::*CallStaticCammandFuntion)(void);
        // CallStaticCammandFuntion StaticFunction[5];

        const std::array<std::string, 6> staticCommand{ "update_It", "normal_Cmd", "custem_Cmd", "change_Cammand", "Quit","Restart"};
        // Details about static cammand
        // 1). update_It      --> update cammandPromt in to RUN TIME
        // 2). normal_Cmd     --> switch cammandPromt to normal cmd
        // 3). custem_Cmd     --> switch cammandPromt to custem cmd
        // 4). change_Cammand --> change name of Dyanamic cammand only
        //                       Note: not change static cammands

        std::string word;
        Json::Value DCommandData;
        std::vector<std::string> ChangeCommandValue;
        std::vector<std::string> CommandSet;
        // std::vector<std::string> OldCommand;

        // String related
        static inline void gotoxy(const int &, const int &);
        static inline void getCursorPosition(COORD &);
        void printColourfulString(const std::string &);

        // Function that is use by static Command

        inline void FilterJsonValue(void);
        inline void ChangeJsonValueCommand(void);

        inline void ProcessJsonPath(const std::string &);
        inline void mergeJsonFromFile(const std::string &);
        void processDirectory(const std::string &);
        inline void mergeJsonObjects(Json::Value &, const Json::Value &);

        inline void ReadJsonFile(void);
        inline void WriteJsonFile(void);

        inline void Systemcommand(const std::string &);
        inline int StaticCommandFinder(const std::string &); // find static command  if exsit
        void DynamicCommandDllFinder(const std::string &);

        inline void MakeVetorSet(const std::string &); // make vector set

    public:
        CommandPromt();
        ~CommandPromt();

        static void Dirtory(void); // Give Current Dirtory
        void InputString(std::string &);

        void CommandHandler(const std::string &); // Find Cammand is Static or Dy..
    };
} // namespace Project_1

#endif