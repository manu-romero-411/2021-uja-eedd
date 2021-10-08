//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#ifndef EEDD_LISTAENLAZADA_H
#define EEDD_LISTAENLAZADA_H

template<class T>
class Iterador {
    Nodo<T> *nodo;
    friend class ListaEnlazada;
public:
    Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}
    bool fin() { return nodo == 0; }
    void siguiente() { nodo = nodo->sig; }
    T &dato() { return nodo->dato; }
};

template<class T>
class Nodo {
public:
    T dato;
    Nodo *sig;
    Nodo(T &aDato, Nodo *aSig = 0):
            dato(aDato), sig(aSig) {}
};

template<class T>
class ListaEnlazada<T> {
    private:
        Iterador<T> iterador;
        int tam;
    public:
        ListaEnlazada<T>();
        ListaEnlazada<T>(const ListaEnlazada<T> &orig);
        ListaEnlazada<T>& operator=(const ListaEnlazada<T> &otro);
        T& inicio();
        T& fin();
        void insertaInicio(T& dato);
        void insertaFin(T& dato);
        void inserta(Iterador<T> &it, T& dato);
        void borraInicio();
        void borraFinal();
        void borra(Iterador<T> &it);
        int tam();
        bool buscar();
        ~ListaEnlazada();
    }
};

template <class T>
ListaEnlazada<T>::ListaEnlazada(){

}

template <class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &orig){

}

template <class T>
ListaEnlazada<T>& ListaEnlazada<T>::operator=(const ListaEnlazada<T> &otro){

}

template <class T>
T& ListaEnlazada<T>::inicio(){

}

template <class T>
T& ListaEnlazada<T>::fin(){

}

template <class T>
void ListaEnlazada<T>::insertaInicio(T& dato){

}

template <class T>
void ListaEnlazada<T>::insertaFin(T& dato){

}

template <class T>
void ListaEnlazada<T>::inserta(Iterador<T> &it, T& dato){

}

template <class T>
void ListaEnlazada<T>::borraInicio(){

}

template <class T>
void ListaEnlazada<T>::borraFinal(){

}

template <class T>
void ListaEnlazada<T>::borra(Iterador<T> &it){

}

template <class T>
int ListaEnlazada<T>::tam(){

}

template <class T>
bool ListaEnlazada<T>::buscar(){

}

template <class T>
ListaEnlazada::~ListaEnlazada(){

}
#endif //EEDD_LISTAENLAZADA_H
