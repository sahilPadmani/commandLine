#ifndef COLOR_H
#define COLOR_H
#include<stdlib.h>
#include <vector>
#include<string>
#ifdef __cplusplus
extern "C"{
#endif
    __declspec(dllexport) void __cdecl CommandMain(const std::vector<std::string>& a){
        std::string COLOR = "color ";
        COLOR = COLOR + a.at(0);
        system(COLOR.c_str());
    }
#ifdef __cplusplus
}
#endif
#endif