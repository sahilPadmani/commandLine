#ifndef REMOVE_H
#define REMOVE_H

#include <vector>
#include <string>
#include <iostream>
#include <filesystem> // for std::filesystem
#include <windows.h>
#include <direct.h> // for _mkdir

std::string GetErrorMessage(DWORD error) {
    LPWSTR buffer = nullptr;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr,
                   error,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   (LPWSTR)&buffer,
                   0,
                   nullptr);
    std::wstring message(buffer);
    LocalFree(buffer);
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(message);
}

void RemoveFile(const std::string &filepath) {
    std::wstring wpath = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(filepath);

    if (DeleteFileW(wpath.c_str()) == 0) {

        std::cerr << "Error: Failed to delete file '" << filepath << "': " << GetErrorMessage(GetLastError()) << std::endl;
    }
}

void RemoveDirectory(const std::string &dirpath) {
    std::wstring wpath = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(dirpath);
    
    if (RemoveDirectoryW(wpath.c_str()) == 0) {
        std::cerr << "Error: Failed to delete directory '" << dirpath << "': " << GetErrorMessage(GetLastError()) << std::endl;
    }
}

void RecursiveRemove(const std::string &path) {
    std::filesystem::path p(path);
    if (std::filesystem::is_directory(p)) {
        for (const auto &entry : std::filesystem::directory_iterator(p)) {
            if (entry.is_directory()) {
                RecursiveRemove(entry.path().string());
            } else {
                RemoveFile(entry.path().string());
            }
        }
        RemoveDirectory(p.string());
    } else {
        RemoveFile(p.string());
    }
}
#ifdef __cplusplus
extern "C"
{
#endif
    __declspec(dllexport) void  __cdecl CommandMain(std::vector<std::string>& ItemPath)
    {
        RecursiveRemove(ItemPath.at(0));
    }
#ifdef __cplusplus
}
#endif
#endif