#include "casilla.h"

#include <iomanip> // setw, setfill
#include "utils.h"
#include "colors.h"

std::istream& operator>> (std::istream& in, tCasilla& casilla) {
    char c;
    in >> c;
    switch (c) {
    case 'R': casilla = _RED;
        break;
    case 'B': casilla = _BLUE;
        break;
    case 'O': casilla = _ORANGE;
        break;
    case 'G': casilla = _GREEN;
        break;
    case 'Y': casilla = _YELLOW;
        break;
    case 'W': casilla = _WHITE;
        break;
    default: casilla = _WHITE;
    }

    return in;
}

void mostrarConsola(std::ostream& out, tCasilla celda) {
    // Cambiar el color de la consola
    switch (celda)
    {
    case _BLUE: out << BG_BLUE << BLUE;
        break;
    case _GREEN: out << BG_GREEN << GREEN;
        break;
    case _RED: out << BG_RED << RED;
        break;
    case _ORANGE: out << BG_ORANGE << ORANGE;
        break;
    case _YELLOW: out << BG_YELLOW << YELLOW;
        break;
    case _WHITE: out << BG_WHITE << WHITE;
        break;
    default: out << BG_BLUE << BLUE;
        break;
    }
    // Escribir la casilla
    out << std::setw(HUECO) << std::setfill(' ') << ' ';
    // Dejar la consola en valor por defecto
    out << RESET;
}

std::ostream& operator<< (std::ostream& out, tCasilla const& casilla) {
    if (esConsola(out)) mostrarConsola(out, casilla);
    else {
        char c = ' ';
        switch (casilla)
        {
        case _BLUE: c = 'B';
            break;
        case _GREEN: c = 'G';
            break;
        case _RED: c = 'R';
            break;
        case _ORANGE: c = 'O';
            break;
        case _YELLOW: c = 'Y';
            break;
        case _WHITE: c = 'W';
            break;
        default: c = 'W';
            break;
        }
        out << c;
    }
    return out;
}
