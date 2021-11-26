#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Tipos.h"

using namespace std;

string padTo(std::string &str, const size_t num, const char paddingChar = '0')
{
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
    return str;
}

string generarIdPaquete()
{
    string id;
    char abecedario[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    std::string parte1 = to_string(rand()%99);
    std::string parte2 = to_string(rand()%9999);
    id= padTo(parte1,2)+  abecedario[rand()%26] + padTo(parte2,4);
//    id = padTo(to_string(rand()%99),2) +  abecedario[rand()%26] + padTo(to_string(rand()%9999),4);

    return id;
}

string generarNIF()
{
    int numero;
    string NIF;
    char letras[] = {'T','R','w','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};

    for (int i=0;i<6;i++)
    {
        numero = numero*10 + rand()%10;
    }

    NIF = to_string(numero) + letras[numero%23];

    return NIF;
}

CoordenadasGPS generarCoordenadas()
{
    CoordenadasGPS c;
    int gradLat, minLat, segLat, gradLong, minLong, segLong;

    gradLat = 40;
    minLat = 29 + rand()%3;
    segLat = rand()%60;
    gradLong = -3;
    minLong = 19 + rand()%7;
    segLong = rand()%60;

    c.latitud[0] = gradLat;
    c.latitud[1] = minLat;
    c.latitud[2] = segLat;
    c.longitud[0] = gradLong;
    c.longitud[1] = minLong;
    c.longitud[2] = segLong;

    return c;
}

Paquete generarPaquete()
{
    Paquete p;

    p.idPaquete = generarIdPaquete();
    p.coordenadas = generarCoordenadas();
    p.NIF = generarNIF();

    return p;
}

void cogerPaquetes(int contador)
{
    do{
        cout << '\n' << "Presiona Enter para coger más paquetes..." << '\n' << endl;
    }
    while (cin.get() != '\n');
    contador++;
}


int main()
{
    srand(time(NULL));

    int opcion;
    bool repetir = true;

    do {
        system("cls");
        // Texto del menú que se verá cada vez
        cout << "\n\nMenu de Opciones" << endl;
        cout << "1. Insertar una CP de forma manual." << endl;
        cout << "2. Borrar una CP del árbol" << endl;
        cout << "3. Mostrar los datos de los paquetes que se distribuirán en una CP dada." << endl;
        cout << "4. Mostrar una estadística de las CP de la empresa recorriendo Inorden los nodos del árbol." << endl;
        cout << "5. Buscar un paquete concreto por su ID." << endl;
        cout << "6. Extraer algún paquete concreto de una CP dada (borrarlo del sistema)." << endl;
        cout << "7. Llevar un paquete concreto del CAE a una CP concreta." << endl;
        cout << "8. Llevar un paquete concreto de una CP a otra." << endl;
        cout << "9. Continuar con la distribución de paquetes." << endl;

        cout << "0. Salir del programa" << endl;

        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Lista de instrucciones de la opción 1
                system("pause>nul"); // Pausa
                break;

            case 2:
                // Lista de instrucciones de la opción 2
                system("pause>nul"); // Pausa
                break;

            case 3:
                // Lista de instrucciones de la opción 3
                system("pause>nul"); // Pausa
                break;

            case 4:
                // Lista de instrucciones de la opción 4
                system("pause>nul"); // Pausa
                break;

            case 5:
                // Lista de instrucciones de la opción 5
                system("pause>nul"); // Pausa
                break;

            case 6:
                // Lista de instrucciones de la opción 6
                system("pause>nul"); // Pausa
                break;

            case 7:
                // Lista de instrucciones de la opción 7
                system("pause>nul"); // Pausa
                break;

            case 8:
                // Lista de instrucciones de la opción 8
                system("pause>nul"); // Pausa
                break;

            case 9:
                // Lista de instrucciones de la opción 9
                system("pause>nul"); // Pausa
                break;

            case 0:
            	repetir = false;
            	break;
        }
    } while (repetir);

    return 0;
}
