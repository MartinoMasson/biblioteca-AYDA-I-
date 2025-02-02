#ifndef FILA_H
#define FILA_H
#include "lista.h"

template <typename T>
class fila
{
    public:
        fila();
        virtual ~fila();
        void agregar_fila(const T & elemento);
        void eliminar_primero();
        const T & verprimero() const;
        int cantidad() const;
        bool es_vacia () const;

    private:
        lista<T> listafila;
};

#endif // FILA_H
