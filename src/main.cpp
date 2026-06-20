#include <iostream>
#include "utils.h"
#include "rubik.h"
#include <ctime>

void menu(); //Muestra por consola el funcionamiento del programa
void leerDatos(int& numCara, int& sentido); //Lee por consola los datos introducidos
void randomizarCubo(tCubo cubo, int numMovimientos); //Realiza movimientos aleatorios en el cubo

int main()
{
    //Semilla para generar numeros aleatorios
    srand(time(NULL));

    configuraCastellanoConsola();

    tCubo cubo;
    bool sentido;
    int giro;
    int numCara;
    int movimientosRandom;

    iniciarCubo(cubo);

    do {
        sentido = 0;

        std::cout << cubo;
        menu();
        leerDatos(numCara, giro);

        sentido = giro;

        if (numCara == -2) {

            std::cout << "Introduce el número de movimientos random que quieres: ";
            std::cin >> movimientosRandom;

            randomizarCubo(cubo, movimientosRandom);
        }
        else if (numCara == -3){

            iniciarCubo(cubo);
            std::cout << cubo;
            std::cout << '\n' << "Cubo reiniciado" << '\n';
            system("pause");

        }
        else if (numCara != -1) {

            actualizarCubo(cubo, numCara, sentido);

            if (cuboSolucionado(cubo)) {

                int x, y;
                getxy(x, y);
                gotoxy(x, y+1);
                std::cout << "¡ENHORABUENA! HAS SOLUCIONADO EL CUBO :)" << '\n';
                system("pause");
            }
        }
        
        system("cls"); //Limpia la pantalla por cada iteración

    } while (numCara != -1);

    if (!cuboSolucionado(cubo)) {
        
        std::cout << "NO HAS SOLUCIONADO EL CUBO :(" << '\n';
    }

    std::cout << "ADIOS! ;)";

    return 0;
}


void menu() {

    gotoxy(60, 1);
    std::cout << "INSTRUCCIONES";
    gotoxy(60, 3);
    std::cout << "+ Abandonar partida: -1";
    gotoxy(60, 4);
    std::cout << "+ Cubo aleatorio: -2";
    gotoxy(60, 5);
    std::cout << "+ Reiniciar cubo: -3";

    gotoxy(60, 7);
    std::cout << "+ Introduce la cara a rotar [0,5] y el sentido a girar (1/0)";
    gotoxy(60, 8);

    gotoxy(60, 10);
    std::cout << "+ Sentidos: (Todos con respecto a la cara 2)";
    gotoxy(60, 11);
    std::cout << "   - Horario/Arriba/Izquierda: 1";
    gotoxy(60, 12);
    std::cout << "   - Antihorario/Abajo/Derecha: 0";
    gotoxy(60, 14);
    std::cout << "+ Introduce los datos separados por un espacio";

    gotoxy(0, 18);
    std::cout << "Movimiento: ";
}

void leerDatos(int& numCara, int& sentido) {

    std::cin >> numCara;

    if (numCara != -1 && numCara != -2 && numCara != -3) {

        std::cin >> sentido;

        bool seguir = true;

        while (((numCara < 0 || numCara > 5) || (sentido != 1 && sentido != 0)) && seguir) {

            std::cout << '\n' << "Entrada no válida. Introduce valores permitidos: ";
            std::cin >> numCara;

            if (numCara == -1 || numCara == -2 || numCara == -3) seguir = false;
            else std::cin >> sentido;
        }
    }
}

void randomizarCubo(tCubo cubo, int numMovimientos) {

    int caraRandom;
    int giroRandom;

    for (int i = 0; i < numMovimientos; i++) {

        caraRandom = rand() % 6; //n.º aleatorio entre 0 y 5
        giroRandom = rand() % 2; //n.º aleatorio entre 0 y 1

        actualizarCubo(cubo, caraRandom, giroRandom);
    }
}