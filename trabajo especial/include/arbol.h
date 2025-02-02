#include "lista.h"
#include "libro.h"
#ifndef ARBOL_H
#define ARBOL_H


template <typename T>
class arbol
{
    public:
        arbol();
        virtual ~arbol();
        void agregar_arbol(T & e);
        bool es_vacio() const;
        bool pertenece(const T & e) const;
        int cantidad() const;
        int profundidad() const;
        lista<T> listado_elementos();
        const T & obtener(const T & e)const;
        int cantidad();
        int profundidad();
        lista<T> listado_hojas();
        lista<T> listado_rango(const T & emin,const T & emax);

    private:
        struct nodo {
            T elemento;
            nodo * izq; //menores izquierda
            nodo * der; //mayores derecha
        };

        void vaciar();
        void InsertarNodo(nodo* & cursor, T & e);
        void elementos(nodo*aux, lista<T>&listafinal);
        void eliminar(nodo*cursor);
        void BuscaHojas(nodo* cursor, lista<T>  & elementos) const;
        void buscar_rango(const T & emin,const T & emax, nodo*puntero,lista<T>& listarango);
        int RamaLarga(nodo* &cursor, int nivel);
        int CuentaElem(nodo* &cursor, int cant);
        const T & buscador(nodo*puntero,const T & e)const;

        nodo * raiz;
};

#endif // ARBOL_H
