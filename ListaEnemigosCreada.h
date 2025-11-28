#include "NodoEnemigos.h"

class ListaEnemigosCreada {
public:
    NodoEnemigos* cabeza;

    ListaEnemigosCreada() : cabeza(NULL) {}

    void agregarNodo(int x, int y, int direccion) {
        NodoEnemigos* nuevoNodo = new NodoEnemigos(x, y, direccion);
        if (!cabeza) {
            cabeza = nuevoNodo;
        }
        else {
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
            cabeza = nuevoNodo;
        }
    }

    void eliminarNodo(NodoEnemigos *nodo)
{
    if (nodo == cabeza)
    {
        cabeza = nodo->siguiente;
    }
    else
    {
        nodo->anterior->siguiente = nodo->siguiente;
        if (nodo->siguiente != NULL)
        {
            nodo->siguiente->anterior = nodo->anterior;
        }
    }

    delete nodo;
}
	
	
	
    ~ListaEnemigosCreada() {
        NodoEnemigos* actual = cabeza;
        while (actual) {
            NodoEnemigos* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
};

