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
#define UINT_MAX   4294967295U

#include <algorithm>
#include <math.h>
#include <stdexcept>
#include "Dosis.h"


template <class T>
class VDinamico {
private:
    int tamFisico;
    int tamLogico;
    T *v;
    bool ordenado;
public:
    VDinamico();
    virtual ~VDinamico();
    VDinamico<T>(unsigned int tamNue);
    VDinamico<T>(const VDinamico<T>& orig);
    VDinamico<T>(const VDinamico<T>& orig, unsigned int desde, unsigned int num);
    VDinamico<T>& operator=(VDinamico<T>& comp);
    T& operator[](const int pos) const;
    void insertar(const T& dato, unsigned int pos = UINT_MAX);
    T borrar( unsigned int pos = UINT_MAX);
    void ordenar() ;
    void ordenarRev() ;
    T* leer(unsigned pos);
    int getTamLogico();
    int busquedaBin(T& dato, int inferior, int superior);
    void ampliar();
    void reducir();
    void setOrdenado(bool ordenado);
    bool isOrdenado() const;
};

template <class T>
    VDinamico<T>::VDinamico() {
        tamFisico = 1;
        tamLogico = 0;
        v = new T[tamFisico];
        ordenado = false;
    }

    template <class T>
    VDinamico<T>::VDinamico(unsigned int tamNue) {
        tamLogico = 0;
        double tam_potencia = log2f(tamNue);
        int tam_potencia_entera = (int)tam_potencia; // El tamaño que hemos pasado es 2^tam_potencia, pero es un valor no entero. Lo casteamos para trabajar con enteros.
        tamNue = powf(2,(tam_potencia_entera+1)); // potencia de 2 inmediatamente superior a tamNue
        v = new T[tamFisico = tamNue];
        ordenado = false;
    }
    
    template <class T>
    VDinamico<T>::VDinamico(const VDinamico<T>& orig) {
        //Constructor de copia
        tamLogico = orig.tamLogico;
        tamFisico = orig.tamFisico;

        v = new T[tamFisico];
        for(int i = 0; i < tamLogico; ++i){
            v[i] = orig.v[i];
        }
        ordenado = false;
    }

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
        ordenado = false;
    }
    
    template <class T>
    VDinamico<T>& VDinamico<T>::operator=(VDinamico<T>& comp) {
        tamFisico = comp.tamFisico;
        tamLogico = comp.tamLogico;

        v = new T[tamFisico];
        for (int i = 0; i < tamLogico; i++) {
            v[i] = comp.v[i];
        }
        delete [] v;
        return *this;
    }
    
    template<class T>
    T& VDinamico<T>::operator[](const int pos) const{
        if (pos > tamLogico) throw std::out_of_range("[ operator[] ] Posición no valida al usar el operador []");
        return v[pos];
    }
    
    template<class T>
    void VDinamico<T>::insertar(const T& dato, unsigned int pos) {
        if (pos > tamLogico) throw std::out_of_range("[insertar] Posicion no valida");

        ampliar();

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
        ordenado = false;
    }

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

        reducir();
    }
    
    template<class T>
    void VDinamico<T>::ordenar()  {
        std::sort(v, v + tamLogico);
        ordenado = true;
    }
    
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

    template <class T>
    VDinamico<T>::~VDinamico() {
        delete [] v;
    }

    /**
     * @brief Devuelve el dato almacenado en la posición dada por el parámetro.
     */
    template <class T>
    T* VDinamico<T>::leer(unsigned pos){
        return &v[pos];
    }
    
    template <class T>
    int VDinamico<T>::getTamLogico(){
        return tamLogico;
    }
    
    template <class T>
    int VDinamico<T>::busquedaBin(T& dato, int inferior, int superior) {
        if (!ordenado) ordenar();
        if (superior >= inferior) {
            int mid = inferior + (superior - inferior) / 2;

            // If the element is present at the middle
            // itself
            if (v[mid] == dato)
                return mid;

            // If element is smaller than mid, then
            // it can only be present in left subarray
            if (v[mid] > dato)
                return busquedaBin(dato, inferior, mid - 1);

            // Else the element can only be present
            // in right subarray
            return busquedaBin(dato, mid + 1, superior);
        }
        // We reach here when element is not
        // present in array
        return -1;
    }
    
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
    void VDinamico<T>::setOrdenado(bool ordenado) {
        this->ordenado = ordenado;
    }

    template <class T>
    bool VDinamico<T>::isOrdenado() const {
        return ordenado;
    }

#endif /* VDINAMICO_H */

