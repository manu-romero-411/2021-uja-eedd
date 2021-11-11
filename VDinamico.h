/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VDinamico.h
 * Author: manuel
 *
 * Created on 25 de septiembre de 2021, 9:26
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H
#define UINT_MAX 4294967295
#include <climits>

#include <algorithm>
#include <math.h>
#include <stdexcept>
#include <ostream>
#include "Dosis.h"
#include <iostream>


template <class T>
class VDinamico {
private:
    int tamFisico; //tamaño que el vector ocupa en memoria
    int tamLogico; //tamaño ocupado del vector, número de elementos que tiene
    T *v;// Puntero al tipo de dato
    void ampliar();
    void reducir();
public:
    VDinamico(); // Constructor por defecto
    virtual ~VDinamico(); //Destructor
    VDinamico<T>(unsigned int tamNue);//Vector Parametrizado con un tamaño nueevo
    VDinamico<T>(const VDinamico<T> &orig); //Constructor copia total
    VDinamico<T>(const VDinamico<T> &orig, unsigned int desde, unsigned int num);//Constructor copia parcial
    VDinamico<T> &operator=(const VDinamico<T> &comp);//Operador de asignación
    T &operator[](const int pos) const;//Operación de lectura en una posición determinada
    void insertar(const T &dato, unsigned int pos = UINT_MAX); //Insertar un dato en una posición determinada
    void insertaFinal(const T& dato); //Insertar un dato al final del vector
    T borrar(unsigned int pos = UINT_MAX); //Borrar un dato en una posición determinada
    void ordenar(); //Ordenar el vector de menor a mayor
    void ordenarRev();//Ordenar el vector de menor a mayor
    T * leer(unsigned pos) const;//Devuelve el dato en una posición dada
    int getTamLogico();//Devuelve el número de elementos en el vector
    int busquedaBin(T &dato, int inferior, int superior);//Búsqueda binaria en vector ordenado
    bool operator==(const VDinamico<T> &elDeLaDerecha) const;
    bool operator!=(const VDinamico<T> &elDeLaDerecha) const;
    void print();
    friend ostream &operator<<(ostream &os, const VDinamico &dinamico);
 };
/**
 * @brief Constructor por defecto, inicia el vector al mínimo
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */

template <class T>
VDinamico<T>::VDinamico() {
    tamFisico = 1;
    tamLogico = 0;
    v = new T[tamFisico];
}


/**
 * @brief Constructor Parametrizado, inicia el vector a un tamaño determinado
 * @param[in]  Entero que indica un tamaño concreto
 * @param[out] -
 * @return -
 * 
 * 
 */
template <class T>
VDinamico<T>::VDinamico(unsigned int tamNue) {
    tamLogico = 0;
    double tam_potencia = log2f(tamNue);
    int tam_potencia_entera = (int)tam_potencia; // El tamaño que hemos pasado es 2^tam_potencia, pero es un valor no entero. Lo casteamos para trabajar con enteros.
    tamNue = powf(2,(tam_potencia_entera+1)); // potencia de 2 inmediatamente superior a tamNue
    v = new T[tamFisico = tamNue];
}
    
    /**
 * @brief Constructor copia
 * @param[in] Referencia a un objeto Vdinamico
 * @param[out] -
 * @return -
 * 
 * 
 */
    
template <class T>
VDinamico<T>::VDinamico(const VDinamico<T>& orig) {
    tamLogico = orig.tamLogico;
    tamFisico = orig.tamFisico;
    delete []v;
    v = new T[tamFisico];
    for(int i = 0; i < tamLogico; ++i){
        v[i] = orig.v[i];
    }
}

        /**
 * @brief Constructor copia de unos elementos específicos de otro vector
 * @param[in] Referencia a un objeto Vdinamico, dos enteros para marcar el inicio y fin de la copia
 * @param[out] -
 * @return -
 * 
 * 
 */
    template <class T>
    VDinamico<T>::VDinamico(const VDinamico<T>& orig, unsigned int desde, unsigned int num) {
        //Constructor de copia parcial
        if (desde > orig.tamLogico) throw std::out_of_range("[VDinamico] Posición no valida al llamar a constructor de copia parcial");

        tamLogico = num;
        tamFisico = tamLogico * 2;

        v = new T[tamFisico];
        for(int i = 0; i < tamLogico; ++i){
            v[i] = orig.v[desde];
            desde++;
        }
    }
    
 /* @brief Operador de asignación
 * @param[in] Borra los elementos originales y asigna los nuevos
 * @param[out] -
 * @return puntero al nuevo Vdinámico
 * 
 * 
 */
template <class T>
VDinamico<T>& VDinamico<T>::operator=(const VDinamico<T>& comp) {
    tamFisico = comp.tamFisico;
    tamLogico = comp.tamLogico;
    delete [] v;

    v = new T[tamFisico];
    for (int i = 0; i < tamLogico; i++) {
        v[i] = comp.v[i];
    }
    return *this;
}
    
 /* @brief Operador de lectura
 * @param[in] Devuelve el elemento en la posición
 * @param[out] -
 * @return Devuelve el elemento en la posición
 * 
 *
 */
    template<class T>
    T& VDinamico<T>::operator[](const int pos) const{
        if (pos > tamLogico) throw std::out_of_range("[ operator[] ] Posición no valida al usar el operador []");
        return v[pos];
    }
    
    
 /* @brief Inserta el elemento en una posición, reordena los que están despues de la posición
 * @param[in] El dato, y la posición deseada
 * @param[out] -
 * @return -
 */
    template<class T>
    void VDinamico<T>::insertar(const T& dato, unsigned int pos) {
        if (pos > tamLogico) throw std::out_of_range("[insertar] Posicion no valida");

        this->ampliar();

        // INSERTAR AL FINAL (O(1))
        if ((pos == tamLogico) || (pos == UINT_MAX)){
            v[tamLogico] = dato;
        } else {
            
            // INSERTAR AL PRINCIPIO O ENMEDIO (O(n))
            for (unsigned i = tamFisico - 1; i >= pos; --i) {
                v[i + 1] = v[i];
            }
            v[pos] = dato;
        }
        tamLogico++;
    }

