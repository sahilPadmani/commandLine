#ifndef JSONREADER_
#define JSONREADER_
#define CommandJsonFile "CommandJsonFile.json"   // <-- change it 
namespace Project_1 {

inline void CommandPromt::ReadJsonFile(void) {

  std::ifstream InputJsonFile(CommandJsonFile);
  if (!InputJsonFile.is_open()) {
    std::cerr << "Failed to open file1.json" << std::endl;
    return;
  }
  InputJsonFile >> DCommandData;
  InputJsonFile.close();
}

inline void CommandPromt::WriteJsonFile(void) {

  std::ofstream OutputJsonFile(CommandJsonFile); 

  if (!OutputJsonFile.is_open()) {
    ErrorInDynamicCommand("Json File Not writed.");
    return;
  }

  OutputJsonFile << DCommandData;
  OutputJsonFile.close();
}


}
#endif