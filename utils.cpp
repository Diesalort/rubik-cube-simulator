#include "utils.h"

#include <iostream>
#include <io.h> // _isatty, _fileno
#include <windows.h>

using std::ios;

// Indica si el str corresponde con una consola.
bool esConsola(ios& str) {
    return (_isatty(_fileno(stdin)) && &str == & std::cin)
        || (_isatty(_fileno(stdout)) && &str == & std::cout)
        || (_isatty(_fileno(stderr)) && &str == & std::cerr);
}

// Configurar la consola para español.
void configuraCastellanoConsola() {
    setlocale(LC_ALL, "spanish");  // Escribe bien y lo coloca a entorno español.

    SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252); // Cambiar STDOUT - Para máquinas Windows

    system("cls"); // LLamada al sistema para dejar limpia la pantalla
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void getxy(int& x, int& y) {
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        x = cbsi.dwCursorPosition.X;
        y = cbsi.dwCursorPosition.Y;
    }
}