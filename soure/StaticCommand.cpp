#ifndef STATICCOMMAND_
#define STATICCOMMAND_
namespace Project_1 {


inline void CommandPromt::FilterJsonValue(void) {
  // Remove the keys that have been updated
  for (const std::string &key : ChangeCommandValue) {
    DCommandData.removeMember(key);
  }
  // Clear the list of updated keys
  ChangeCommandValue.clear();
}

inline void CommandPromt::ChangeJsonValueCommand(void) {

  if (CommandSet.size() != 3) {
    ErrorInDynamicCommand("Too Many Command Found.This is Invalid.");
    return;
  }

  word = CommandSet.at(1);

  if (!DCommandData.isMember(word)) {
    ErrorInDynamicCommand("Write Real Command.");
    return;
  }

  DCommandData[CommandSet.at(2)] = DCommandData[word];

  // Keep track of the updated key
  ChangeCommandValue.push_back(CommandSet.at(2));
  std::cout << "Change This Command ->" << word << " To " << CommandSet.at(2) << '\n';
}


// Update File in RUN TIME
void CommandPromt::processDirectory(const std::string &directory) {
    WIN32_FIND_DATA fileData;
    HANDLE hFind;
    std::string searchPath = directory + "/*.json";
    hFind = FindFirstFile(searchPath.c_str(), &fileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string filename = fileData.cFileName;
            if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                // Check if the file is a JSON file
                size_t pos = filename.find_last_of(".");
                if (pos != std::string::npos && filename.substr(pos) == ".json") {
                    // Read and merge JSON data
                    mergeJsonFromFile(directory + "/" + filename);
                }
            }
        } while (FindNextFile(hFind, &fileData) != 0);
        FindClose(hFind);
    }
}

inline void CommandPromt::mergeJsonObjects(Json::Value &dest, const Json::Value &src) {
    for (const auto &key : src.getMemberNames()) {
        if (dest.isMember(key)) {
            if (dest[key].isObject() && src[key].isObject()) {
                // Merge objects recursively
                mergeJsonObjects(dest[key], src[key]);
            } else {
                // Overwrite value if it's not an object
                dest[key] = src[key];
            }
        } else {
            // Add new key-value pair
            dest[key] = src[key];
        }
    }
}

inline void CommandPromt::mergeJsonFromFile(const std::string &filename) {
    Json::Value tempJsonValue;
    std::ifstream file(filename);
    if (!file.is_open()) {
        ErrorInDynamicCommand("Failed to open " + filename);
        return;
    }
    file >> tempJsonValue;
    file.close();

    // Merge the JSON objects
    mergeJsonObjects(DCommandData, tempJsonValue);
}

inline void CommandPromt::ProcessJsonPath(const std::string &path) {
    DWORD attrib = GetFileAttributes(path.c_str());
    if (attrib == INVALID_FILE_ATTRIBUTES) {
        ErrorInDynamicCommand("Failed to get file attributes for " + path);
        return;
    }

    if (attrib & FILE_ATTRIBUTE_DIRECTORY) {
        // Path is a directory, recursively process all JSON files
        processDirectory(path);
    } else {
        // Path is a file, merge its JSON data
        mergeJsonFromFile(path);
    }
}


}
#endif