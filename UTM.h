//
// Created by Manuel Jesús Romero Mateos on 8/11/21.
//

#ifndef INC_2021_EEDD_PRACTICAS_UTM_H
#define INC_2021_EEDD_PRACTICAS_UTM_H

#include<cmath>

struct UTM {
    double latitud;
    double longitud;

    UTM(double _lat = 0.0, double _long = 0.0) : latitud(_lat), longitud(_long) {
    }

    double distancia(const UTM &utm) {
        double x = pow(utm.latitud - this->latitud, 2);
        double y = pow(utm.longitud - this->longitud, 2);
        double distancia = sqrt(x + y);
        return distancia;
    }

    double getLatitud() const {
        return latitud;
    }

    void setLatitud(double latitud) {
        this->latitud = latitud;
    }

    double getLongitud() const {
        return longitud;
    }

    void setLongitud(double longitud) {
        this->longitud = longitud;
    }
};

#endif //INC_2021_EEDD_PRACTICAS_UTM_H
