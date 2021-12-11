#include <iostream>
#include "Tipos.h"

using namespace std;

//Métodos de tipos de datos:
Lista::~Lista()
{
    pNodoLista aux;
    while(cabeza)
    {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    actual = NULL;
}

void Lista::insertarNodo(Paquete p)
{
    pNodoLista aux;
    if (listaVacia())
    {
        cabeza = new NodoLista(p, NULL);
        final = cabeza;
    }
    else
    {
        aux = new NodoLista(p,NULL);
        aux->siguiente = actual->siguiente;
        actual->siguiente = aux;
        actual = aux;
        if (aux->siguiente==NULL) {
            final = aux;
        }
    }
}

pNodoLista Lista::borrarNodo()
{
    // Si la lista está vacía tiene que devolver un NULL y no hacer nada
    if (listaVacia()){
        return NULL;
    }

    pNodoLista nodoBorrado = NULL;
    pNodoLista aux = cabeza;
    if (cabeza==actual){
        cabeza = actual->siguiente;
    }
    else
    {
        while (aux!=NULL && aux->siguiente!=actual)
        {
            aux = aux->siguiente;
        }
        aux->siguiente=actual->siguiente;
        if (aux->siguiente==NULL){
            final=aux;
        }
    }
    nodoBorrado = actual;
    actual=actual->siguiente;
    nodoBorrado->siguiente=NULL;

    return nodoBorrado;
}

bool Lista::listaVacia()
{
    return cabeza == NULL;
}

void Lista::recorrerLista()
{
    pNodoLista aux;
    aux = cabeza;
    while(aux)
    {
        cout << aux->paquete.idPaquete << "-> ";
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

Paquete Lista::paqueteActual()
{
    return actual->paquete;
}



//Arbol
// Poda: borrar todos los nodos a partir de uno, incluido
void Arbol::podar(pNodoArbol &NodoArbol)
{
   // Algoritmo recursivo, recorrido en postorden
   if(NodoArbol) {
      podar(NodoArbol->izquierdo); // Podar izquierdo
      podar(NodoArbol->derecho);   // Podar derecho
      delete NodoArbol;            // Eliminar nodo
      NodoArbol = NULL;
   }
}

// Insertar un int en el árbol ABB
void Arbol::insertar(CP cp)
{
   pNodoArbol padre = NULL;

   actual = raiz;
   // Buscar el int en el árbol, manteniendo un puntero al nodo padre
   while(!vacio(actual) && cp.numCP  != actual->centralP.numCP) {
      padre = actual;
      if(cp.numCP > actual->centralP.numCP) actual = actual->derecho;
      else if(cp.numCP < actual->centralP.numCP) actual = actual->izquierdo;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if(!vacio(actual)) return;
   // Si padre es NULL, entonces el árbol estaba vacío, el nuevo nodo será
   // el nodo raiz
   if(vacio(padre)) raiz = new NodoArbol(cp);
   // Si el int es menor que el que contiene el nodo padre, lo insertamos
   // en la rama izquierda
   else if(cp.numCP < padre->centralP.numCP) padre->izquierdo = new NodoArbol(cp);
   // Si el int es mayor que el que contiene el nodo padre, lo insertamos
   // en la rama derecha
   else if(cp.numCP > padre->centralP.numCP) padre->derecho = new NodoArbol(cp);
}

// Eliminar un elemento de un árbol ABB
void Arbol::borrar(CP cp)
{
   pNodoArbol padre = NULL;
   pNodoArbol nodo;
   CP aux;

   actual = raiz;
   // Mientras sea posible que el valor esté en el árbol
   while(!vacio(actual)) {
      if(cp.numCP == actual->centralP.numCP) { // Si el valor está en el nodo actual
         if(esHoja(actual)) { // Y si además es un nodo hoja: lo borramos
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
            aux = actual->centralP;
            actual->centralP = nodo->centralP;
            nodo->centralP = aux;
            actual = nodo;
         }
      }
      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if(cp.numCP > actual->centralP.numCP) actual = actual->derecho;
         else if(cp.numCP < actual->centralP.numCP) actual = actual->izquierdo;
      }
   }
}

// Recorrido de árbol en inorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&);
void Arbol::inOrden(void (*func)(int&) , pNodoArbol nodo, bool r)
{
   if(r) nodo = raiz;
   if(nodo->izquierdo) inOrden(func, nodo->izquierdo, false);
   func(nodo->centralP.numCP);
   if(nodo->derecho) inOrden(func, nodo->derecho, false);
}

// Recorrido de árbol en preorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&);
void Arbol::preOrden(void (*func)(int&), pNodoArbol nodo, bool r)
{
   if(r) nodo = raiz;
   func(nodo->centralP.numCP);
   if(nodo->izquierdo) preOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) preOrden(func, nodo->derecho, false);
}

// Recorrido de árbol en postorden, aplicamos la función func, que tiene
// el prototipo:
// void func(int&);
void Arbol::postOrden(void (*func)(int&), pNodoArbol nodo, bool r)
{
   if(r) nodo = raiz;
   if(nodo->izquierdo) postOrden(func, nodo->izquierdo, false);
   if(nodo->derecho) postOrden(func, nodo->derecho, false);
   func(nodo->centralP.numCP);
}

// Buscar un valor en el árbol
pNodoArbol Arbol::buscar(CP cp)
{
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!vacio(actual)) {
      if(cp.numCP == actual->centralP.numCP) return actual; // int encontrado
      else if(cp.numCP > actual->centralP.numCP) actual = actual->derecho; // Seguir
      else if(cp.numCP < actual->centralP.numCP) actual = actual->izquierdo;
   }
   return NULL; // No está en árbol
}

// Calcular la altura del nodo que contiene el int dat
int Arbol::calculaAltura(CP cp)
{
   int altura = 0;
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while(!vacio(actual)) {
      if(cp.numCP == actual->centralP.numCP) return altura; // int encontrado
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(cp.numCP > actual->centralP.numCP) actual = actual->derecho;
         else if(cp.numCP < actual->centralP.numCP) actual = actual->izquierdo;
      }
   }
   return -1; // No está en árbol
}

// Contar el número de nodos
const int Arbol::numeroNodos()
{
   contador = 0;

   auxContador(raiz); // FUnción auxiliar
   return contador;
}

// Función auxiliar para contar nodos. Función recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
void Arbol::auxContador(pNodoArbol nodo)
{
   contador++;  // Otro nodo
   // Continuar recorrido
   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del árbol, que es la altura del nodo de mayor altura.
const int Arbol::alturaArbol()
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
   if(esHoja(nodo) && a > altura) altura = a;
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
//      arbolNew.insertar(num); // Santi, aquí tendríais que generar un CP de forma aleatoria. No entiendo la utilidad de este método. Yo lo quitaría
    }
}

