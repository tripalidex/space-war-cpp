#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "Nodo2.h"
#include "ListaEnemigosCreada.h"
using namespace std;

// Código ASCII
#define IZQUIERDA 75
#define DERECHA 77

void aniadir();
void gotoxy(int x, int y);
void vidas(int vi);
void barra_salud(int n);
void avion_explota();
void menu();
void jugar();

char avion_l1[] = {' ', ' ', ' ', '*', ' ', ' ', ' ', 0};
char avion_l2[] = {' ', ' ', '*', '*', '*', ' ', ' ', 0};
char avion_l3[] = {' ', '*', ' ', '*', ' ', '*', ' ', 0};

char explocion_l1[] = {' ', ' ', '*', '*', ' ', ' ', ' ', 0};
char explocion_l2[] = {' ', '*', '*', '*', '*', ' ', ' ', 0};
char explocion_l3[] = {' ', ' ', '*', '*', ' ', ' ', ' ', 0};

char explocion_r1[] = {'*', ' ', '*', '*', ' ', '*', ' ', 0};
char explocion_r2[] = {' ', '*', '*', '*', '*', ' ', ' ', 0};
char explocion_r3[] = {'*', ' ', '*', '*', ' ', '*', ' ', 0};

// Esta línea sirve para borrar el avión, primero se borra y luego se imprime el avión en la posición deseada
char borrar_avion[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', 0};

int num_vidas = 3;
int corazones = 3;

// Coordenadas globales del avión
int ix = 40; // Coordenada X del avión
int iy = 19; // Coordenada Y del avión

// Lista de asteroides
ListaEnemigosCreada listaAsteroides;

// Puntero a la cabeza de la lista
Nodo2 *cabeza = NULL;

void agregar_avion()
{
    Nodo2 *nuevo_avion = new Nodo2(1); // Supongamos que el valor 1 representa al avión
    nuevo_avion->set_sig(cabeza);
    if (cabeza != NULL)
    {
        cabeza->set_ant(nuevo_avion);
    }
    cabeza = nuevo_avion;
}

void mover_avion(int direccion)
{
    // Borra el avión en la posición actual
    gotoxy(ix, iy);
    puts(borrar_avion);

    // Mueve el avión según la dirección
    switch (direccion)
    {
    case IZQUIERDA:
        ix--;
        break;
    case DERECHA:
        ix++;
        break;
    // Otros casos según las teclas que desees manejar
    }

    // Imprime el avión en la nueva posición
    gotoxy(ix, iy);
    puts(avion_l1);
    gotoxy(ix, iy + 1);
    puts(avion_l2);
    gotoxy(ix, iy + 2);
    puts(avion_l3);
}

void eliminar_aviones()
{
    // Libera la memoria ocupada por los nodos de la lista
    Nodo2 *actual = cabeza;
    while (actual != NULL)
    {
        Nodo2 *siguiente = actual->get_sig();
        delete actual;
        actual = siguiente;
    }
    cabeza = NULL;
}

// Librería windows.h
void gotoxy(int x, int y)
{
    HANDLE hcon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hcon, dwPos);
}

void vidas(int vi)
{
    gotoxy(2, 1);
    printf("VIDAS: %d", vi); // Mostrar el número de vidas
}

// Imprime la cantidad de corazones que le diga
void barra_salud(int n)
{
    gotoxy(72, 1);
    printf(" ");
    gotoxy(73, 1);
    printf(" ");
    gotoxy(74, 1);
    printf(" ");

    for (int v = 0; v < n; v++)
    {
        gotoxy(72 + v, 1);
        printf("%c", 3); // En el código ASCII es un corazón
    }
}

