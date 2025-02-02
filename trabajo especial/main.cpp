#include "arbol.h"
#include "Lista.h"
#include "filas.h"
#include "libro.h"
#include <iostream>
#include <fstream>

using namespace std;
int opciones();
void procesar_archivo_entrada(string origen,arbol<libro>& biblioteca,lista<libro>& lista_biblioteca);
void menu(const arbol<libro> &  biblioteca,lista<libro>& lista_biblioteca);
void cant_por_id(string idbuscada, const arbol<libro> & biblioteca);
void mostrar_libros(string generobuscado, const lista<libro> &  lista_biblioteca);
void mostrar_listarango(lista<libro>& lista_biblioteca,const int minpag,const int maxpag);
void mostrar_atributos(const libro & librobuscado);
void crea_archivo_texto(ofstream & archsalida, const libro & librobuscado);

int main(){
    arbol<libro> biblioteca;
    lista<libro> lista_biblioteca;
    procesar_archivo_entrada("datasets/biblioteca1.csv",biblioteca,lista_biblioteca);

    menu(biblioteca,lista_biblioteca);
    return 0;
}

int opciones(){
    int seleccion=0;
    while(seleccion > 5 || seleccion < 1){
        cout << " -------------------------------------------------------------- " <<endl;
        cout << "|Elige una opcion a realizar seleccionando por numero de indice:|" <<endl;
        cout << "|1. Cantidad de ejemplares por ID.                              |" <<endl;
        cout << "|2. Buscar libros por genero.                                   |" <<endl;
        cout << "|3. Buscar libros por rango de cantidad de paginas.             |" <<endl;
        cout << "|4. Salir.                                                      |" <<endl;
        cout << " -------------------------------------------------------------- " <<endl;
        cin >> seleccion;
        //system("cls");
    }
    return seleccion;
}

void menu(const arbol<libro> &  biblioteca,lista<libro>& lista_biblioteca){
    int opcion=opciones();
    while(opcion != 4){
        switch (opcion) {
            case 1:{
                string idbuscada;
                cout<< "Ingresa un ID para buscar la cantidad de ejemplares." <<endl;
                cin >> idbuscada;
                cant_por_id(idbuscada, biblioteca);
                break;
            }

            case 2:{
                string generobuscado;
                cout << "Ingresa el genero que quieras leer." <<endl;
                cin >> generobuscado;
                mostrar_libros(generobuscado,lista_biblioteca);
                break;
            }

            case 3:{
                int minpag, maxpag;
                cout << "Ingresa un minimo de paginas." <<endl;
                cin >> minpag;
                cout << "Ingresa un maximo de paginas." <<endl;
                cin >> maxpag;
                if (minpag >= 0 && maxpag >= minpag){
                        mostrar_listarango(lista_biblioteca,minpag,maxpag);
                }else
                    cout << "Valor/es ingresado/s invalido/s. Por favor, vuelva a intentarlo." << endl;

                break;
            }

            case 4:{
                system("cls");
                cout<< "Hasta pronto!" <<endl;
                break;
            }
        }
        if(opcion!=4){
            cout<<endl;
            cout<<endl;
            opcion=opciones();
        }
    }
}

void cant_por_id(string idbuscada, const arbol<libro> & biblioteca){
    libro librobuscado = libro(idbuscada,"","",0,0);
    if(biblioteca.pertenece(librobuscado))
        cout << "La cantidad de ejemplares con el ID ingresado es: " << biblioteca.obtener(librobuscado).cantidad_ejemplares()<< "." << endl;
    else
        cout<<"El libro no fue encontrado";
    librobuscado.~libro();
}

void mostrar_libros(string generobuscado, const lista<libro> &  lista_biblioteca){
    string resultado = "archivos de textos/Libros por genero " + generobuscado + ".txt";
    ofstream archsalida(resultado, ios::trunc);

    for (int i=0; i <= lista_biblioteca.cantidad(); i++){
        if (lista_biblioteca.obtener(i).pertenece_genero(generobuscado)){
            crea_archivo_texto(archsalida,lista_biblioteca.obtener(i));
            mostrar_atributos(lista_biblioteca.obtener(i));
        }
    }
    archsalida.close();
}

