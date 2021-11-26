#include <iostream>
#include "Tipos.h"

using namespace std;

//Métodos de tipos de datos:
Lista::~Lista()
{
    pnodo aux;
    while(cabeza)
    {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    actual = NULL;
}

void Lista::insertarNodo(int v)
{
    pnodo aux;
    if (listaVacia())
    {
        cabeza = new Nodo(v, NULL);
        final = cabeza;
    }
    else
    {
        aux = new Nodo(vnuevo,NULL);
        actual -> siguiente = aux;
        final = aux;
    }
}

void Lista::insertarNodoIntermedio(int v, int posicion) //Hacer este método
{
    pnodo aux;
    if (listaVacia())
    {
        cabeza = new Nodo(v, NULL);
        final = cabeza;
    }
    else
    {
        int cont = 0;
        aux = new Nodo(v,NULL);
        while (actual -> valor != aux) //Localizar el nodo
        {
            cont++;
            aux ->siguiente
        }
    }
}

void Lista::borrarNodo(int v)
{
    pnodo anterior;
    actual = cabeza;
    while (actual->valor!=v && (actual->siguiente)!=NULL)
    {
        anterior=actual;
        actual=actual->siguiente;
    }
    if(actual==cabeza)   // Primer elemento
    {
        cabeza = actual->siguiente;
    }
    else
    {
        anterior->siguiente = actual->siguiente;
        if (actual==final)
        {
            final=anterior;
        }
    }
    actual->siguiente=NULL;
    delete actual;
}

bool Lista::listaVacia()
{
    return cabeza == NULL;
}

void Lista::recorrerLista()
{
    pnodo aux;
    aux = cabeza;
    while(aux)
    {
        cout << aux->valor << "-> ";
        aux = aux->siguiente;
    }
    cout << endl;
}

void Lista::esCabeza()
{
    actual = cabeza;
}

void Lista::esFinal()
{
    esCabeza();
    if(!listaVacia())
    {
        while(actual->siguiente)
        {
            esSiguiente();
        }
    }
}

void Lista::esSiguiente()
{
    if(actual) actual = actual->siguiente;
}

bool Lista::esActual()
{
    return actual != NULL;
}

int Lista::valorActual()
{
    return actual->valor;
}

//Lista Doble
const int ASCENDENTE=0;
const int DESCENDENTE=1;

ListaD::~ListaD()
{
    pnodo aux;
    esCabeza();
    while(cabeza)
    {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    cabeza=NULL;
    actual=NULL;
    final=NULL;
}

void ListaD::insertarNodo(int v, char c)
{
    pnodo aux;
    char tipoInsercion;
    tipoInsercion=c;
    if(listaDVacia()) // Si la lista está vacía
    {
        aux = new Nodo(v,NULL,NULL);
        final=cabeza=aux;
    }
    else if (tipoInsercion=='f') //Inserción por el final
    {
        aux= new Nodo(v,NULL,NULL);
        aux->anterior=final;
        final->siguiente=aux;
        final=aux;
    }
    else if (tipoInsercion=='p')  //Inserción por el principio
    {
        aux= new Nodo(v,NULL,NULL);
        aux->siguiente=cabeza;
        cabeza->anterior=aux;
        cabeza=aux;
    }
}

void ListaD::borrarNodo(char c)
{
    char tipoBorrado;
    tipoBorrado=c;
    if(tipoBorrado=='f')  //Eliminación por el final
    {
        pnodo aux=NULL;
        if((cabeza==final))   //Sólo hay elemento
        {
            aux=final;
            cabeza = final = NULL;
            aux=NULL;
            delete aux;
        }
        else
        {
            aux=final;
            final=final->anterior;
            aux->anterior=NULL;
            final->siguiente=NULL;
            delete aux;
        }
    }
    else if(tipoBorrado=='p')  //Eliminación por el Principio
    {
        pnodo aux=NULL;
        if((cabeza==final))  //Sólo hay elemento
        {
            aux=cabeza;
            cabeza = final = NULL;
            aux=NULL;
            delete aux;
        }
        else
        {
            aux=cabeza;
            cabeza=cabeza->siguiente;
            aux->siguiente=NULL;
            cabeza->anterior=NULL;
            delete aux;
        }
    }
}

void ListaD::borrarNodoValor(int v) //Hacer este método
{
    while !(v = Lista.valorActual())
    {
        Lista.recorrerLista(ASCENDENTE);
    }
    aux=cabeza;
    cabeza=cabeza->siguiente;
    aux->siguiente=NULL;
    cabeza->anterior=NULL;
    delete aux;
}

void ListaD::recorrerLista (int orden)
{
    pnodo aux;
    if (orden == ASCENDENTE)
    {
        esCabeza();
        aux = cabeza;
        while(aux)
        {
            cout << aux->valor << "-> ";
            aux = aux->siguiente;
        }
    }
    else
    {
        esFinal();
        aux = final;
        while(aux)
        {
            cout << aux->valor << "-> ";
            aux = aux->anterior;
        }
    }
    cout << endl;
}

bool ListaD::listaVacia()
{
    return cabeza == NULL;
}

void ListaD::esSiguiente()
{
    if(actual) actual = actual->siguiente;
}

void ListaD::esAnterior()
{
    if(actual) actual = actual->anterior;
}

void ListaD::esCabeza()
{
    actual=cabeza;
}

void ListaD::esFinal()
{
    actual=final;
}

bool ListaD::esActual()
{
    return actual != NULL;
}

int ListaD::valorActual()
{
    if (!listaDVacia()) return actual->valor;
    else return 0;
}

//Arbol
// Poda: borrar todos los nodos a partir de uno, incluido
void Arbol::Podar(pNodoArbol &NodoArbol)
{
   // Algoritmo recursivo, recorrido en postorden
   if(NodoArbol) {
      Podar(NodoArbol->izquierdo); // Podar izquierdo
      Podar(NodoArbol->derecho);   // Podar derecho
      delete NodoArbol;            // Eliminar nodo
      NodoArbol = NULL;
   }
}

// Insertar un int en el árbol ABB
void Arbol::Insertar(const int dat)
{
   pNodoArbol padre = NULL;

   actual = raiz;
   // Buscar el int en el árbol, manteniendo un puntero al nodo padre
   while(!Vacio(actual) && dat  != actual->dato) {
      padre = actual;
      if(dat > actual->dato) actual = actual->derecho;
      else if(dat < actual->dato) actual = actual->izquierdo;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if(!Vacio(actual)) return;
   // Si padre es NULL, entonces el árbol estaba vacío, el nuevo nodo será
   // el nodo raiz
   if(Vacio(padre)) raiz = new Nodo(dat);
   // Si el int es menor que el que contiene el nodo padre, lo insertamos
   // en la rama izquierda
   else if(dat < padre->dato) padre->izquierdo = new NodoArbol(dat);
   // Si el int es mayor que el que contiene el nodo padre, lo insertamos
   // en la rama derecha
   else if(dat > padre->dato) padre->derecho = new NodoArbol(dat);
}

// Eliminar un elemento de un árbol ABB
void Arbol::Borrar(const int dat)
{
   pNodoArbol padre = NULL;
   pNodoArbol nodo;
   int aux;

   actual = raiz;
   // Mientras sea posible que el valor esté en el árbol
   while(!Vacio(actual)) {
      if(dat == actual->dato) { // Si el valor está en el nodo actual
         if(EsHoja(actual)) { // Y si además es un nodo hoja: lo borramos
            if(padre){ // Si tiene padre (no es el nodo raiz)
               // Anulamos el puntero que le hace referencia
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            }
            delete actual; // Borrar el nodo
            actual = NULL;
            return;
         }
         else { // Si el valor está en el nodo actual, pero no es hoja
            // Buscar nodo
            padre = actual;
            // Buscar nodo más izquierdo de rama derecha
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo más derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            // Intercambiar valores de no a borrar u nodo encontrado
            // y continuar, cerrando el bucle. El nodo encontrado no tiene
            // por qué ser un nodo hoja, cerrando el bucle nos aseguramos
            // de que sólo se eliminan nodos hoja.
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
}

// Recorrido de árbol en inorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&);
void Arbol::InOrden(void (*func)(int&) , pNodoArbol nodo, bool r)
{
   if(r) nodo = raiz;
   if(nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
   func(nodo->dato);
   if(nodo->derecho) InOrden(func, nodo->derecho, false);
}

// Recorrido de árbol en preorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&);
void Arbol::PreOrden(void (*func)(int&), pNodoArbol nodo, bool r)
{
   if(r) nodo = raiz;
   func(nodo->dato);
   if(nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PreOrden(func, nodo->derecho, false);
}

// Recorrido de árbol en postorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&);
void Arbol::PostOrden(void (*func)(int&), pNodoArbol nodo, bool r)
{
   if(r) nodo = raiz;
   if(nodo->izquierdo) PostOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) PostOrden(func, nodo->derecho, false);
   func(nodo->dato);
}

// Buscar un valor en el árbol
bool Arbol::Buscar(const int dat)
{
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat == actual->dato) return true; // int encontrado
      else if(dat > actual->dato) actual = actual->derecho; // Seguir
      else if(dat < actual->dato) actual = actual->izquierdo;
   }
   return false; // No está en árbol
}

// Calcular la altura del nodo que contiene el int dat
int Arbol::Altura(const int dat)
{
   int altura = 0;
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; // int encontrado
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
   return -1; // No está en árbol
}

// Contar el número de nodos
const int Arbol::NumeroNodos()
{
   contador = 0;

   auxContador(raiz); // FUnción auxiliar
   return contador;
}

// Función auxiliar para contar nodos. Función recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
void Arbol::auxContador(pNodo nodo)
{
   contador++;  // Otro nodo
   // Continuar recorrido
   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del árbol, que es la altura del nodo de mayor altura.
const int Arbol::AlturaArbol()
{
   altura = 0;

   auxAltura(raiz, 0); // Función auxiliar
   return altura;
}

// Función auxiliar para calcular altura. Función recursiva de recorrido en
// postorden, el proceso es actualizar la altura sólo en nodos hojas de mayor
// altura de la máxima actual
void Arbol::auxAltura(pNodoArbol nodo, int a)
{
   // Recorrido postorden
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1);
   // Proceso, si es un nodo hoja, y su altura es mayor que la actual del
   // árbol, actualizamos la altura actual del árbol
   if(EsHoja(nodo) && a > altura) altura = a;
}

// Función mostrar el contenido de los nodos del árbol
void Mostrar(int &d)
{
   cout << d << ",";
}

//Funión que permite generar árboles de forma aleatoria
void generarArbol(Arbol& arbolNew)
{
    int i = 0;
    int num=0;
    int MAX=20;

    for (i=0;i<MAX;i++)
    {
        num=rand()%MAX;
        cout << num << endl;
        arbolNew.Insertar(num);
    }
}

