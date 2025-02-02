#include "lista.h"
#include "libro.h"
#include <iostream>
#include <fstream>

using namespace std;

libro::libro(){
    libronuevo = NULL;
}

libro::libro(string idnuevo, string autornuevo, string titulonuevo, int pagnuevo, int ejemplaresnuevo){
    libronuevo = new librito;
    libronuevo->id=idnuevo;
    libronuevo->autor=autornuevo;
    libronuevo->titulo=titulonuevo;
    libronuevo->pag=pagnuevo;
    libronuevo->ejemplares=ejemplaresnuevo;
}

void libro::agregar_genero(string generoagregad){
    libronuevo->generos.agregar_lista_fin(generoagregad);
}

libro::~libro() {
    vaciar();
}

void libro::vaciar(){
    libronuevo->generos.~lista();
    delete libronuevo;
}

string libro::obtener_id()const{
    return libronuevo->id;
}

string libro::obtener_autor()const{
    return libronuevo->autor;
}

const lista<string> & libro::obtener_generos()const{
    return libronuevo->generos;
}

string libro::obtener_titulo()const{
    return libronuevo->titulo;
}

int libro::cantidad_pag()const{
    return libronuevo->pag;
}

int libro::cantidad_ejemplares()const{
    return libronuevo->ejemplares;
}

libro & libro::operator=(const libro & l){
    libronuevo = new librito;
    libronuevo->id = l.obtener_id();
    libronuevo->autor= l.obtener_autor();
    libronuevo->generos=l.obtener_generos();
    libronuevo->titulo = l.obtener_titulo();
    libronuevo->pag = l.cantidad_pag();
    libronuevo->ejemplares = l.cantidad_ejemplares();
    return *this;
}

bool libro::operator==(const libro & l){
    return libronuevo->id == l.obtener_id();
}

bool libro::operator!=(const libro & l){
    return libronuevo->id != l.obtener_id();
}

bool libro::operator>(const libro & l){
    return libronuevo->id > l.obtener_id();
}

bool libro::operator<(const libro & l){
    return libronuevo->id < l.obtener_id();
}

bool libro::operator>=(const libro & l){
    return libronuevo->id >= l.obtener_id();
}

bool libro::operator<=(const libro & l){
    return libronuevo->id <= l.obtener_id();
}

bool libro::pertenece_genero(string generobuscado) const{
    return libronuevo->generos.pertenece(generobuscado);
}

