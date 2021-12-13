
//
//  Created by Antonio Rueda y Lidia Ortega 
//



#ifndef PPM_IMG_H
#define PPM_IMG_H

#include <string>
#include <iostream>

using namespace std;

/** Error al abrir un fichero para lectura */
class ErrorLecturaFichero {};
/** Formato incorrecto (no es una imagen PPM) */
class ErrorFormatoFichero {};
/** Error al abrir un fichero para escritura */
class ErrorEscrituraFichero {};

/** Color con tres componentes: rojo, verde, negro codificadas en 3 bytes */
class RGBColor {
    unsigned char r, g, b;
    
public:
    /** Iniciar a negro */
    RGBColor() { r = g = b = 0; }
    
    /** Iniciar al color indicado */
    RGBColor(unsigned char r, unsigned char g, unsigned char b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    /** Indica si ambos colores son iguales */
    bool operator==(RGBColor &color) {
        return color.r == r && color.g == g && color.b == b;
    }
    
    /** Indica si se trata de distinto colores */
    bool operator!=(RGBColor &color) {
        return !(*this == color);
    }
        
    /** Obtener componente rojo */
    unsigned char rojo() const { return r; }
    /** Obtener componente verde */
    unsigned char verde() const { return g; }
    /** Obtener componente azul */
    unsigned char azul() const { return b; }
    /** Operador de salida a stream */
};

ostream &operator<<(ostream &os, const RGBColor &color) {
    os << "(" << (int)color.rojo() << ", " << (int)color.verde() << ", " << (int)color.azul() << ")";
    return os;
}

/** Clase para leer imágenes en formato PPM */
class Img {
    /** Pixels codificados en rgb */
    RGBColor *pixels;
    /** Tamaño de la imagen */
    int filas, columnas;
    
public:
    Img(int filas, int columnas) {
        this->filas = filas;
        this->columnas = columnas;
        pixels = new RGBColor[filas * columnas];
    }


    Img(int filas, int columnas, RGBColor &color) {
        this->filas = filas;
        this->columnas = columnas;
        pixels = new RGBColor[filas * columnas];
        for (int i= 0; i< filas*columnas; i++) pixels[i]= color;
    }

    Img(const string &fileName) {
        ifstream f(fileName.c_str(), ios::binary);

        if (!f) throw ErrorLecturaFichero();

        string tmp;
        stringstream stmp;

        // Leer cabecera
        getline(f, tmp);
        if (tmp != "P6") throw ErrorFormatoFichero();

        // Leer descripción programa generador
        getline(f, tmp);

        // Leer número de filas
        f >> tmp;
        stmp.str(tmp);
        if (!(stmp >> filas)) throw ErrorFormatoFichero();

        // Leer número de columnas
        f >> tmp;
        stmp.clear();
        stmp.str(tmp);
        if (!(stmp >> columnas)) throw ErrorFormatoFichero();
        getline(f, tmp);

        // Leer rango de color
        int tamColor;
        f >> tmp;
        stmp.clear();
        stmp.str(tmp);
        if (!(stmp >> tamColor) || (tamColor != 255)) throw ErrorFormatoFichero();
        getline(f, tmp);

        // Leer pixels
        int numPixels;
        pixels = new RGBColor[numPixels = filas * columnas];
        RGBColor *auxPixel = pixels;
        unsigned char rgb[3];

        while (numPixels--) {
            if (f.read((char *)rgb, 3)) throw ErrorFormatoFichero();
            *(auxPixel++) = RGBColor(rgb[0], rgb[1], rgb[2]);
        }
    }

    void guardar(const string &fileName) {
        ofstream f(fileName.c_str(), ios::binary);

        if (!f) throw ErrorEscrituraFichero();

        f << "P6" << endl;
        f << "# Generada por clase Img" << endl;
        f << filas << " " << columnas << endl;
        f << 255 << endl;

        int numPixels = filas * columnas;
        RGBColor *auxPixel = pixels;
        unsigned char rgb[3];

        while (numPixels--) {
            rgb[0] = auxPixel->rojo();
            rgb[1] = auxPixel->verde();
            rgb[2] = auxPixel->azul();
            if (f.write((char *)rgb, 3)) throw ErrorEscrituraFichero();
            ++auxPixel;
        }
    }

    void pintarRecuadro (int xmin, int ymin, int xmax, int ymax, int r, int g, int b){
        if (xmin > xmax) swap (xmin, ymax);
        if (ymin > ymax) swap (ymin, ymax);

        for (int i = xmin; i < xmax; ++i) {
            pintarPixel(i, ymin, r, g, b);
            pintarPixel(i, ymax - 1, r, g, b);
        }

        for (int i = ymin; i < ymax; ++i) {
            pintarPixel(xmin, i, r, g, b);
            pintarPixel(xmax - 1, i, r, g, b);
        }
    }

    /** Acceder al color situado en la posición (x, y) */
    RGBColor &pixel(int x, int y) { return pixels[y * filas + x]; }
    void pintarPixel(int x, int y, char r, char g, char b) {
    	RGBColor color(r,g,b);
    	pixels[y * filas + x] = color;
    }
    
    /** Pinta un punto grande en las coordenadas (x,y) en la imagen */
    void pintarPixelGrande(int x, int y, char r, char g, char b) {
   		pintarPixel (x,y,r,g,b);
   		pintarPixel (x,y+1,r,g,b);
   		pintarPixel (x+1,y,r,g,b);
   		pintarPixel (x+1,y+1,r,g,b);    
    }

	/** Pinta un recuadro con las coordenadas de las esquinas indicadas */

    /** Guardar la imagen en un fichero PPM */

    /** Numero de filas */
    int numFilas() { return filas; }
    /** Numero de columnas */
    int numColumnas() { return columnas; }
    /** Pinta un recuadro de color azul en la imagen **/
};

#endif

