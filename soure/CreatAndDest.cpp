#ifndef COMMANDPROMT_CD_
#define COMMANDPROMT_CD_

#include <cstring>
#include <unistd.h> // Include for getcwd

namespace Project_1 {
// consterter
  CommandPromt::CommandPromt() {
  
  ReadJsonFile();
  CmdType = &Project_1::CommandPromt::DynamicCommandDllFinder;
}

  CommandPromt::~CommandPromt() {
  CmdType = nullptr;
  FilterJsonValue();
  WriteJsonFile();
  DCommandData.clear();
  CommandSet.clear();
}

}

#endif