void avion_explota()
{
    gotoxy(ix, iy);
    puts(explocion_l1);
    gotoxy(ix, iy + 1);
    puts(explocion_l2);
    gotoxy(ix, iy + 2);
    puts(explocion_l3);

    Sleep(380); // El tiempo para que se vea la explosión, sino el programa va muy rápido y no se ve

    gotoxy(ix, iy);
    puts(explocion_r1);
    gotoxy(ix, iy + 1);
    puts(explocion_r2);
    gotoxy(ix, iy + 2);
    puts(explocion_r3);

    Sleep(380);

    gotoxy(ix, iy);
    puts(avion_l1);
    gotoxy(ix, iy + 1);
    puts(avion_l2);
    gotoxy(ix, iy + 2);
    puts(avion_l3);
}

void generaAsteroides()
{
    const double probabilidad = 0.2;

    for (int xCoord = 6; xCoord < 76; xCoord += 6)
    {
        if ((rand() / static_cast<double>(RAND_MAX)) < probabilidad)
        {
            int yCoord = rand() % 5; // Generar coordenada Y aleatoria dentro de las primeras 5 filas
            int direccion = 1;
            listaAsteroides.agregarNodo(xCoord, yCoord, direccion);
        }
    }
}

void dibujaAsteroides()
{
    NodoEnemigos *actual = listaAsteroides.cabeza;
    while (actual != NULL)
    {
        // Borra el asteroide actual
        gotoxy(actual->x, actual->y);
        printf(" ");

        // Mueve el puntero al siguiente asteroide antes de imprimir el nuevo
        actual = actual->siguiente;
    }

    // Después de borrar todos los asteroides, imprime los nuevos
    actual = listaAsteroides.cabeza;
    while (actual != NULL)
    {
        gotoxy(actual->x, actual->y);
        printf("%c", 2); // Dibuja el asteroide
        actual = actual->siguiente;
    }
}

void eliminaAsteroides()
{
    NodoEnemigos *actual = listaAsteroides.cabeza;
    while (actual != NULL)
    {
        NodoEnemigos *siguiente = actual->siguiente;

        // Elimina el asteroide si ha llegado al borde inferior de la pantalla
        if (actual->y >= 20)
        {
            listaAsteroides.eliminarNodo(actual);
        }

        actual = siguiente;
    }
}

void moverAsteroides()
{
    NodoEnemigos *actual = listaAsteroides.cabeza;
    while (actual != NULL)
    {
        // Mueve el asteroide hacia abajo
        actual->y += 1;

        actual = actual->siguiente;
    }
}

// Función principal del juego
void jugar()
{
    system("cls"); // Limpiar la pantalla

    // Rutina de los asteroides
    if (listaAsteroides.cabeza == NULL || listaAsteroides.cabeza->y > 5)
    {
        generaAsteroides(); // Genera un nuevo asteroide solo si la lista está vacía o el último asteroide ha pasado la parte inferior de la pantalla
    }

    eliminaAsteroides(); // Borra los asteroides que han llegado al borde inferior
    dibujaAsteroides();  // Dibuja todos los asteroides
    vidas(num_vidas);    // Muestra el número de vidas
    barra_salud(corazones);

    Sleep(70);

    // Mueve el avión
    if (kbhit())
    {
        char tecla = getch();
        switch (tecla)
        {
        case IZQUIERDA:
            mover_avion(IZQUIERDA);
            break;
        case DERECHA:
            mover_avion(DERECHA);
            break;
        }
    }

    // Rutina para golpes de asteroides
    // Coordenadas que abarca el avión en X
    NodoEnemigos *actual = listaAsteroides.cabeza;
    while (actual != NULL)
    {
        if (actual->x > ix && actual->x < ix + 6 && actual->y >= iy - 1 && actual->y <= iy + 2)
        {
            corazones--;
            barra_salud(corazones);
            printf("\a"); // Hace el ruidito cuando le pega
            actual->x = -1; // Mueve el asteroide fuera de la pantalla
        }
        actual = actual->siguiente;
    }

    // Imprime el avión
    gotoxy(ix, iy);
    puts(avion_l1);
    gotoxy(ix, iy + 1);
    puts(avion_l2);
    gotoxy(ix, iy + 2);
    puts(avion_l3);

    if (corazones == 0)
    {
        num_vidas--;
        avion_explota();
        corazones = 3;
        barra_salud(corazones);
    }

    // Incremento de los asteroides
    moverAsteroides();
}

