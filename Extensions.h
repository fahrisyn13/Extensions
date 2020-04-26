/* Fahri Synyster
Module name:
  Extensions.h

Summary:
  Berisikan fungsi-fungsi pembantu.

Reference:
  https://docs.microsoft.com/en-us/
  https://en.cppreference.com/w/
  https://stackoverflow.com/
  https://www.cplusplus.com/
  https://www.geeksforgeeks.org/
  https://www.youtube.com/user/TheChernoProject

Last changelog:
  17 Apr 2020
    - Penambahan fungsi Print()
  14 Apr 2020
    - Perbaikan kode
  10 Apr 2020
    - Perbaikan kode
  9 Apr 2020
    - Penambahan fungsi SetBufferSize()
  8 Apr 2020
    - Perbaikan kode
    - Penghapusan fungsi RemoveConsoleScrollBar()
  7 Apr 2020
    - Penambahan enumerator ConsoleAnswer
  6 Apr 2020
    - Perbaikan kode
    - Penambahan fungsi GetDefaultColor()
  5 Apr 2020
    - Module dibuat

Written in Visual Studio 2019
*/

#ifndef EXTENSIONS_H
#define EXTENSIONS_H
#include <iostream>
#include <string>
namespace Extensions {
  /* Console Color */
	enum class ConsoleColor {
    Black = 0,
    DarkBlue = 1,
    DarkGreen = 2,
    DarkCyan = 3,
    DarkRed = 4,
    DarkMagenta = 5,
    DarkYellow = 6,
    Gray = 7,
    DarkGray = 8,
    Blue = 9,
    Green = 10,
    Cyan = 11,
    Red = 12,
    Magenta = 13,
    Yellow = 14,
    White = 15
	};

  /* Console Message */
  enum class ConsoleMessage {
    Information = 1,
    Warning = 2,
    Danger = 3
  };

  /* Pengoperasian didalam console */
  class Console {
  public:
    /* Mengambil default console color */
    static short GetDefaultColor();

    /*
      Menempatkan console cursor
      \param xPos adalah posisi x
      \param yPos adalah posisi y
    */
    static void SetCursorPosition(
      short xPos,
      short yPos
      );

    /*
      Mengubah warna teks pada Console
      \param bgColor adalah warna background
      \param fgColor adalah warna foreground
    */
    static void SetTextColor(
      ConsoleColor bgColor,
      ConsoleColor fgColor
      );

    /*
      Mengubah warna teks pada Console
      \param color adalah warna
    */
    static void SetTextColor(
      short color
      );

    /* Membersihkan console */
    static void Clear();

    /*
      Mengosongkan field input string
      \param var adalah string yang dikosongkan
    */
    static void ClearField(
      const std::string& var
      );

    /*
      Menghapus teks
      \param xPos adalah posisi x
      \param yPos adalah posisi y
      \param textLength adalah panjang teks
    */
    static void DeleteText(
      short xPos,
      short yPos,
      short textLength
      );

    /*
      Membuat huruf pertama menjadi kapital
      \param val adalah kata
    */
    static std::string FirstLetterToUppercase(
      std::string val
      );

    /*
      Membuat huruf acak
      \param numberOfLetter adalah jumlah huruf
    */
    static std::string GenerateRandomKey(
      short numberOfLetter
      );

    /* Membaca input string */
    static std::string InputLine();

    /* Membaca input password */
    static std::string InputPassword();

    /*
      Mengkonversi string menjadi integer
      \param str adalah string yang di konversi
    */
    static int IntParse(
      std::string str
      );

    /*
      Menampilkan teks
      \param val adalah teks
    */
    template<typename Type>
    static void Print(Type val) {
      std::cout << val;
    }

    /*
      Menampilkan teks dengan warna
      \param bgColor adalah warna background
      \param fgColor adalah warna foreground
      \param text adalah teks
    */
    static void PrintTextColor(
      ConsoleColor bgColor,
      ConsoleColor fgColor,
      std::string text
      );

    /* Mengubah buffer size */
    static void SetBufferSize(
      short width,
      short height
      );

    /*
      Mengubah font pada console
      \param fontFamily adalah nama font
      \param fontSize adalah ukuran font
    */
    static void SetConsoleFont(
      const wchar_t* fontFamily,
      short fontSize
      );

    /*
      Menampilkan pesan
      \param xPos adalah posisi x
      \param yPos adalah posisi y
      \param messageType adalah tipe pesan
      \param message adalah pesan
    */
    static void SetMessage(
      short xPos,
      short yPos,
      ConsoleMessage messageType,
      std::string message
      );

    /*
      Menampilkan atau menyembunyikan console cursor
      \param showFlag adalah value
    */
    static void ShowConsoleCursor(
      bool showFlag
      );

    /*
      Mengenkripsi atau mendekripsi string menggunaan XOR Cipher
      \param str adalah string
      \param key adalah kunci
    */
    static std::string XORCipher(
      const std::string str,
      const char key
      );
  };

  /* Pengoperasian diluar console */
  class Window {
  public:
    /* Menonaktifkan tombol close */
    static void DisableCloseButton();

    /* Menonatifkan tombol maximize */
    static void DisableMaximizeButton();

    /* Menonaktifkan tombol minimize */
    static void DisableMinimizeButton();

    /* Menonaktifkan resize console */
    static void DisableResizeConsole();

    /* Membuat console menjadi fullscreen */
    static void SetConsoleFullScreen();

    /* Menempatkan console ke tengah layar */
    static void SetConsolePositionToCenter();

    /*
      Mengubah ukuran console
      \param width adalah lebar console
      \param height adalah tinggi console
    */
    static void SetConsoleSize(
      short width,
      short height
      );
  };
}
#endif // !EXTENSIONS_H