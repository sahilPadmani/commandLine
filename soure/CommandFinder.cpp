#ifndef COMMANDFINDER_
#define COMMANDFINDER_

namespace Project_1 {

// System call
inline void  CommandPromt::Systemcommand(const std::string &command) {
  system(command.c_str());
}

void  CommandPromt::DynamicCommandDllFinder(const std::string &command) {

  word = CommandSet.at(0);

  if (!DCommandData.isMember(word)) {
    ErrorInDynamicCommand("Command did not Found.");
    return;
  }

  CommandSet.erase(CommandSet.begin());

  if (DCommandData[word]["MinElement"].asInt() > CommandSet.size()) {
    ErrorInDynamicCommand("Command did not have Minmum Element.");
    return;
  }

  if (DCommandData[word]["Type"].asInt() == 1) {
    CommandSet.clear();
    std::istringstream iss(command);
    std::string restOfCommand;
    iss >> word;
    std::getline(iss >> std::ws, restOfCommand);
    CommandSet.push_back(restOfCommand);
  }

  LoadDLLFile(DCommandData[word]["DllFilePath"].asString(), CommandSet);
}

void  CommandPromt::CommandHandler(const std::string &Command) {

  MakeVetorSet(Command);

  switch (StaticCommandFinder(CommandSet.at(0))) {
  case 0:
    if(CommandSet.size() == 1){
      // CommandPromt();
      DCommandData.clear();
      ReadJsonFile();
      break;
    }
    else if (CommandSet.size() != 2) {
      ErrorInDynamicCommand("Too Many Argument Found in Command.");
      break;
    }
    ProcessJsonPath(CommandSet.at(1));
    WriteJsonFile();
    break;
  case 1:
    CmdType = & CommandPromt::Systemcommand;
    std::cout << "Noraml Cmd on online Now.\n";
    break;
  case 2:
    CmdType = & CommandPromt::DynamicCommandDllFinder;
    std::cout << "Custem Made Cmd online Now.\n";
    break;
  case 3:
    ChangeJsonValueCommand();
    break;
  case 4:
    this->~CommandPromt();
    ExitProcess(0);
    break;
  case 5:
    // DCommandData.clear();
    Restart();
    // ReadJsonFile();
    break;
  case -1:
    (this->*CmdType)(Command);
    break;
  }
  CommandSet.clear();
}

// Make vector set of command
inline void
 CommandPromt::MakeVetorSet(const std::string &FullCommand) {

  std::istringstream iss(FullCommand);

  while (iss >> word) {
    CommandSet.push_back(word);
  }
}

// Find static command if exsit
inline int CommandPromt::StaticCommandFinder(const std::string &command) {
  int i = 0;
  for (const std::string &Static : staticCommand) {
    if (Static == command)
      return i;
    i++;
  }
  return -1;
}


}
#endif