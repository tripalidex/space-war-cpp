#include <cstdlib>
#include <iostream>
class Nodo2 {
private:
    int valor;
    int x;
    int y;
    int direccion;
    Nodo2* Sig;
    Nodo2* Ant;

public:
    Nodo2(int val, int _x, int _y, int dir);
    ~Nodo2();
    Nodo2() {}  // constructor
    Nodo2(int x);  // constructor
    Nodo2(int x, Nodo2* s);  // constructor
    int get_valor();  // obtener el valor del Nodo
    void set_valor(int e);  // asignar el valor al Nodo
    Nodo2* get_sig();  // obtener a donde apunta
    void set_sig(Nodo2* p);  // asignar a donde apuntar
    Nodo2* get_ant();  // obtener a donde apunta
    void set_ant(Nodo2* p);  // asignar a donde apuntar
};
Nodo2::Nodo2(int val, int _x, int _y, int dir) {
    valor = val;
    x = _x;
    y = _y;
    direccion = dir;
    Sig = NULL;
    Ant = NULL;
}

Nodo2::~Nodo2() {
    // Puedes agregar alguna lógica de limpieza adicional si es necesario
}

Nodo2::Nodo2(int x) {
    valor = x;
    Sig = NULL;
    Ant = NULL;
}

Nodo2::Nodo2(int x, Nodo2* s) {
    valor = x;
    Sig = s;
}

int Nodo2::get_valor() {
    return valor;
}

void Nodo2::set_valor(int x) {
    valor = x;
}

Nodo2* Nodo2::get_sig() {
    return Sig;
}

void Nodo2::set_sig(Nodo2* p) {
    Sig = p;
}

Nodo2* Nodo2::get_ant() {
    return Ant;
}

void Nodo2::set_ant(Nodo2* p) {
    Ant = p;
}