/* @brief Inserta el elemento al final del vector
* @param[in] Dato que queremos insertar, de tipo T
* @param[out] -
* @return -
*/

    template<class T>
    void VDinamico<T>::insertaFinal(const T& dato){
        if (tamLogico + 1 > tamFisico) this->ampliar();
        v[tamLogico] = dato;
        tamLogico++;
    }
/* @brief Borra el elemento en una posición, reordena los demás
 * @param[in] Devuelve el elemento en la posición
 * @param[out] -
 * @return -devuelve el elemento en la posición
 * 
 * 
 */
    template<class T>
    T VDinamico<T>::borrar(unsigned int pos) {

        if (pos>tamLogico) throw std::out_of_range("[borrar] Posición no valida");

        if ((pos == tamLogico) || (pos == UINT_MAX)){
            return v[--tamLogico];
        } else {
            for (unsigned i = pos; i < tamLogico; i++){
                v[i] = v[i+1];
            }
            tamLogico--;
            return v[tamLogico];
        }

        this->reducir();
    }
    /* @brief
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */
    template<class T>
    void VDinamico<T>::ordenar()  {
        std::sort(this->v, this-> v + tamLogico);
        //ordenado = true;
    }
    
    
     /* @brief ordena el vector de menor a mayor
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */
    
    template<class T>
    void VDinamico<T>::ordenarRev()  {
        ordenar();
        for(int i = 0, j = tamLogico - 1; i < tamLogico/2; ++i, --j){
            T auxiliar;
            auxiliar = this->v[i];
            this->v[i] = this->v[j];
            this->v[j] = auxiliar;     
        }
    }

 /* @brief oDestructor
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */
    template <class T>
    VDinamico<T>::~VDinamico() {
        delete [] v;
    }

    /**
     * @brief Devuelve el dato almacenado en la posición dada por el parámetro.
     * @param[in] Posición a leer
     * @return referencia al elemento seleccionado
     */
    template <class T>
    T * VDinamico<T>::leer(unsigned pos) const {
        return &v[pos];
    }
    
    
     /* @brief Devuelve el tamaño lógico
 * @param[in] -
 * @param[out] -
 * @return - tamaño logico
 * 
 * 
 */
    template <class T>
    int VDinamico<T>::getTamLogico(){
        return tamLogico;
    }
    
     /* @brief Búsqueda binaria si el vector está ordenado
 * @param[in] - Referencia al dato, dos enteros que son la cota a entre los elementos que buscar
 * @param[out] -
 * @return -
 * 
 * 
 */
    template <class T>
    int VDinamico<T>::busquedaBin(T& dato, int inferior, int superior) {
        ordenar();
        if (superior >= inferior) {
            int mid = inferior + (superior - inferior) / 2;

            // Si el elemento está justo en la mitad
            if (v[mid] == dato)
                return mid;

            //Si el elemento es menor, sólo puede estar en la mitad izquierda del vector
            if (v[mid] > dato)
                return busquedaBin(dato, inferior, mid - 1);

            // Si no, sólo puede estar en  la mitad derecha
            return busquedaBin(dato, mid + 1, superior);
        }
        // Sólo llegamos aquí si el elemento no está en el vector
        return -1;
    }
    
     /* @brief Si el tamaño logico llega al tamaño fisico, amplia el vector al doble
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */
    template <class T>    
    void VDinamico<T>::ampliar(){
        if (tamLogico == tamFisico) {
            T *vaux;
            vaux = new T[tamFisico = tamFisico * 2];
            for (int i = 0; i < tamLogico; ++i) {
                vaux[i] = v[i];
            }
            delete [] v;
            v = vaux;
        }
    }
    
      /* @brief Si el tamaño logico es un tercio del fisico, reduce el tamaño del vector a la mitad
 * @param[in] -
 * @param[out] -
 * @return -
 * 
 * 
 */
    template <class T>
    void VDinamico<T>::reducir(){
         if (tamLogico * 3 < tamFisico){
            T *vaux;
            vaux = new T[tamFisico = tamFisico /2];
            for (int i = 0; i < tamLogico; i++){
                vaux[i] = v[i];
            }

            delete [] v;
            v=vaux;
        }
    }

    template <class T>
    bool VDinamico<T>::operator==(const VDinamico<T> &elDeLaDerecha) const{
        int tamA = this->tamLogico;
        int tamB = elDeLaDerecha.tamLogico;
        if (tamA != tamB){
            return false;
        } else {
            for(int i = 0; i < this->tamLogico; ++i){
                T& elemento = v[i];
                T& otro = elDeLaDerecha[i];
                if(elemento != otro){
                    return false;
                }
            }
            return true;
        }
    }

    template <class T>
    bool VDinamico<T>::operator!=(const VDinamico<T> &elDeLaDerecha) const {
        return !(this == elDeLaDerecha);
    }

template <class T>
void VDinamico<T>::print(){
    for(int i = 0; i < tamLogico; ++i){
        std::cout << v[i] << " | ";
    }
    std::cout << std::endl;
}


#endif /* VDINAMICO_H */

