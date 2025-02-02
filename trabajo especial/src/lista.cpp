#include <cassert>
#include <iostream>
#include "lista.h"
#include "libro.h"

using namespace std;

template <typename T> lista<T>::lista(){
    primero = NULL;
    ultimo=NULL;
}

template <typename T> lista<T>::~lista() {
    vaciar();
}

template <typename T> void lista<T>::vaciar(){
    nodo*cursor=primero;
    while (cursor != NULL){
        nodo * siguiente = cursor->sig;
        delete cursor;
        cursor=siguiente;
    }
    primero=NULL;
}

template <typename T> void lista<T>:: agregar_lista_inicio(const T & e){
    nodo*nuevo = new nodo;
    nuevo->elemento = e;
    if(lista_vacio()){
        primero=nuevo;
        primero->sig=NULL;
        ultimo=primero;
    }else{
        nuevo->sig = primero;
        primero = nuevo;
    }
}

template <typename T> void lista<T>::agregar_lista(const T & e, int pos){
    nodo*puntero=primero;
    nodo*anterior;
    nodo*nuevo = new nodo;
    nuevo->elemento = e;
    int posicion=0;
    if (pos==0){
        agregar_lista_inicio(e);
    }else if(pos>=cantidad()){
        agregar_lista_fin(e);
    }else{
        while (puntero->sig != NULL && pos == posicion){
            anterior=puntero;
            puntero = puntero->sig;
            posicion++;
        }
        nuevo->sig = puntero;
        anterior->sig = nuevo;
    }
}

template <typename T> void lista<T>:: agregar_lista_fin(const T & e){
    nodo*nuevo = new nodo;
    nuevo->elemento = e;
    nuevo->sig = NULL;
    if (primero == NULL){
        agregar_lista_inicio(e);
    }
    else {
        ultimo->sig = nuevo;
        ultimo = nuevo;
    }
}

template <typename T> bool lista<T>:: pertenece(const T & e)const{
    nodo*aux=primero;
    while (aux != NULL && !(aux->elemento ==e)){
        aux = aux-> sig;
    }
    if(aux != NULL){
        return true;
    }else{
        return false;
    }
}

template <typename T> void lista<T>:: eliminar(const T & e){
    nodo*cursor=primero;
    if (pertenece(e)){
        if (not(cursor->elemento ==e )){
            while (not(cursor->sig->elemento ==e)){
                cursor=cursor->sig;
            }
            nodo * eliminarnodo =cursor->sig;
            cursor->sig = eliminarnodo->sig;
            delete eliminarnodo;
        } else {
            primero = cursor->sig;
            delete cursor;
        }
    }
}

template <typename T> bool lista<T>:: lista_vacio()const{
    if (primero == NULL){
        return true;
    } else{
        return false;
    }
}

template <typename T> int lista<T>:: cantidad()const{
    //nodo*aux=primero;
    int cont = 0;
    for(nodo*aux=primero; aux != NULL; aux = aux->sig){
         cont ++;
    }
    return cont-1;
}

template <typename T> const T & lista<T>:: obtener(int posicion)const{
    nodo*aux=primero;
    int posactual=0;
    while (aux != NULL && posicion != posactual ){
        aux = aux->sig;
        posactual++;
    }
    if( aux != NULL){
        return aux->elemento;
    }
}

template <typename T> lista<T>& lista<T>::operator=(const lista<T>& otralista){
     vaciar();

    // Copiar los elementos de la otra lista
    if (otralista.primero != NULL) {
        nodo*cursor=otralista.primero;
        while (cursor != NULL) {
            agregar_lista_fin(cursor->elemento);
            cursor=cursor->sig;
        }
        delete cursor;
    } else {
        primero = NULL; // La lista está vacía
    }
    return *this;
}

template class lista<int>;
template class lista<float>;
template class lista<long>;
template class lista<char>;
template class lista<double>;
template class lista<string>;
template class lista<libro>;
