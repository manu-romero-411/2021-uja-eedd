/* 
 * File:   VDinamico.h
 * Author: Luis Miguel Valverde Merino, Manuel Jesús Romero Mateos
 *
 * Created on 19 de septiembre de 2019, 12:54
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <algorithm>
#include <math.h>
#include <stdexcept>
#include <climits>

/**
 * @brief Clase VDinamico.
 */
template <class T>
class VDinamico {
private:
    int tamf, taml;
    T *v;

public:
    VDinamico();
    VDinamico<T>(unsigned int taml);
    VDinamico<T>(const VDinamico<T>& origen);
    VDinamico<T>(const VDinamico<T>& origen, unsigned int inicio, unsigned int num); // unsigned indica que podamos poner negativos
    VDinamico<T>& operator=(VDinamico<T>& arr);
    T& operator[](int pos);
    void insertar(const T& dato, unsigned int pos);
    T borrar(unsigned int pos);
    void ordenar();
    int busquedaBin(T& dato);
    unsigned int tam();
    virtual ~VDinamico();
    T lee(unsigned pos);

};

/**
 * @brief En caso de no pasar argumentos al crear un objeto VDinamico, se construirá un vector vacío de tamaño físico 1.
 */
template <class T>
VDinamico<T>::VDinamico() {
    tamf = 1;
    taml = 0;
    v = new T[tamf];
}

/**
 * @brief Si se pasa el argumento tam al crear el objeto VDinamico, se podrá crear un vector cuyo
   tamaño será la potencia de 2 inmediatamente superior al valor de tam que hemos dado.
 */
template <class T>
VDinamico<T>::VDinamico(unsigned int tam) {
    taml=0;
    double tam_potencia=log2(tam);
    int tam_potencia_entera=(int)tam_potencia;
    tam=pow(2,(tam_potencia_entera+1));
    v=new T[tamf=tam];
}

/**
 * @brief Copiará un objeto VDinamico ya existente, en memoria dinámica aunque otra posición distinta al original.
 */
template <class T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen) {
    //Constructor de copia
    taml = origen.taml;
    tamf = origen.tamf;
    
    v = new T[tamf];
    for(int i=0; i<taml; i++){
        v[i]=origen.v[i];
    }
}


/**
 * @brief Copiará un objeto VDinamico ya existente, en memoria dinámica aunque 
  otra posición distinta al original. Solo copiará una cantidad de elementos 
  dada por inicio "(desde donde se van a copiar)" y num (número de datos que se copiarán).
 */
template <class T>
VDinamico<T>::VDinamico(const VDinamico<T>& origen, unsigned int inicio, unsigned int num) {
    //Constructor de copia parcial
    if (inicio>origen.taml) throw std::out_of_range("[VDinamico] Posicion no valida");
    
    taml = num;
    tamf = taml*2;
    
    v = new T[tamf];
    for(int i=0; i<taml; i++){
        v[i]=origen.v[inicio];
        inicio++;
    }
}

/**
 * @brief Igualará un objeto VDinamico a otro nuevo
  en otra posición de memoria, devolviéndonos un puntero al objeto original.
 */
template<class T>
VDinamico<T>& VDinamico<T>::operator=(VDinamico<T>& arr) {
    delete [] v;
    tamf = arr.tamf;
    taml = arr.taml;

    v = new T[tamf];
    for (int i = 0; i < taml; i++) {
        v[i] = arr.v[i];
    }
    return *this;
}

/**
 * @brief Permite la lectura y escritura de objetos de la clase VDinamico, 
            invalidando al usuario el poner posiciones no válidas en el vector.
 */
template<class T>
T& VDinamico<T>::operator[](int pos) {
    if (pos > tamf) throw std::out_of_range("[ operator[] ] Posicion no valida");
    return v[pos];
}

/**
 * @brief Inserta datos en el vector, y optimiza el vector ampliándolo a su tamaño doble en caso de que sea necesario.
 */
template<class T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos) {
    // El siguiente código verificará si al añadir el dato nuevo, nos vamos a quedar sin espacio físico en el vector,
    //duplicando tal espacio si es necesario antes de la inserción.
    if (pos > taml) throw std::out_of_range("[insertar] Posicion no valida");

    if (taml == tamf) {
        T *vaux;
        vaux = new T[tamf = tamf * 2];
        for (int i = 0; i < taml; i++) {
            vaux[i] = v[i];
        }
        delete [] v;
        v = vaux;
    }
    
    if (pos == 0) { // Si la posicion es 0 inserta por el final
        v[taml++] = dato;
    } else {
        for (unsigned i = taml - 1; i >= pos; i--) {
            v[i + 1] = v[i];
        }
        v[pos] = dato;
        taml++;
    }
}


/**
 * @brief Borra datos del vector, y optimiza el vector disminuyendo el tamaño a la mitad 
         si menos de un tercio del mismo está ocupado.
 */
template<class T>
T VDinamico<T>::borrar(unsigned int pos) {
    // El siguiente código eliminará el dato seleccionado según el parámetro pos, y manipulará el vector 
    //para que no haya espacios vacíos en una posición no terminal del mismo tras el borrado del dato pos.
    if (pos>taml) throw std::out_of_range("[borrar] Posicion no valida");
    
    if (pos == 0){ // Si la posicion es 0 borra por el final
            return v[--taml];
        } else{
            for (unsigned i=pos;i<taml;i++){
                v[i]=v[i+1];
            }
            taml--;
            return v[taml];
        }
    
    // El siguiente código acorta a la mitad el tamaño físico del vector si menos de un tercio del tamaño físico está ocupado
    if (taml*3<tamf){
        T *vaux;
        vaux = new T[tamf=tamf/2];
        for (int i=0; i<taml; i++){
            vaux[i]=v[i];
        }
        
        delete [] v;
        v=vaux;
    }
}

/**
 * @brief Ordena datos en el vector, usando la función sort en la biblioteca std.
 */
template<class T>
void VDinamico<T>::ordenar() {
    std::sort(v, v + taml);
}

/**
 * @brief Busca datos en el vector.
 */
template <class T>
int VDinamico<T>::busquedaBin(T& dato) {
    int inf = 0;
    int sup = taml - 1;
    int curIn;
    while (inf <= sup) {
        curIn = (inf + sup) / 2;
        if (v[curIn] == dato)
            return curIn;
        else if (v[curIn] < dato) inf = curIn + 1;
        else sup = curIn - 1;
    }
    return -1;
}


/**
 * @brief Devuelve el tamaño lógico del vector, es decir, lo que hay ocupado.
 */
template <class T>
unsigned int VDinamico<T>::tam() {
    return taml;
}


/**
 * @brief Borra el objeto vector.
 */
template <class T>
VDinamico<T>::~VDinamico() {
    delete [] v;
}

/**
 * @brief Devuelve el dato almacenado en la posición dada por el parámetro.
 */
template <class T>
T VDinamico<T>::lee(unsigned pos){
    return v[pos];
}

#endif /* VDINAMICO_H */

