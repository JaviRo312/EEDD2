#ifndef PilasColas
#define PilasColas

#include <iostream>

using namespace std;

//Definición de tipos de datos:
struct CoordenadasGPS
{
    int latitud[3];
    int longitud[3];
};

struct Paquete
{
    string idPaquete;
    CoordenadasGPS coordenadas;
    string NIF;
    int numCP;
};

struct CP
{
    int numCP;
    string localidad;
    Lista listaPaq;
};

//Lista
class NodoLista
{
private:
    int valor;
    NodoLista *siguiente;
    friend class Lista;
public:
    NodoLista(int v, Nodo *sig = NULL)
    {
        valor = v;
        siguiente = sig;
    }
};
typedef NodoLista *pnodolista;

class Lista
{
private:
    pnodolista cabeza, actual, final;
public:
    Lista()
    {
        cabeza = actual = final = NULL;
    }
    ~Lista();
    void insertarNodo(int v);
    void insertarNodoIntermedio(int v, int posicion);
    void borrarNodo(int v);
    bool listaVacia();
    void esCabeza();
    void esFinal();
    void esSiguiente();
    bool esActual();
    int valorActual();
    void recorrerLista();
};

//Lista Doble
class NodoListaD
{
private:
    int valor;
    NodoListaD *siguiente;
    NodoListaD *anterior;
    friend class ListaD;
public:
    NodoListaD(int v, NodoListaD *sig = NULL, NodoListaD *ant = NULL)
    {
        valor = v;
        siguiente = sig;
        anterior = ant;
    }
};
typedef NodoListaD *pnodolistad;

class ListaD
{
private:
    pnodolistad cabeza, actual, final;
public:
    ListaD()
    {
        cabeza=actual=final=NULL;
    }
    ~Lista();
    void insertarNodo(int v, char c);
    void borrarNodo(char c);
    void borrarNodoValor(int v);
    bool listaVacia();
    void esCabeza();
    void esFinal();
    void esSiguiente();
    void esAnterior();
    bool esActual();
    int valorActual();
    void recorrerLista(int);
};

class NodoArbol {
    private:
        // Miembros:
        int dato;
        NodoArbol *izquierdo;
        NodoArbol *derecho;
        friend class Arbol;

    public:
        // Constructor:
        NodoArbol(const int dat, NodoArbol *izq=NULL, NodoArbol *der=NULL) :
        dato(dat), izquierdo(izq), derecho(der) {}
};
typedef NodoArbol *pNodoArbol;

class Arbol {
    private:
        // Punteros de la lista, para cabeza y nodo actual:
        pNodoArbol raiz;
        pNodoArbol actual;
        int contador;
        int altura;

    public:
        // Constructor y destructor básicos:
        Arbol() : raiz(NULL), actual(NULL) {}
        ~Arbol() { Podar(raiz); }
        // Insertar en árbol ordenado:
        void Insertar(const int dat);
        // Borrar un elemento del árbol:
        void Borrar(const int dat);
        // Función de búsqueda:
        bool Buscar(const int dat);
        // Comprobar si el árbol está vacío:
        bool Vacio(pNodo r) { return r==NULL; }
        // Comprobar si es un nodo hoja:
        bool EsHoja(pNodo r) { return !r->derecho && !r->izquierdo; }
        // Contar número de nodos:
        const int NumeroNodos();
        const int AlturaArbol();
        // Calcular altura de un int:
        int Altura(const int dat);
        // Devolver referencia al int del nodo actual:
        int ValorActual() { return actual->dato; } //&ValorActual()
        // Moverse al nodo raiz:
        void Raiz() { actual = raiz; }
        // Aplicar una función a cada elemento del árbol:
        void InOrden(void (*func)(int&) , pNodo nodo=NULL, bool r=true);
        void PreOrden(void (*func)(int&) , pNodo nodo=NULL, bool r=true);
        void PostOrden(void (*func)(int&) , pNodo nodo=NULL, bool r=true);
        private:
        // Funciones auxiliares
        void Podar(pNodo &nodo);
        void auxContador(pNodo nodo);
        void auxAltura(pNodo nodo, int alt);
};

void Mostrar(int&);
void generarArbol(Arbol&);

#endif
