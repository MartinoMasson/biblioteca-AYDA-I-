#include "arbol.h"
#include "lista.h"
#include "libro.h"
#include <cstddef>
#include <iostream>

using namespace std;

template <typename T> arbol<T>::arbol(){
    raiz = NULL;
}

template <typename T> arbol<T>::~arbol(){
    eliminar(raiz);
}

template <typename T> void arbol<T>::eliminar(nodo*aux){
    if(aux==NULL){
        delete aux;
    }else if (aux->izq == NULL || aux->der==NULL){
        delete aux;
    }else if(aux!=NULL){
        if(aux->izq != NULL){
            eliminar(aux->izq);
        }
        if(aux->der != NULL){
            eliminar(aux->der);
        }
        delete aux;
    }
}

template <typename T> bool arbol<T>::es_vacio()const{
    if (raiz == NULL){
        return true;
    }else{
        return false;
    }
}

template <typename T> void arbol<T>::agregar_arbol(T & e){
    InsertarNodo(raiz, e);
}

template <typename T> void arbol<T>::InsertarNodo(nodo * & cursor, T & e){
    if(cursor==NULL){
        nodo * nuevo = new nodo();
        nuevo->elemento=e;
        nuevo->der=NULL;
        nuevo->izq=NULL;
        cursor=nuevo;
    }else{
        if(e < cursor->elemento){
            InsertarNodo(cursor->izq, e);
        }else{
            InsertarNodo(cursor->der, e);
        }
    }
}

template <typename T> bool arbol<T>::pertenece(const T & e)const{
    nodo * puntero = raiz;
    while (not(puntero == NULL) && not(puntero->elemento == e)){
        if(puntero->elemento > e){
            puntero= puntero->izq;
        } else{
            puntero= puntero->der;
        }
    }
    if (puntero == NULL){
        return false;
    }else if(puntero->elemento == e){
        return true;
    }
}

template <typename T> lista<T> arbol<T>::listado_elementos(){
    lista<T> listafinal;
    elementos(raiz,listafinal);
    return listafinal;
}

template <typename T> void arbol<T>::elementos(nodo*aux, lista<T>&listafinal){
    if(aux!=NULL){
        listafinal.agregar_lista_fin(aux->elemento);
        if(aux->izq != NULL){
            elementos(aux->izq,listafinal);
        }
        if(aux->der != NULL){
            elementos(aux->der,listafinal);
        }
    }
}

template <typename T> lista<T> arbol<T>::listado_hojas(){
    lista<T> elementos;
    BuscaHojas(raiz, elementos);
    return elementos;
}

template <typename T> void arbol<T>::BuscaHojas(nodo* cursor, lista<T> & elementos)const{
    if (cursor->der == NULL && cursor->izq == NULL) {
        elementos.agregar_lista_fin(cursor->elemento);
    }
    else {
        if (cursor->izq != NULL){
            BuscaHojas(cursor->izq, elementos);
        }
        if (cursor->der != NULL){
            BuscaHojas(cursor->der, elementos);
        }
    }
}

template <typename T> int arbol<T>:: profundidad(){
    int prof = RamaLarga(raiz, 0);
    return prof;
}

template <typename T> int arbol<T>::RamaLarga(nodo* &cursor, int nivel) {
    if (cursor == NULL) {
        return nivel;
    }
    int prof_izq = RamaLarga(cursor->izq, nivel + 1);
    int prof_der = RamaLarga(cursor->der, nivel + 1);

    if (prof_izq >= prof_der)
        return prof_izq;
    else
        return prof_der;
}

template <typename T> int arbol<T>:: cantidad(){
    int prof = CuentaElem(raiz, 1);
    return prof;
}

template <typename T> int arbol<T>::CuentaElem(nodo* &cursor, int cant) {
    if (cursor == NULL) {
        return cant;
    }

    int total = RamaLarga(cursor->izq, total + 1);
    total = RamaLarga(cursor->der, total + 1);

    return total;
}

template <typename T> const T & arbol<T>::obtener(const T & e)const{
    return buscador(raiz,e);
}

template <typename T> const T & arbol<T>::buscador(nodo*puntero,const T & e)const{
    if(puntero==NULL){
        return e;
    }else if(puntero->elemento==e){
        return puntero->elemento;
    }else if(puntero->elemento>e){
        return buscador(puntero->izq,e);
    }else if(puntero->elemento < e){
        return buscador(puntero->der,e);
    }

}

template <typename T> lista<T> arbol<T>::listado_rango(const T& emin, const T& emax) {
    lista<T> rango;
    buscar_rango(emin, emax, raiz, rango);
    return rango;
}

template <typename T> void arbol<T>::buscar_rango(const T& emin, const T& emax, nodo* puntero, lista<T>& listarango) {
    if (puntero != NULL) {
        if (puntero->elemento >= emin && puntero->elemento <= emax) {
            listarango.agregar_lista_fin(puntero->elemento);
        }
        if (puntero->izq != NULL && puntero->elemento >= emin) {
            buscar_rango(emin, emax, puntero->izq, listarango);
        }
        if (puntero->der != NULL && puntero->elemento <= emax) {
            buscar_rango(emin, emax, puntero->der, listarango);
        }
    }
}


template class arbol<int>;
template class arbol<float>;
template class arbol<long>;
template class arbol<double>;
template class arbol<char>;
template class arbol<libro>;
