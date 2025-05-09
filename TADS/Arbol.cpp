/*********************************************************************************
-Nombres: Gabriel Jaramillo, Salomon Avila, Tomas Silva, Juan Pabon, Angel Morales
-Pontificia Universidad Javeriana
-Proyecto de Estructuras de Datos; Entrega 2
-Temas: TADs, Compilacion Modular, Contenedores, Estructuras Lineales
*********************************************************************************/
#include <vector>
#include <utility>
#include <queue>
#include <map>
#include "Arbol.h"
#include "Nodo.h"
#include "Imagen.h"

using namespace std;
/**
 * @brief Un comparador personalizado. Al momento de insertar nodos en la cola de
 * prioridad no se organizan por defecto dado que son apuntadores de una clase.
 * Para resolver esto se crea un comparador personalizado usando una funcion anonima
 * (funcion lambda) donde filtramos las frecuencias de cada uno de los nodos.
 * 
 */
auto comparador = [](Nodo* a, Nodo* b) {
    return a->getFrecuencia() > b->getFrecuencia();
};

/**
 * @brief Constructor por defecto
 * 
 */
Arbol::Arbol(){
    raiz = nullptr;
}
/**
 * @brief Getters y setters
 * 
 * 
 */
void Arbol::setRaiz(Nodo *ra){
    raiz = ra;
}

Nodo* Arbol::getRaiz(){
    return raiz;
}

map<int,vector<bool>> Arbol::getValores(){
    return valor;
}

/**
 * @brief Elimina recursivamente memoria del nodo raiz de un arbol
 * 
 * @param nodo 
 */
void Arbol::eliminar(Nodo* nodo){
    if(nodo != nullptr){
        eliminar(nodo->getNodoIzquierda());
        eliminar(nodo->getNodoDerecha());
        delete nodo;
    }
}
/**
 * @brief Usando las frecuencias se genera un arbol de Huffman usando
 * las frecuencias de los valores ya extraidas. Se usa un cola de prioridad
 * la cual está implementada bajo el concepto de min_heap.
 * Revisar las aclaraciones del readme.md
 * @param frecuencias 
 */
void Arbol::crearArbol(vector<pair<int,int>> frecuencias){
    priority_queue<Nodo*, std::vector<Nodo*>, decltype(comparador)> arbol(comparador);
    for(int i = 0; i<frecuencias.size(); i++){
        //cout<<"\nFrecuencia de "<<frecuencias[i].first<<" es de: "<<frecuencias[i].second;
        if(frecuencias[i].second > 0){
            //cout<<" pasa";
            Nodo *nuevo = new Nodo;
            nuevo->setEsHoja(true);
            nuevo->setFrecuencia(frecuencias[i].second);
            nuevo->setNodoDerecha(nullptr);
            nuevo->setNodoIzquierda(nullptr);
            nuevo->setValor(frecuencias[i].first);
            arbol.push(nuevo);
        }
    }
    while(arbol.size()>1){
        Nodo *auxiliarDerecha, *auxiliarIzquierda;
        auxiliarIzquierda = arbol.top();
        arbol.pop();
        auxiliarDerecha = arbol.top();
        arbol.pop();
        //cout<<"Calculando con frecuencias de "<<auxiliarIzquierda->getFrecuencia() <<" y "<<auxiliarDerecha->getFrecuencia()<<endl;
        Nodo *nuevo = new Nodo;
        nuevo->setNodoDerecha(auxiliarDerecha);
        nuevo->setNodoIzquierda(auxiliarIzquierda);
        nuevo->setEsHoja(false);
        nuevo->setFrecuencia( (auxiliarDerecha->getFrecuencia()) + (auxiliarIzquierda->getFrecuencia()));
        arbol.push(nuevo);
    }
    Nodo *raizArbol = arbol.top();
    //cout<<"la raiz tiene una frecuencia de: "<<raizArbol->getFrecuencia()<<endl;
    setRaiz(raizArbol);
}

/**
 * @brief Rellena los valores necesarios del mapa recorriendo el arbol
 * 
 * @param codigo 
 * @param raiz 
 */
void Arbol::completarValores(vector<bool> codigo, Nodo *raiz){
    //cout<<"es una hoja?"<<endl;
    if(raiz->getEsHoja() == true){
        //cout<<"si es una hoja"<<endl;
        valor.insert({raiz->getValor(),codigo});
        //cout<<"el valor de "<<raiz->getValor()<<" es: ";
        /*for(auto b : valor[raiz->getValor()]){
            cout<<b;
        }
        cout<<endl;*/
    }
    if(raiz->getNodoIzquierda() != nullptr){
        codigo.push_back(false);
        //cout<<"codigo es: ";
        //cout<<endl;
        completarValores(codigo,raiz->getNodoIzquierda());
        //cout<<"ya se mando por derecha"<<endl;
        codigo.pop_back();
    }
    if(raiz->getNodoDerecha() != nullptr){
        codigo.push_back(true);
        //cout<<"codigo es: ";
        //for(auto b : codigo){
        //    cout<<b;
        //}
        //cout<<endl;
        completarValores(codigo,raiz->getNodoDerecha());
    }
    //cout<<"ya se mando por izquieda"<<endl;
    
}

