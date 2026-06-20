#ifndef __CASILLA_H__
#define __CASILLA_H__
#include <iostream>

const int HUECO = 2; // Número de huecos de cada celda. Valor óptimo para consola = 2.

typedef enum tCasilla { _BLUE, _GREEN, _RED, _ORANGE, _YELLOW, _WHITE };

std::istream& operator>> (std::istream& in, tCasilla& casilla);
std::ostream& operator<< (std::ostream& out, tCasilla const& casilla);

#endif
