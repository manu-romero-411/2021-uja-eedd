//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#ifndef EEDD_LISTAENLAZADA_H
#define EEDD_LISTAENLAZADA_H

template<class T>
class Nodo {
public:
    Nodo(){
        dato = nullptr ;
        sig = nullptr;
    }
    T dato = 0;
    Nodo *sig;
    Nodo(T &aDato, Nodo *aSig = nullptr):
            dato(aDato), sig(aSig) {}
};

template<class T>
class ListaEnlazada;

template<class T>
class Iterador {
    Nodo<T> *nodo;
    friend class ListaEnlazada<T>;
public:
    Iterador(Nodo<T> *aNodo) : nodo(aNodo) {}
    bool fin() { return nodo == nullptr; }
    void siguiente() { nodo = nodo->sig; }
    T &dato() { return nodo->dato; }
};

template<class T>
class ListaEnlazada {
    private:
        Nodo<T>* cabecera;
        Nodo<T>* cola;
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
    cabecera = nullptr;
    cola = nullptr;
}

template <class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada<T> &orig){
    cabecera = nullptr;
    cola = nullptr;
    tama = 0;
    Nodo<T> *n;
    n = orig.cabecera;
    while (n != nullptr) {
        this->insertaFin(n->dato);
        n = n->sig;
    }
    //this->tama = orig.tama;
}

template <class T>
ListaEnlazada<T>& ListaEnlazada<T>::operator=(const ListaEnlazada<T> &otro){
    Nodo<T> *p = cabecera;
    while (p != nullptr) {
        Nodo<T> *borrado = p;
        p = p->sig;
        delete borrado;
    }
    cabecera = nullptr;
    cola = nullptr;
    tama = 0;

    p = otro.cabecera;
    while (p != nullptr) {
        this->insertaFin(p->dato);
        p = p->sig;
    }
    return (*this);
}

template <class T>
T& ListaEnlazada<T>::inicio(){
    if (cabecera == nullptr)
        throw std::out_of_range("[inicio] La lista esta vacia ");
    else
        return cabecera->dato;
}

template <class T>
T& ListaEnlazada<T>::fin(){
    if (cola == nullptr)
        throw std::out_of_range("[fin] La lista esta vacia ");
    else
        return cola->dato;
}

template <class T>
Iterador<T> ListaEnlazada<T>::iteradorInicio() {
    return Iterador<T>(cabecera);
}

template <class T>
Iterador<T> ListaEnlazada<T>::iteradorFinal() {
    return Iterador<T>(cola);
}

template <class T>
void ListaEnlazada<T>::insertaInicio(T& dato){
    Nodo<T> *nuevo;
    nuevo = new Nodo<T>(dato, nullptr);

    if (cola == nullptr)
        cola = nuevo; // Esto solo ocurrirá si la lista está vacía
    else
        nuevo->sig = cabecera;

    cabecera = nuevo;
    tama++;
}

template <class T>
void ListaEnlazada<T>::insertaFin(T& dato){
    Nodo<T> *nuevo = new Nodo<T>(dato, nullptr);

    if (cabecera == nullptr)
        cabecera = nuevo; // Esto solo ocurrirá si la lista está vacía
    else
        cola->sig = nuevo;

    cola = nuevo;
    tama++;
}

template <class T>
void ListaEnlazada<T>::inserta(Iterador<T> &it, T& dato){
    Nodo<T> *p = it.nodo;
    if (p == cabecera) {
        this->insertaInicio(dato);
    } else if (p == cola) {
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
    if (cabecera == nullptr) {
        throw std::out_of_range("[borraInicio] La lista esta vacia ");
    } else {
        Nodo<T> *borrado = cabecera;
        cabecera = cabecera->sig;
        delete borrado;
        if (cabecera == nullptr) {
            cola = nullptr;
        }
        tama--;
    }
}

template <class T>
void ListaEnlazada<T>::borraFinal(){
    if (cola == 0)
        throw std::out_of_range("[borraFinal] La lista esta vacia ");
    else {
        Nodo<T> *p = this->cabecera;
        Nodo<T> *borrado = this->cola;
        for(int i = 0; i < (tama-1); ++i){
            if (p->sig != cola) {
                p = p->sig;
            }
        }

        cola = p;
        delete borrado;

        if (cola != nullptr)
            cola->sig = nullptr;
        else
            cabecera = nullptr;

        tama--;
    }
}

template <class T>
void ListaEnlazada<T>::borra(Iterador<T> &it){
    Nodo<T> *p = it.nodo;
    if (p == nullptr)
        throw std::out_of_range("[borra] La lista esta vacia ");
    else {
        if (p == cabecera) {
            this->borraInicio();
        } else {
            if (p == cola) {
                this->borraFinal();
            } else {
                Nodo<T>* borrado = p;
                Nodo<T>* anterior = nullptr;
                if (cabecera != cola){
                    anterior = cabecera;
                    while (anterior->sig != p){
                        anterior = anterior->sig;
                    }
                }
                anterior->sig = p->sig;
                delete borrado;
                tama--;
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
    Nodo<T> *p = it.nodo;
    while(p != cola){
        if(p->dato == dato){
            return true;
        } else {
            p=p->sig;
            it.nodo = p;
        }
    }
    if (p->dato == cola->dato){
        return true;
    } else {
        return false;
    }
}

template <class T>
ListaEnlazada<T>::~ListaEnlazada(){
    Nodo<T> *p = this->cabecera;
    while (p) {
        Nodo<T>* tmp = p;
        p=p->sig;
        delete tmp;
    }
}

#endif //EEDD_LISTAENLAZADA_H
