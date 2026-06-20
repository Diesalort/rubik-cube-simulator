#ifndef __UTILS_H__
#define __UTIL_H__
#include <fstream> // para ficheros, ios....

// Indica si el str corresponde con una consola.
bool esConsola(std::ios& str);
// Configurar la consola para español.
void configuraCastellanoConsola();
// Colocar el cursor de la consola en una posicion dada
void gotoxy(int x, int y);
// Conseguir las coordenadas del cursor.
void getxy(int& x, int& y);
#endif // !__UTILS_H__
