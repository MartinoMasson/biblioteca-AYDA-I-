#include "filas.h"
#include "lista.h"
#include "cassert"

template <typename T> fila<T>::fila(){
}

template <typename T> fila<T>::~fila(){
}

template <typename T> void fila<T>::agregar_fila(const T & elemento){
    listafila.agregar_lista_inicio(elemento);
}

template <class T> bool fila<T>::es_vacia()const{
        return listafila.lista_vacio();
}

template <typename T> void fila<T>::eliminar_primero(){
    assert(!es_vacia());
    listafila.eliminar(verprimero());
}

template <typename T> const T & fila<T>::verprimero() const{
    return listafila.obtener(0);
}

template <typename T> int fila<T>::cantidad() const {
    return listafila.cantidad();
}

template class fila<int>;
template class fila<float>;
template class fila<long>;
template class fila<double>;
template class fila<char>;
