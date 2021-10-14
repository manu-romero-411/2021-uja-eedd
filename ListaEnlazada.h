//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#ifndef EEDD_LISTAENLAZADA_H
#define EEDD_LISTAENLAZADA_H

template<class T>
class Nodo {
public:
    Nodo(){
        dato = 0;
        sig = 0;
    }
    T dato = 0;
    Nodo *sig;
    Nodo(T &aDato, Nodo *aSig = 0):
            dato(aDato), sig(aSig) {}
    //~Nodo();
};

template<class T>
class ListaEnlazada;

template<class T>
class Iterador {
    Nodo<T> *nodo;
    friend class ListaEnlazada<T>;
public:
    Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}
    bool fin() { return nodo == 0; }
    void siguiente() { nodo = nodo->sig; }
    T &dato() { return nodo->dato; }
};

template<class T>
class ListaEnlazada {
    private:
        Nodo<T>* nodoCabecera;
        Nodo<T>* nodoCola;
        int tama;
    public:
        ListaEnlazada<T>();
        ListaEnlazada<T>(const ListaEnlazada<T> &orig);
        ListaEnlazada<T>& operator=(const ListaEnlazada<T> &otro);
        T& inicio();
        T& fin();

        Iterador<T> iteradorInicio();
        Iterador<T> iteradorFinal();

        void insertaInicio(T& dato);
        void insertaFin(T& dato);
        void inserta(Iterador<T> &it, T& dato);
        void borraInicio();
        void borraFinal();
        void borra(Iterador<T> &it);
        int tam();
        bool buscar(T &dato, Iterador<T> &it);
        ~ListaEnlazada();
};

template <class T>
ListaEnlazada<T>::ListaEnlazada(){
    tama = 0;
}

template <class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &orig){
    nodoCola = 0;
    Nodo<T> *n;
    n = orig.nodoCabecera;
    while (n != 0) {
        this->insertaFin(n->dato);
        n = n->sig;
    }
}

template <class T>
ListaEnlazada<T>& ListaEnlazada<T>::operator=(const ListaEnlazada<T> &otro){
    Nodo<T> *p = nodoCabecera;
    while (p != 0) {
        Nodo<T> *borrado = p;
        p = p->sig;
        delete borrado;
    }
    nodoCabecera = 0;
    nodoCola = 0;

    p = otro.nodoCabecera;
    while (p != 0) {
        this->insertaFin(p->dato);
        p = p->sig;
    }
    return (*this);
}

template <class T>
T& ListaEnlazada<T>::inicio(){
    if (nodoCabecera == 0)
        throw std::out_of_range("[inicio] La lista esta vacia ");
    else
        return nodoCabecera->dato;
}

template <class T>
T& ListaEnlazada<T>::fin(){
    if (nodoCola == 0)
        throw std::out_of_range("[fin] La lista esta vacia ");
    else
        return nodoCola->dato;
}

template <class T>
Iterador<T> ListaEnlazada<T>::iteradorInicio() {
    return Iterador<T>(nodoCabecera);
}

template <class T>
Iterador<T> ListaEnlazada<T>::iteradorFinal() {
    return Iterador<T>(nodoCola);
}

template <class T>
void ListaEnlazada<T>::insertaInicio(T& dato){
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato, 0);

    if (nodoCola == 0)
        nodoCola = nuevo; // Esto solo ocurrirá si la lista está vacía
    else
        nuevo->sig = nodoCabecera;

    nodoCabecera = nuevo;
    tama++;
}

template <class T>
void ListaEnlazada<T>::insertaFin(T& dato){
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato, 0);

    if (nodoCabecera == 0)
        nodoCabecera = nuevo; // Esto solo ocurrirá si la lista está vacía
    else
        nodoCola->sig = nuevo;

    nodoCola = nuevo;
    tama++;
}

template <class T>
void ListaEnlazada<T>::inserta(Iterador<T> &it, T& dato){
    Nodo<T> *p = it.nodo;
    if (p == nodoCabecera) {
        this->insertaInicio(dato);
    } else if (p == nodoCola) {
        this->insertaFin(dato);
    } else {
        Nodo<T>* nuevo = new Nodo<T> (dato, p);
        nuevo->sig = p->sig;
        p->sig = nuevo;
        tama++;
    }
}

template <class T>
void ListaEnlazada<T>::borraInicio(){
    if (nodoCabecera == 0)
        throw std::out_of_range("[borraInicio] La lista esta vacia ");
    else {
        Nodo<T> *borrado = nodoCabecera;
        nodoCabecera = nodoCabecera->sig;
        delete borrado;
        if (nodoCabecera != 0)
            nodoCabecera->ant = 0;
        else
            nodoCola = 0;

        tama--;
    }
}

template <class T>
void ListaEnlazada<T>::borraFinal(){
    if (nodoCola == 0)
        throw std::out_of_range("[borraFinal] La lista esta vacia ");
    else {
        Nodo<T> *borrado = nodoCola;
        Iterador<T> it = nodoCabecera;
        for(int i = 0; i < tama - 1; i++){
            it.siguiente();
        }
        nodoCola = it;
        delete borrado;

        if (nodoCola != 0)
            nodoCola->sig = 0;
        else
            nodoCabecera = 0;

        tama--;
    }
}

template <class T>
void ListaEnlazada<T>::borra(Iterador<T> &it){
    Nodo<T> *p = it.nodo;
    if (p == 0)
        throw std::out_of_range("[borra] La lista esta vacia ");
    else {
        if (p == nodoCabecera) {
            this->borraInicio();
            this->iteradorInicio();
        } else {
            if (p == nodoCola) {
                this->borraFinal();
                p->sig;
            } else {
                Nodo<T>* borrado = p;
                Nodo<T>* anterior = 0;
                if (nodoCabecera != nodoCola){
                    anterior = nodoCabecera;
                    while (anterior->sig != p->dato){
                        anterior = anterior->sig;
                    }
                }
                anterior->sig = p->sig;
                delete borrado;
            }
        }
    }
}

template <class T>
int ListaEnlazada<T>::tam(){
    return tama;
}

template <class T>
bool ListaEnlazada<T>::buscar(T &dato, Iterador<T> &it){
    return (it->dato == dato);
}

template <class T>
ListaEnlazada<T>::~ListaEnlazada(){

        Nodo<T> *p = nodoCabecera;
        while (p != 0) {
            nodoCabecera=p->sig;
            delete p;
          p  =  nodoCabecera;
        }
}

#endif //EEDD_LISTAENLAZADA_H
