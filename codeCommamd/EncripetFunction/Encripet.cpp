#ifndef ENCRIPT_H
#define ENCRIPT_H
#include <cmath>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define DIR_SEPARATOR '/'


#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>

#endif

void encryptFile(const std::string &filePath, const int bit_shift = 1) {
  std::ifstream file;
  std::ofstream tempfile;
  std::string tempFilepath = "temp.txt";
  std::string tempFileName =
      filePath.substr(filePath.find_last_of(DIR_SEPARATOR) + 1);

  try {
    file.open(filePath, std::ios::binary);
    tempfile.open(tempFilepath, std::ios::binary);
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return;
  }

  char byte;
  size_t HashBytes =
      std::_Hash_bytes(tempFileName.c_str(), tempFileName.size() % 10,
                       pow(tempFileName.size(), M_PI_2));
  std::string HashBytes_string = std::to_string(HashBytes);
  int i = 0;
  int sizeofst = HashBytes_string.size();

  while (file.get(byte)) {
    int temp = (i++) % sizeofst;
    byte += bit_shift * (HashBytes_string.at(temp) - '0');
    tempfile.put(byte);
  }

  file.close();
  tempfile.close();

  file.open(tempFilepath, std::ios::binary );
  tempfile.open(filePath, std::ios::binary );

  while (file.get(byte)) {
    tempfile.put(byte);
  }

  file.close();
  tempfile.close();

  remove(tempFilepath.c_str());
}

#ifdef _WIN32
void DirReader(const std::string &DirPath, const int FLAG = 1) {
  WIN32_FIND_DATA fileData;
  HANDLE hFind;

  std::string searchPath = DirPath + "/*";
  hFind = FindFirstFile(searchPath.c_str(), &fileData);
  if (hFind != INVALID_HANDLE_VALUE) {
    do {
      std::string filename = fileData.cFileName;
      if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        if (filename != "." && filename != "..") {
          DirReader(DirPath + "/" + filename, FLAG);
        }
      } else {
        encryptFile(DirPath + "/" + filename, FLAG);
      }
    } while (FindNextFile(hFind, &fileData) != 0);
    FindClose(hFind);
  }else
    std::cout<<"Error : Not File or Dir " + DirPath <<std::endl;
}
#else
void DirReader(const std::string &DirPath, const int FLAG = 1) {
  DIR *dir = opendir(DirPath.c_str());
  if (dir != nullptr) {
    dirent *dir_enter;
    while ((dir_enter = readdir(dir)) != nullptr) {
      std::string filename = dir_enter->d_name;
      if (dir_enter->d_type == DT_REG) {
        encryptFile(DirPath + "/" + filename, FLAG);
      } else if (dir_enter->d_type == DT_DIR && filename != "." &&
                 filename != "..") {
        DirReader(DirPath + "/" + filename, FLAG);
      }
    }
    closedir(dir);
  }
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
__declspec(dllexport) void  __cdecl CommandMain(const std::vector<std::string>& ItemPath) {

  int FLAG = 1;
  int point  = 0 ;

  if (ItemPath.at(0) == "-d") {FLAG = -1;point = 1;}

  // Check if filepath represents a file

#ifdef _WIN32
  DWORD dwAttrib = GetFileAttributesA(ItemPath.at(point).c_str());
  if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
      !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
    encryptFile(ItemPath.at(point), FLAG);
    return ;
  }
#else
  struct stat st;
  if (stat(filepath.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
    encryptFile(ItemPath.at(point), FLAG);
    return;
  }
#endif

  // If not a file, continue to process as directory
  DirReader(ItemPath.at(point), FLAG);
}
#ifdef __cplusplus
}
#endif

#endif