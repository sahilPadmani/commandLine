#ifndef PRINT_H
#define PRINT_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif
    __declspec(dllexport) void __cdecl CommandMain(const void *clear)
    {
        system("cls");
    }
#ifdef __cplusplus
}
#endif
#endif