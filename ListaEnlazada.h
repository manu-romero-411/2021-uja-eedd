//
// Created by Manuel Jesús Romero Mateos on 8/10/21.
//

#ifndef EEDD_LISTAENLAZADA_H
#define EEDD_LISTAENLAZADA_H
/*
Clase nodo, elemento básico de la lista enlazada. Cuenta con dos punteros, uno al dato que
contiene y otro al siguiente nodo en la lista
*/

template<class T>
class Nodo {
    //Constructor poro defecto de nodom necesita la dirección del dato
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

/*
Clase iterador, herramienta del usuario para recorrer la lista enlazada
*/
template<class T>
class Iterador {
    Nodo<T> *nodo; //el iterador se apunta a un nodo
    friend class ListaEnlazada<T>;
public:
    Iterador(Nodo<T> *aNodo) : nodo(aNodo) {} //Constructor proporcionando un nodo
    bool fin() { return nodo == nullptr; } //Devuelve true si el nodo está vacío
    void siguiente() { nodo = nodo->sig; } //Pasa al siguiente nodo de la lista
    T &dato() { return nodo->dato; } //Devuelve la referencia al dato del nodo al que apunta
};

/*
Clase lista enlazada
*/
template<class T>
class ListaEnlazada {
    private:
        Nodo<T>* cabecera; //Puntero al primer elemento de la lista
        Nodo<T>* cola; //Puntero al ultimo elemento de la lista
        int tama; //Numero de elementos en la lista
    public:
        ListaEnlazada<T>(); //Constructor por defecto
        ListaEnlazada<T>(const ListaEnlazada<T> &orig); //Constructor copia
        ListaEnlazada<T>& operator=(const ListaEnlazada<T> &otro); //Operador de asignación
        T& inicio(); //Devuelve el dato en la primera posición de la lista (cabecera)
        T& fin();    //Devuelve el dato en la última posición de la lista (cola)

        Iterador<T> iteradorInicio(); //Crea un iterador al inicio de la lista
        Iterador<T> iteradorFinal(); //Crea un iterador al inicio de la lista

        void insertaInicio(T& dato); //Inserta un dato al inicio de la lista
        void insertaFin(T& dato); //Inserta un dato al final de la lista
        void inserta(Iterador<T> &it, T& dato); //Inserta un dato en la posición donde apunta el iterador de la lista
        void borraInicio(); //Borra el primer elemento
        void borraFinal(); //Borra el ultimo elemento
        void borra(Iterador<T> &it); //Borra el elemento indicado por el iterador
        int tam(); //devuelve el numero de elementos
        bool buscar(T &dato, Iterador<T> &it); //Indica si un elemento concreto está en la posición indicada por el iterador
        ~ListaEnlazada();
};

/**
* @brief Constructor por defecto
* @param[in]
* @param[out] -
* @return -
*
*
*/
template <class T>
ListaEnlazada<T>::ListaEnlazada(){
    tama = 0;
    cabecera = nullptr;
    cola = nullptr;
}

/**
* @brief Constructor copia
* @param[in] Referencia a un objeto ListaEnlazada
* @param[out] -
* @return -
*
*
*/
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
}

/**
* @brief Operador de asignación
* @param[in] Referencia a un objeto ListaEnlazada
* @param[out] -
* @return - Devuelve un puntero a este objeto (Para asignaciones encadenadas)
*
*
*/
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

/**
* @brief Devuelve el dato al inicio de la lista
* @param[in] -
* @param[out] -
* @return - Dato en la lista
*
*
*/
template <class T>
T& ListaEnlazada<T>::inicio(){
    if (cabecera == nullptr)
        throw std::out_of_range("[inicio] La lista esta vacia ");
    else
        return cabecera->dato;
}
/**
* @brief Devuelve el dato al final de la lista
* @param[in] -
* @param[out] -
* @return - Dato en la lista
*
*
*/

template <class T>
T& ListaEnlazada<T>::fin(){
    if (cola == nullptr)
        throw std::out_of_range("[fin] La lista esta vacia ");
    else
        return cola->dato;
}
/**
* @brief Devuelve un iterador apuntando al inicio de la lista
* @param[in] -
* @param[out] -
* @return - Objeto Iterador
*
*
*/

template <class T>
Iterador<T> ListaEnlazada<T>::iteradorInicio() {
    return Iterador<T>(cabecera);
}

/**
* @brief Devuelve un iterador apuntando al final de la lista
* @param[in] -
* @param[out] -
* @return - Objeto Iterador
*
*
*/
template <class T>
Iterador<T> ListaEnlazada<T>::iteradorFinal() {
    return Iterador<T>(cola);
}


/**
* @brief Inserta un elemento al principio de la lista
* @param[in] -Referencia al objeto a insertar
* @param[out] -
* @return - 
*
*
*/

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


/**
* @brief Inserta un elemento al final de la lista
* @param[in] -Referencia al objeto a insertar
* @param[out] -
* @return -
*
*
*/
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

/**
* @brief Inserta un elemento en una posición de la lista
* @param[in] -Referencia al objeto a insertar, iterador indicando a la posición
* @param[out] -
* @return -
*
*
*/

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

/**
* @brief Borra el elemento al principio de la lista
* @param[in] -
* @param[out] -
* @return -
*
*
*/

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

/**
* @brief Borra un elemento al final de la lista
* @param[in] -Referencia al objeto a insertar, iterador indicando a la posición
* @param[out] -
* @return -
*
*
*/

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
/**
* @brief Borra un elemento en una posición de la lista
* @param[in]  Iterador indicando a la posición
* @param[out] -
* @return -
*
*
*/

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
/**
* @brief Busca si está un dato en una posición determinada
* @param[in]  Iterador indicando a la posición, objeto a buscar
* @param[out] - 
* @return Booleano indicando si se ha encontrado el elemento
*
*
*/

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
