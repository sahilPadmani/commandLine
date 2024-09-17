#ifndef PRINT_H
#define PRINT_H
#include <iostream>
#include <vector>
#ifdef __cplusplus
extern "C"
{
#endif
    __declspec(dllexport) void __cdecl CommandMain(const std::vector<std::string> &Printed_Line)
    {
        std::cout << Printed_Line.at(0) << '\n';
    }
#ifdef __cplusplus
}
#endif
#endif
