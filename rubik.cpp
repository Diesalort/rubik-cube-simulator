#include "rubik.h"

std::ostream& operator<< (std::ostream& out, const tCara cara);
void rellenaCara(tCubo cubo, int nCara); //Inicializa una cara del cubo
void rotarCara(tCara cara, bool sentido);
void actualizarCarasAdyacentes0y4(tCubo cubo, int numCara, bool sentido);
void actualizarCarasAdyacentes1y3(tCubo cubo, int numCara, bool sentido);
void actualizarCarasAdyacentes2y5(tCubo cubo, int numCara, bool sentido);
bool caraSolucionada(tCara cara, int numCara); //Comprueba si una cara esta solucionada


void iniciarCubo(tCubo cubo) {

	for (int i = 0; i < NUM_CARAS; i++) {

		rellenaCara(cubo, i);
	}
}

void rellenaCara(tCubo cubo, int nCara) {

	for (int i = 0; i < DIM; i++) {

		for (int j = 0; j < DIM; j++) {

			cubo[nCara][i][j] = tCasilla(nCara);

		}
	}
}

std::ostream& operator << (std::ostream& out, const tCara cara) {

	int x, y;

	getxy(x, y);

	for (int i = 0; i < DIM; i++) {

		gotoxy(x, y);

		for (int j = 0; j < DIM; j++) {

			out << cara[i][j];

		}

		y++;
	}

	return out;
}

std::ostream& operator << (std::ostream& out, const tCubo cubo) {

	gotoxy(20, 1);
	out << "0 " << cubo[0];

	gotoxy(11, 5);
	out << "1 " << cubo[1];
	
	gotoxy(20, 5);
	out << "2 " << cubo[2];

	gotoxy(29, 5);

	out << "3 " << cubo[3];
	
	gotoxy(20, 9);
	out << "4 " << cubo[4];

	gotoxy(20, 13);
	out << "5 " << cubo[5];
	
	out << '\n';
	return out;
}

void actualizarCubo(tCubo cubo, int numCara, bool sentido) {

	if (numCara == 0 || numCara == 4) {

		actualizarCarasAdyacentes0y4(cubo, numCara, sentido);

	}
	else if (numCara == 1 || numCara == 3) {

		actualizarCarasAdyacentes1y3(cubo, numCara, sentido);

	}
	else { //numCara == 2 || numCara == 5

		actualizarCarasAdyacentes2y5(cubo, numCara, sentido);

	}

	//Para la representación correcta de las caras del cubo (debido a la perspectiva del cubo plegable)
	if (numCara == 1 || numCara == 5 || numCara == 4) sentido = !sentido;
	rotarCara(cubo[numCara], sentido); //Rota la cara según el sentido indicado
}

void rotarCara(tCara cara, bool sentido) {

	tCara aux;

	for (int i = 0; i < DIM; i++) {

		for (int j = 0; j < DIM; j++) {

			if (sentido) { //HORARIO

				aux[j][DIM - 1 - i] = cara[i][j];

			}
			else { //ANTIHORARIO

				aux[DIM-1-j][i] = cara[i][j];

			}	
		}
	}

	for (int i = 0; i < DIM; i++) { //Copiamos la matriz rotada en el cubo

		for (int j = 0; j < DIM; j++) {

			cara[i][j] = aux[i][j];
		}
	}
}

void actualizarCarasAdyacentes0y4(tCubo cubo, int numCara, bool sentido) {

	tCasilla temp[DIM];

	int fila = 0; //Si rotamos la 0, giramos la fila superior de cada cara (Excepto la 5)

	if (numCara == 4) fila = DIM-1; //Si rotamos la 4, giramos la fila inferior de cada cara (Excepto la 5)


	int F5 = DIM-1; //F5 sirve para colocar las casillas de la cara 5 donde corresponde en el cubo plegable
	if (numCara == 4) F5 = 0;

	int v1 = 3, v2 = 1; //Caras adyacentes

	if (!sentido) { //Se intercambian estas caras adyacentes si el giro es antihorario
		v1 = 1;
		v2 = 3;
	}

	for (int j = 0; j < DIM; j++) { //Lógica de giro

		temp[j] = cubo[2][fila][j];

		cubo[2][fila][j] = cubo[v1][fila][j];
		cubo[v1][fila][j] = cubo[5][F5][DIM-j-1];
		cubo[5][F5][DIM-j-1] = cubo[v2][fila][j];
		cubo[v2][fila][j] = temp[j]; 

		std::cout << cubo;
	}
}

