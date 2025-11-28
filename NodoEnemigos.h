#pragma once
#include <cstdlib>
#include <iostream>

class NodoEnemigos {
public:
    int x;
    int y;
    NodoEnemigos* siguiente;
    NodoEnemigos* anterior;
    int direccion; // Agregamos la propiedad "direccion" a la clase Nodo

    NodoEnemigos(int _x, int _y, int _direccion) : x(_x), y(_y), siguiente(NULL), anterior(NULL), direccion(_direccion) {
	}
};

