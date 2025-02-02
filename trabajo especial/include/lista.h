#ifndef CLASE_H
#define CLASE_H

template <typename T>
class lista {
public:
    lista();
    ~lista();
    void agregar_lista_inicio(const T & e);
    void agregar_lista(const T & e,int pos);
    void agregar_lista_fin(const T & e);
    bool pertenece(const T & e)const;
    void eliminar(const T & e);
    int cantidad()const;
    bool lista_vacio()const;
    const T & obtener(int posicion)const;
    lista& operator = (const lista &otralista);

private:
    struct nodo{
        T elemento;
        nodo * sig;
    };

    void vaciar();

    nodo * primero;
    nodo * ultimo;
};

#endif // CLASES_H_INCLUDED
