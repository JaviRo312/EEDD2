#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include "Tipos.h"
#define N1 8
#define N2 100
#define N3 12
#define N5 6
#define N4 N5*N3

using namespace std;

std::string localidades[] = {"Daganzo","Alcala", "Mejorada", "Nuevo Baztan", "Arganda", "Carabanna", "Chinchon", "Villarejo"};

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
int generarNumCP()
{
    return rand()%1000;
}
string AsignarLocalidades()//Revisar
{
    int size= 7;
    int aleatorio=rand()%size;
    return localidades[aleatorio];
}
string generarNIF()
{
    int numero;
    string NIF;
    char letras[] = {'T','R','w','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};

    for (int i=0; i<6; i++)
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
    minLat = 6 + rand()%28;
    segLat = rand()%60;
    gradLong = -3;
    minLong = 5 + rand()%29;
    segLong = rand()%60;

    c.latitud[0] = gradLat;
    c.latitud[1] = minLat;
    c.latitud[2] = segLat;
    c.longitud[0] = gradLong;
    c.longitud[1] = minLong;
    c.longitud[2] = segLong;

    return c;
}

Paquete generarPaquete(int numCp)
{
    Paquete p;

    p.idPaquete = generarIdPaquete();
    p.coordenadas = generarCoordenadas();
    p.NIF = generarNIF();
    p.numCP = numCp;

    return p;
}
CP generarCpPredeterminado()
{
    CP cp;
    cp.numCP=generarNumCP();
    cp.localidad=AsignarLocalidades();
//    cp.listaPaq=NULL; // No es un puntero

    return cp;
}

void cogerPaquetes(int contador)
{
    do
    {
        cout << '\n' << "Presiona Enter para coger más paquetes..." << '\n' << endl;
    }
    while (cin.get() != '\n');
    contador++;
}
void sigInstruccion() //Método para ir paso a paso con la ejecución del programa
{
    cout << '\n' << "Presiona Enter para realizar la siguiente instruccion..." << '\n' << endl;
    getchar();

}

Arbol *arbolCP=NULL;
Lista *CAE=NULL;

void inicializaSistema()
{
    // Inicializamos árbol de búsqueda y lista maestra de paquetes
    arbolCP = new Arbol();
    CAE = new Lista();
    int aux[N1];

    for (int i=0; i<N1; i++)//Crea las 8 centrales de paqueteria y las muestra por pantalla
    {
        CP cp=generarCpPredeterminado();
        aux[i]=cp.numCP;
        arbolCP->insertar(cp);
        cout<<setw(3)<<i+1<<" "<< setw(8) << cp.numCP << " " <<"   "<< setw(12) << cp.localidad << endl;//Ver como se hace con abb y no con array
    }

    cout << string(27, '=') << "LISTADO DE PAQUETES" << string(27,'=') << endl;
    cout << setw(4) << " No." << "|" << setw(7) << "ID Paq " << "|" << setw(9) << "   NIF   " << "|" << setw(21) << "     Coordenadas     " << "|" << endl;
    cout << string(22, ' ') << "|" << setw(10) << " Latitud  " << "|"<< setw(10) << " Longitud " << "|" << endl;
    cout << string(45, '-') << endl;
    //Crea los 100 paquetes y los muestra por pantalla
    for (int j=0; j<N2; j++)
    {
        // Seleccionamos aleatoriamente uno de los numCp generados en el paso anterior
        Paquete p = generarPaquete(aux[rand()%N1]);
        CAE->insertarNodo(p);
        cout << setw(4)<< j+1 << " " << setw(7) << p.idPaquete << " " << setw(9) << p.NIF << " " << setw(2) << p.coordenadas.latitud[0] << "*" << setw(2) << p.coordenadas.latitud[1] << "'" << setw(2) << p.coordenadas.latitud[2] << "''" << " " << setw(2) << p.coordenadas.longitud[0] << "*"<< setw(2) << p.coordenadas.longitud[1] << "'" << setw(2) << p.coordenadas.longitud[2] << "''" << endl;
    }
}

int main()
{
    srand(time(NULL));
    int opcion;
    bool repetir = true;
    Paquete p;
    CP centralPaq;
    string IDp, IDcp;
    int i=0, j=0, nPaquetes=0, nCP=0;
    int paquetesCogidos=0;
    int codCentral = 0;
    int gradLat=0, minLat=0, segLat=0, gradLong=0, minLong=0, segLong=0;
    int contadorPaquetes=N1;

    cout << string(33, '#') << "ALMACEN DE PAQUETES" << string(33, '#') << endl;
    cout << string(27, '=') << "LISTADO DE CENTRALES DE PAQUETERIA" << string(27, '=') << endl;
    cout << setw(4) << " No." << "|" << setw(7) << "ID CP " << "|" << setw(9) << "   Nombre localidad   " << endl;
    cout << string(45, '-') << endl;

    inicializaSistema();

    // Bucle de iteraciones/días
    int contador = 0;
    while(contador++<N5)
    {
        sigInstruccion();
        cout << "Paquetes enviados en el día " << contador << ":"<<endl;
        while(paquetesCogidos++ < N3)
        {
            pNodoLista nodo = CAE->borrarNodo();
            if (nodo!=NULL)
            {
                p = nodo->getPaquete();
                CP cpAux;
                cpAux.numCP = p.numCP;
                pNodoArbol nodo = arbolCP->buscar(cpAux);
                nodo->getCentrarlP().listaPaq.insertarNodo(p);
                delete(nodo);
                cout<< "Paquete: "<<p.idPaquete << " añadido a la lista de paquetes del CP de :" <<nodo->getCentrarlP().localidad << endl;//Ver como se hace con abb y no con array
            }
        }
    }

    do
    {
        system("cls");
        // Texto del menú que se verá cada vez
        cout << "\n\nMenu de Opciones" << endl;
        cout << "1. Insertar una CP de forma manual." << endl;
        cout << "2. Borrar una CP del árbol." << endl;
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

        switch (opcion)
        {
        case 1:
            // Insertar una CP de forma manual
            centralPaq.numCP = if (!arbolCP.buscar(cp.numCP)){generarNumCP();}; //Asigno el número de CP manual o aleatoriamente?
            for(auto const& value : localidades) //Para ver las localidades disponibles.
            {
                cout << value << ", ";
            }
            cout << endl;
            cout << "Localidad deseada: ";
            cin >> centralPaq.localidad;
            cout << endl;
            system("pause>nul"); // Pausa
            break;

        case 2:
            // Borrar una CP del árbol
            cout << "Codigo de la central que desea eliminar: "; //Busco la central por su código?
            cin >> codCentral;
            cout << endl;
            arbolCP.borrar(arbolCP.buscar(codCentral));
            system("pause>nul"); // Pausa
            break;

        case 3:
            // Mostrar los datos de los paquetes que se distribuirán en una CP dada
            cout << "Código de la central que desea ver: "
            cin >> codCentral;
            CAE.recorrerLista();
            if (codCentral == )
            {
                cout << setw(7) << p.idPaquete << " " << setw(9) << p.NIF << " " << setw(2) << p.coordenadas.latitud[0] << "*" << setw(2) << p.coordenadas.latitud[1] << "'" << setw(2) << p.coordenadas.latitud[2] << "''" << " " << setw(2) << p.coordenadas.longitud[0] << "*"<< setw(2) << p.coordenadas.longitud[1] << "'" << setw(2) << p.coordenadas.longitud[2] << "''" << endl;
            }
            system("pause>nul"); // Pausa
            break;

        case 4:
            // Mostrar una estadística de las CP de la empresa recorriendo Inorden los nodos del árbol
            arbolCP.inOrden();
            // Estadística? Se refiere a los paquetes que se han repartido desde cada CP o qué?
            system("pause>nul"); // Pausa
            break;

        case 5:
            // Buscar un paquete concreto por su ID
            cout << "ID del paquete a buscar: ";
            cin >> IDp;
            cout << endl;
            if (CAE.actual->getPaquete().idPaquete != IDp)
            {
                CAE.esSiguiente();
            }
            else if (CAE.final->getPaquete().idPaquete != IDp)
            {
                cout << "No se ha encontrado el paquete en el CAE. Se buscará en los CP." << endl;
            }
            else
            {
                cout << "El paquete con ID " << CAE.actual->getPaquete().idPaquete << " se encuentra en el CAE."<< endl;
            }
            arbolCP.preOrden();
            // Quiero recorrer el árbol y buscar en la lista de paquetes de cada CP si está este paquete.
            system("pause>nul"); // Pausa
            break;

        case 6:
            // Extraer algún paquete concreto de una CP dada (borrarlo del sistema)
            cout << "ID del paquete a buscar: ";
            cin >> IDcp;
            cout << endl;
            arbolCP.preOrden(buscar(actual),actual.ID);
            arbolCP.
            system("pause>nul"); // Pausa
            break;

        case 7:
            // Llevar un paquete concreto del CAE a una CP concreta
            system("pause>nul"); // Pausa
            break;

        case 8:
            // Llevar un paquete concreto de una CP a otra
            system("pause>nul"); // Pausa
            break;

        case 9:
            // Continuar con la distribución de paquetes
            sigInstruccion();
            system("pause>nul"); // Pausa
            break;

        case 0:
            // Salir del programa
            repetir = false;
            break;
        }
    }
    while (repetir);

    return 0;
}