void crea_archivo_texto(ofstream & archsalida, const libro & librobuscado){
    if (archsalida.is_open()) {
        archsalida << librobuscado.obtener_id() << "  ";
        archsalida << librobuscado.obtener_autor() << "  ";
        archsalida << librobuscado.obtener_titulo() << "  ";
        for (int i = 0; i <= librobuscado.obtener_generos().cantidad(); i++){
            archsalida << librobuscado.obtener_generos().obtener(i) << ", ";
        }
        archsalida << librobuscado.cantidad_pag() << "  ";
        archsalida << librobuscado.cantidad_ejemplares() << "\n\n";
    } else
        cout << "Error al crear el archivo de salida\n";
}

void mostrar_listarango(lista<libro>& lista_biblioteca,const int minpag,const int maxpag){
    string resultado = "archivos de textos/Libros por rangoPag. " + to_string(minpag) + "-" + to_string(maxpag) + ".txt";
    bool existen =false;

    ofstream archsalida(resultado, ios::trunc);
    for (int i=0; i <= lista_biblioteca.cantidad(); i++){
        int cantidadpag=lista_biblioteca.obtener(i).cantidad_pag();
        if(cantidadpag>=minpag && cantidadpag<=maxpag){
            existen =true;
            crea_archivo_texto(archsalida,lista_biblioteca.obtener(i));
            mostrar_atributos(lista_biblioteca.obtener(i));
        }
    }
    if(!existen)
        cout<<"No hay libros en este rango";
    archsalida.close();
}

void mostrar_atributos(const libro & librobuscado){
    cout << "ID: " << librobuscado.obtener_id() << ", " << "Autor: " << librobuscado.obtener_autor() << ", " << "Titulo: "<< librobuscado.obtener_titulo() << ", " << "Cantidad de paginas:" << librobuscado.cantidad_pag() << ", " << "Cantidad de ejemplares: " << librobuscado.cantidad_ejemplares() << "," << "generos: ";
    for (int i = 0; i <= librobuscado.obtener_generos().cantidad(); i++){
        cout << librobuscado.obtener_generos().obtener(i) << ", ";
    }
    cout << endl;
}


void procesar_archivo_entrada(string origen,arbol<libro>& biblioteca,lista<libro>& lista_biblioteca){
    ifstream archivo(origen.c_str());
    if (!archivo.is_open()){
        cout << "No se pudo abrir el archivo: " << origen << endl;
        exit(1);
    }else {
        string linea;
        getline(archivo, linea);
        cout << "Se cargaron " << atoi(linea.c_str()) << " libros." << endl;

        //Descartamos la primera linea de titulos
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            int pos_inicial = 0;
            int pos_final = linea.find(';');
            string id = linea.substr(pos_inicial, pos_final).c_str();

            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string titulo = linea.substr(pos_inicial, pos_final - pos_inicial);

            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string autor = linea.substr(pos_inicial, pos_final - pos_inicial);

            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            int paginas = atoi(linea.substr(pos_inicial, pos_final - pos_inicial).c_str());

            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            int ejemplares = atoi(linea.substr(pos_inicial, pos_final - pos_inicial).c_str());

            string generos = linea.substr(pos_final + 1, linea.size());
            int pos_inicial_guion = 0, pos_final_guion = 0;

            //creacion del libro
            cout << id << " " << titulo << " " << autor << " " << paginas << " " << ejemplares << " ";
            libro libronuevo =  libro(id,autor, titulo,paginas,ejemplares);
            while (pos_final_guion != -1) {
                pos_final_guion = generos.find('-', pos_inicial_guion);
                string genero = generos.substr(pos_inicial_guion, pos_final_guion - pos_inicial_guion);
                pos_inicial_guion = pos_final_guion + 1;

                libronuevo.agregar_genero(genero);
                cout << genero << ", ";
            }
            cout<<endl;
            biblioteca.agregar_arbol(libronuevo);
            lista_biblioteca.agregar_lista_fin(libronuevo);
        }
    }
}

