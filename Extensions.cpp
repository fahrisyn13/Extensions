#include "Extensions.h"
#include <time.h>
#include <conio.h>
#include <windows.h>
namespace Extensions {
  /* Class Console */
  short Console::GetDefaultColor() {
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;

    if (
      !GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &csbInfo
        )
      )
      throw std::runtime_error{ "Unable to get screen buffer info" };
    return csbInfo.wAttributes;
  }

  void Console::SetCursorPosition(
    short xPos,
    short yPos
    ) {
    if (
      !SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        {
          xPos,
          yPos
        }
        )
      )
      throw std::runtime_error{ "Unable to set cursor position" };
  }

  void Console::SetTextColor(
    ConsoleColor bgColor,
    ConsoleColor fgColor
    ) {
    if (
      !SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        (static_cast<short>(bgColor) << 4) | static_cast<short>(fgColor)
        )
      )
      throw std::runtime_error{ "Unable to change console color" };
  }

  void Console::SetTextColor(
    short color
    ) {
    if (
      !SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
        )
      )
      throw std::runtime_error{ "Unable to change console color" };
  }

  void Console::Clear() {
    system("cls");
  }

  void Console::ClearField(
    const std::string& var
    ) {
    if (var.length() > 0) {
      for (unsigned short i = 0; i < var.length(); i++)
        std::cout << ' ';
      for (unsigned short i = 0; i < var.length(); i++)
        std::cout << '\b';
    }
  }

  void Console::DeleteText(
    short xPos,
    short yPos,
    short textLength
    ) {
    SetCursorPosition(xPos, yPos);
    for (short i = 0; i < textLength; i++)
      std::cout << ' ';
  }
  
  std::string Console::FirstLetterToUppercase(
    std::string val
    ) {
    val[0] = toupper(val[0]);
    for (short i = 0; val[i] != '\0'; i++)
      if (isspace(val[i]))
        val[i + 1] = toupper(val[i + 1]);
    return val;
  }

  std::string Console::GenerateRandomKey(
    short numberOfLetter
    ) {
    std::string key;
    char keyList[36]{
      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
      'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
      'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0',
      '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };

    srand(static_cast<unsigned int>(time(NULL)));
    for (short i = 0; i < numberOfLetter; i++)
      key += keyList[rand() % 36];
    return key;
  }

  std::string Console::InputLine() {
    std::string str;

    getline(std::cin, str);
    return str;
  }

  std::string Console::InputPassword() {
    char ch;
    std::string password;

    while ((ch = _getch()) != '\r') {
      switch (ch) {
      case 0:
      case 224:
        _getch();
        break;
      case '\b':
        if (password.length() > 0) {
          password.erase(password.end() - 1);
          std::cout << "\b \b";
        }
        break;
      default:
        password += ch;
        std::cout << '*';
      }
    }
    return password;
  }

  int Console::IntParse(
    std::string str
    ) {
    try {
      return stoi(str);
    }
    catch (...) {
      std::cout << "Error";
    }
  }

  void Console::PrintTextColor(
    ConsoleColor bgColor,
    ConsoleColor fgColor,
    std::string text
    ) {
    short defColor = GetDefaultColor();

    SetTextColor(bgColor, fgColor);
    std::cout << text;
    SetTextColor(defColor);
  }

  void Console::SetBufferSize(
    short width,
    short height
    ) {
    COORD size{
      width,
      height
    };
    if (
      !SetConsoleScreenBufferSize(
        GetStdHandle(STD_OUTPUT_HANDLE),
        size
        )
      )
      throw std::runtime_error{ "Unable to resize screen buffer" };
  }

  void Console::SetConsoleFont(
    const wchar_t* fontFamily,
    short fontSize
    ) {
    CONSOLE_FONT_INFOEX cfInfo;

    cfInfo.cbSize = sizeof(cfInfo);
    cfInfo.nFont = 0;
    cfInfo.dwFontSize.X = 0;
    cfInfo.dwFontSize.Y = fontSize;
    cfInfo.FontFamily = FF_DONTCARE;
    cfInfo.FontWeight = FW_NORMAL;
    wcscpy_s(cfInfo.FaceName, fontFamily);
    if (
      !SetCurrentConsoleFontEx(
        GetStdHandle(STD_OUTPUT_HANDLE),
        false,
        &cfInfo
        )
      )
      throw std::runtime_error{ "Unable to change console font" };
  }

  void Console::SetMessage(
    short xPos,
    short yPos,
    ConsoleMessage messageType,
    std::string message
    ) {
    SetCursorPosition(xPos, yPos);
    if (messageType == ConsoleMessage::Information)
      PrintTextColor(ConsoleColor::Black, ConsoleColor::Cyan, "[INFORMATION] ");
    else if (messageType == ConsoleMessage::Warning)
      PrintTextColor(ConsoleColor::Black, ConsoleColor::Yellow, "[WARNING] ");
    else if (messageType == ConsoleMessage::Danger)
      PrintTextColor(ConsoleColor::Black, ConsoleColor::Red, "[DANGER] ");
    std::cout << message;
    std::cin.get();
    DeleteText(xPos, yPos, 14 + static_cast<short>(message.length()));
  }

  void Console::ShowConsoleCursor(
    bool showFlag
    ) {
    HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ccInfo;

    if (
      !GetConsoleCursorInfo(
        cHandle,
        &ccInfo
        )
      )
      throw std::runtime_error{ "Unable to get cursor info" };
    ccInfo.bVisible = showFlag;
    if (
      !SetConsoleCursorInfo(
        cHandle,
        &ccInfo
        )
      )
      throw std::runtime_error{ "Unable to set console cursor" };
  }

  std::string Console::XORCipher(
    const std::string str,
    const char key
    ) {
    std::string res;

    for (short i = 0; i < static_cast<int>(str.size()); i++)
      res += str[i] ^ key;
    return res;
  }

  /* Class Window */
  void Window::DisableCloseButton() {
    if (
      !EnableMenuItem(
        GetSystemMenu(
          GetConsoleWindow(),
          FALSE
          ),
        SC_CLOSE,
        MF_BYCOMMAND | MF_DISABLED | MF_GRAYED
        )
      )
      throw std::runtime_error{ "Unable to disable close button" };
  }
  
  void Window::DisableMaximizeButton() {
    SetWindowLong(
      GetConsoleWindow(),
      GWL_STYLE,
      GetWindowLong(
        GetConsoleWindow(),
        GWL_STYLE
        ) &
      ~WS_MAXIMIZEBOX
      );
  }

  void Window::DisableMinimizeButton() {
    SetWindowLong(
      GetConsoleWindow(),
      GWL_STYLE,
      GetWindowLong(
        GetConsoleWindow(),
        GWL_STYLE
        ) &
      ~WS_MINIMIZEBOX
      );
  }

  void Window::DisableResizeConsole() {
    SetWindowLong(
      GetConsoleWindow(),
      GWL_STYLE,
      GetWindowLong(
        GetConsoleWindow(),
        GWL_STYLE
        ) &
      ~WS_SIZEBOX
      );
  }

  void Window::SetConsoleFullScreen() {
    if (
      !SetConsoleDisplayMode(
        GetStdHandle(STD_OUTPUT_HANDLE),
        CONSOLE_FULLSCREEN_MODE,
        NULL
        )
      )
      throw std::runtime_error{ "Unable to change window" };
  }

  void Window::SetConsolePositionToCenter() {
    RECT rScreen;
    HWND hScreen = GetDesktopWindow();
    GetWindowRect(hScreen, &rScreen);
    RECT rWindow;
    HWND hWindow = GetForegroundWindow();
    GetWindowRect(hWindow, &rWindow);

    int width = rWindow.right - rWindow.left;
    int height = rWindow.bottom - rWindow.top;
    int xPos = ((rScreen.right - rScreen.left) / 2 - width / 2);
    int yPos = ((rScreen.bottom - rScreen.top) / 2 - height / 2);
    if (
      !SetWindowPos(
        hWindow,
        NULL,
        xPos,
        yPos,
        width,
        height,
        SWP_SHOWWINDOW || SWP_NOSIZE
        )
      )
      throw std::runtime_error{ "Unable to move console" };
  }

  void Window::SetConsoleSize(
    short width,
    short height
    ) {
    HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (cHandle == INVALID_HANDLE_VALUE)
      throw std::runtime_error{ "Unable to get stdout handle" };

    /* Getting console screen buffer info */ {
      COORD cCoord = GetLargestConsoleWindowSize(cHandle);
      if (width > cCoord.X)
        throw std::out_of_range{ "The width dimensions is too large" };
      if (height > cCoord.Y)
        throw std::out_of_range{ "The height dimensions is too large" };
    }

    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
    if (!GetConsoleScreenBufferInfo(cHandle, &csbInfo))
      throw std::runtime_error{ "Unable to retrieve screen buffer info" };

    SMALL_RECT& wInfo = csbInfo.srWindow;
    COORD wSize{
      wInfo.Right - wInfo.Left + 1,
      wInfo.Bottom - wInfo.Top + 1
    };

    if (wSize.X > width || wSize.Y > height) {
      SMALL_RECT info{
        0,
        0,
        width < wSize.X ? width - 1 : wSize.X - 1,
        height < wSize.Y ? height - 1 : wSize.Y - 1
      };

      if (!SetConsoleWindowInfo(cHandle, true, &info))
        throw std::runtime_error{ "Unable to resize window before resizing buffer" };
    }

    COORD size{
      width,
      height
    };
    if (!SetConsoleScreenBufferSize(cHandle, size))
      throw std::runtime_error{ "Unable to resize screen buffer" };

    SMALL_RECT info{
      0,
      0,
      width - 1,
      height - 1
    };
    if (!SetConsoleWindowInfo(cHandle, true, &info))
      throw std::runtime_error{ "Unable to resize window after resizing buffer" };
  }
}