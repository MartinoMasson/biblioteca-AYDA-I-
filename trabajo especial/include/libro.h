#ifndef LIBRO_H
#define LIBRO_H
#include "lista.h"
#include <iostream>
#include <fstream>

using namespace std;

class libro{
    public:
        libro();
        libro(string idnuevo, string autornuevo, string titulonuevo, int pagnuevo, int ejemplaresnuevo);
        ~libro();
        void agregar_genero(string generoagregado);
        string obtener_id()const;
        string obtener_autor()const;
        const lista<string> & obtener_generos()const;
        string obtener_titulo()const;
        int cantidad_pag()const;
        int cantidad_ejemplares()const;
        libro & operator=(const libro & l);
        bool operator==(const libro & l);
        bool operator!=(const libro & l);
        bool operator<(const libro & l);
        bool operator>(const libro & l);
        bool operator<=(const libro & l);
        bool operator>=(const libro & l);
        bool pertenece_genero(string generobuscado) const;

    private:
        struct librito{
            string id;
            string autor;
            lista<string> generos;
            string titulo;
            int pag;
            int ejemplares;
        };

        librito * libronuevo;
        void vaciar();

};

#endif // LIBRO_H
