#include <iostream>
#include "Casilla.h"
#include "utils.h"

const int DIM = 3;
const int NUM_CARAS = 6;

typedef tCasilla tCara[DIM][DIM]; //Matriz que representa cada cara del cubo

typedef tCara tCubo[6]; //Array con las caras del cubo

void iniciarCubo(tCubo cubo); // Inicializa el cubo

std::ostream& operator<< (std::ostream& out, const tCubo cubo);

// Actualiza el cubo rotando una de sus caras en el sentido oportuno y realizando el giro
void actualizarCubo(tCubo cubo, int numCara, bool sentido); 

//Detecta si el cubo ha sido seleccionado
bool cuboSolucionado(tCubo cubo);