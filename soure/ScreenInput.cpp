#ifndef SCREENINPUT_H
#define SCREENINPUT_H

namespace Project_1{
void CommandPromt::Dirtory() {

  SetConsoleTextAttribute(PhConsole, FOREGROUND_GREEN);

  char buffer[260] = "PS ";
  char tempbuffer[260];
  _getcwd(tempbuffer, 260);

  strcat(buffer, tempbuffer);
  strcat(buffer, ">");

  std::cout << buffer;

  SetConsoleTextAttribute(PhConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

inline void CommandPromt::gotoxy(const int &x, const int &y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(PhConsole, coord);
}

inline void CommandPromt::getCursorPosition(COORD &coord) {
  CONSOLE_SCREEN_BUFFER_INFO cursorInfo;
  GetConsoleScreenBufferInfo(PhConsole, &cursorInfo);
  coord = cursorInfo.dwCursorPosition;
}

void CommandPromt::printColourfulString(const std::string &str) {

  size_t posFirst = std::string::npos, lastPos = std::string::npos;

  for (const std::string &i : staticCommand) {
    posFirst = str.find(i);
    if (posFirst != std::string::npos) {
      lastPos = posFirst + i.size() - 1;
      goto Print;
    }
  }

  for (const std::string &i : DCommandData.getMemberNames()) {
    posFirst = str.find(i);
    if (posFirst != std::string::npos) {
      lastPos = posFirst + i.size() - 1;
      goto Print;
    }
  }

  if (posFirst == std::string::npos) {
    std::cout << str << ' ';
    return;
  }

Print:
  std::string firstSet = str.substr(0, posFirst);
  if (!firstSet.empty())
    std::cout << firstSet;

  SetConsoleTextAttribute(PhConsole,
                          FOREGROUND_RED | FOREGROUND_INTENSITY);

  std::string midSet = str.substr(posFirst, lastPos - posFirst + 1);
  if (!midSet.empty())
    std::cout << midSet;

  SetConsoleTextAttribute(PhConsole,
                          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

  std::string lastSet = str.substr(lastPos + 1);
  if (!lastSet.empty()) {
    std::cout << lastSet;
  }

  std::cout << ' ';
}

enum {
  ARROW_LEFT = 75,
  ARROW_RIGHT = 77,
  ARROW_UP = 72,
  ARROW_DOWN = 80,
};

enum { TAB = 9, BACKSPACE = 8, ENTER = 13, ARROWKEY = 224 };

void CommandPromt::InputString(std::string &command) {

  static bool isArrowKeyPressed;
  static int key, sub, currentIndex, maxIndex;
  static COORD initialCoord, currentCoord;
  static CONSOLE_SCREEN_BUFFER_INFO csbi;
  static CONSOLE_CURSOR_INFO cci;

  isArrowKeyPressed = false;
  sub = 1, currentIndex = 0, maxIndex = 0;
  command.clear();
  // static int OldPointCammand;
  // OldPointCammand =  OldCommand.size() - 1;

  GetConsoleScreenBufferInfo(PhConsole, &csbi);
  static const int consoleWidth = csbi.dwSize.X;

  initialCoord.X = csbi.dwCursorPosition.X;
  initialCoord.Y = csbi.dwCursorPosition.Y;

  do {

  StartPoint:

    key = _getch();
    getCursorPosition(currentCoord);

    if (isArrowKeyPressed) {
      isArrowKeyPressed = false;
      switch (key) {
      case ARROW_LEFT:
        if (0 < currentIndex) {
          currentIndex--;
          sub = -1;
          goto CursorSetByArrowKey;
        }
        break;
      case ARROW_RIGHT:
        if (maxIndex > currentIndex) {
          currentIndex++;
          goto CursorSetByArrowKey;
        }
        break;
        // case ARROW_UP:
        //     if( 0 <= OldPointCammand){
        //         command = OldCommand.at(OldPointCammand);
        //         currentIndex = command.size();
        //         maxIndex = currentIndex;
        //         sub = maxIndex;
        //         currentCoord = initialCoord;
        //         OldPointCammand--;
        //         goto PrintString;
        //     }
        //     break;
        }
        continue;
      }

      switch (key) {

      case ARROWKEY:
        isArrowKeyPressed = true;
        goto StartPoint;
        break;
      
      case ENTER:
        std::cout << '\n'; 
        break;

      case TAB:
        sub = 5;
        command.insert(currentIndex, 5, ' ');
        currentIndex += 5;
        maxIndex += 5;
        goto PrintString;
        break;

      case BACKSPACE:
        if (!command.empty()) {
          std::cout << "\b \b";
          currentIndex--;
          command.erase(command.begin() + currentIndex);
          maxIndex--;
          sub = -1;
          goto PrintString;
        }
        goto StartPoint;
        break;

      default:
        command.insert(command.begin() + currentIndex, key);
        currentIndex++;
        maxIndex++;

      PrintString:
        // Print the updated string
        cci.bVisible = false;
        SetConsoleCursorInfo(PhConsole,&cci);
        gotoxy(initialCoord.X, initialCoord.Y);
        printColourfulString(command);
        
        cci.bVisible = true;
        SetConsoleCursorInfo(PhConsole,&cci);

      CursorSetByArrowKey:

        // Move cursor to the correct position
        if (consoleWidth <= currentCoord.X + sub) {
          currentCoord.Y++;
          currentCoord.X = currentCoord.X + sub - consoleWidth;
          sub = 0;
        }
        gotoxy(currentCoord.X + sub, currentCoord.Y);
      }
      sub = 1;
    }
    while (key != ENTER);

    // OldCommand.push_back(command);
  }
}

#endif