void aniadir()
{
    cout << "               ___________         ";
    cout << "\n    _|   _    _   _  _ _ _   |__ ";
    cout << "\n    |       |  ||  (   |     |   |   |    |      | ";
    cout << "\n    |       | |   |  ) |  | | |   |      |  ";
    cout << "\n    |       |___________|      |  ";
    cout << "\n    |___)                        (___| ";

    cout << "\n     ^                                      _^_";
    cout << "\n    ( _ )------------------------------------( _ )";
    cout << "\n     | | |                                      | | |";
    cout << "\n     | | |          |  WELCOME TO GAME  |       | | |";
    cout << "\n     |_|                                      |_|";
    cout << "\n    (__)------------------------------------(__) ";

    ofstream archivo;

    archivo.open("Puntuacion.txt", ios::app);

    if (archivo.fail())
    {
        cout << "No se pudo crear el archivo de texto";
        exit(1);
    }

    char nombre[20];
    archivo << "\n";

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 5);
    cout << "\n\n  [I][n][g][r][e][s][e] ";

    SetConsoleTextAttribute(hConsole, 15);
    cout << "[s][u] ";

    SetConsoleTextAttribute(hConsole, 5);
    cout << " [N][o][m][b][r][e]: ";
    cin >> nombre;

    archivo << nombre;

    archivo.close();
}
void menu()
{
    int opcion;

    do
    {
        system("cls"); // Limpiar pantalla
        cout << "------------- MENU -------------" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Instrucciones" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:{
			
            system("cls");
            aniadir(); // Pide el nombre al usuario y lo guarda en el archivo
            system("cls");
            vidas(num_vidas);
            barra_salud(corazones);

            while (num_vidas > 0)
            {
                jugar();
            }

            system("cls");
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 7);
            cout << "\n\n[¯G¯][¯R¯][¯A¯][¯C¯][¯I¯][¯A¯][¯S¯]  ";

            SetConsoleTextAttribute(hConsole, 13);
            cout << "[¯P¯][¯O¯][¯R¯] ";

            SetConsoleTextAttribute(hConsole, 11);
            cout << " [¯J¯][¯U¯][¯G¯][¯A¯][¯R¯]\n\n\n\n\n";

            system("pause");
            getch();
            break;}
		case 2:{
				
			
            	system("cls");
            	cout<<"\t\t\t ----------------INSTRUCCIONES----------------- ";
            	cout<<"\n Controles de movimiento:\n";
            	cout<<"\t	[A] Desplazamiento hacia la izquierda\n";
            	cout<<"\t	[D] Desplazamineto hacia la derecha";
            	cout<<"\n Vidas:";
            	cout<<"\t 	Se cuenta con 3 vidas y 3 corazones lo que es distinto,"<<endl;
            	cout<<"\t	los corazones son la cantidad de impactos con esteroides que puedes aguantar,"<<endl;
            	cout<<"\t 	antes de perder 1 vida, por cada vida hay 3 corazones, se pierde un corazon"<<endl;
            	cout<<"\t	cuando la punta de la nave golpea el asteroide."<<endl;
            	cout<<"\t Disfrute del juego!!!!\n\n";
            	system("pause");break;}
        case 3: {
				
				system("cls");
				cout<<"Gracias por hacer uso de nuestro juego";break;
			}
        default:{
				
            cout << "Opcion invalida. Intente de nuevo." << endl;break;}
        }

    } while (opcion != 3);
}

int main()
{
	srand(static_cast<unsigned>(time(NULL))); // Initialize random seed
	
    menu();
    eliminar_aviones(); // Limpia la memoria al finalizar el juego
    return 0;
}
