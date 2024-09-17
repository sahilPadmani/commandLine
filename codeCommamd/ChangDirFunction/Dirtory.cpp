#ifndef PRINT_H
#define PRINT_H
#include <unistd.h>
#include <vector>
#include <string>
#ifdef __cplusplus
extern "C"
{
#endif
    __declspec(dllexport) void __cdecl CommandMain(const std::vector<std::string>& ChangingDirPath)
    {
        int cheack = chdir(ChangingDirPath.at(0).c_str());
        if (cheack)printf("Your Path is not Valied \"%s\"\n", ChangingDirPath.at(0).c_str());
    }
#ifdef __cplusplus
}
#endif
#endif