void actualizarCarasAdyacentes1y3(tCubo cubo, int numCara, bool sentido) {

	tCasilla temp[DIM];

	int col = 0; //Si rotamos la cara 1, giramos la columna de la izquierda de cada cara

	if (numCara == 3) col = DIM-1; //Si rotamos la cara 3, giramos la columna de la derecha de cada cara

	int v1 = 2, v2 = 5; //Caras adyacentes

	if (!sentido) { //Se intercambian estas caras adyacentes si el giro es antihorario
		v1 = 5;
		v2 = 2;
	}


	for (int i = 0; i < DIM; i++) { //Lógica de giro

		temp[i] = cubo[0][i][col];

		cubo[0][i][col] = cubo[v1][i][col];
		cubo[v1][i][col] = cubo[4][i][col];
		cubo[4][i][col] = cubo[v2][i][col];
		cubo[v2][i][col] = temp[i];

		std::cout << cubo;
	}
}

void actualizarCarasAdyacentes2y5(tCubo cubo, int numCara, bool sentido) {

	//En la cara 1 y 3 cambia la columna, en la 0 y 4 la fila, de ahí que la lógica sea más compleja

	tCasilla temp[DIM];

	int col1 = DIM-1, col2 = 0; //Diferencian la columna que se actualiza en la cara 1 y 3, dependiendo de si se gira la cara 2 o la 5

	int v1 = 4, v2 = 0; //Caras adyacentes
	int t1 = 0, t2 = DIM-1; //Facilita que se coloquen las casillas en el lugar que le corresponda según el movimiento
	
	if (numCara == 5) {

		col1 = 0;
		col2 = DIM-1;
		t1 = DIM-1;
		t2 = 0;
	}

	if (!sentido) {
		//Se intercambian estas caras adyacentes si el giro es antihorario
		v1 = 0;
		v2 = 4;

		//Recibiran las casillas de la cara anterior, cuya fila es la opuesta a la cara de la que reciben en sentido horario
		int temp = t1;
		t1 = t2;
		t2 = temp;
	}


	/* Para que las casillas se coloquen en la posicion que les corresponde.
	   Ej.: Giramos la cara 2 en sentido horario, por lo que la cara 1 recibe de la cara 4
	   (La casilla superior de 1 debe contener la casilla de la izquierda de 4)
	   Si giramos la cara 2 en sentido antihorario, la cara 1 recibe de la 0
	   (La casilla superior de 1 debe ser la de la derecha de 0)
	*/

	int selec1;
	int selec2;

	for (int j = 0; j < DIM; j++) {

		if (sentido) selec1 = j, selec2 = DIM-j-1;
		else selec1 = DIM - j - 1, selec2 = j;

		temp[j] = cubo[1][j][col1];

		cubo[1][j][col1] = cubo[v1][t1][selec1];
		cubo[v1][t1][selec1] = cubo[3][DIM-j-1][col2];
		cubo[3][DIM-j-1][col2] = cubo[v2][t2][selec2];
		cubo[v2][t2][selec2] = temp[j];

		std::cout << cubo;
	}
}

bool cuboSolucionado(tCubo cubo) {

	bool solucionado = true;

	int i = 0; 

	while (i < NUM_CARAS && solucionado) {

		solucionado = caraSolucionada(cubo[i], i);

		i++;
	}
	
	return solucionado;
}

bool caraSolucionada(tCara cara, int numCara) {

	int i = 0;
	int j = 0;
	bool solucionado = true;

	while (i < DIM && solucionado) {

		j = 0;

		while (j < DIM && solucionado) {

			cara[i][j] != tCasilla(numCara) ? solucionado = false : j++;

		}

		i++;
	}

	return solucionado;
}