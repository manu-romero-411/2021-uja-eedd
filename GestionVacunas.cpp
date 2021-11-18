//
// Created by manuel on 28/10/21.
//

#include <algorithm>
#include "GestionVacunas.h"
#include <float.h>


/**
* @brief Constructor parametrizado
* @param[in] String con los nombres de los ficheros de las listaDosis y ususarios
* @param[out] -
* @return -
*
*
*/
GestionVacunas::GestionVacunas(std::string fileDosis, std::string fileUsuarios, std::string fileCentros) {
    cuantasDosis = 0;
    cuantosUsuarios = 0;
    lecturaVacunas = 0;
    ifstream archivoDosis(fileDosis);
    int id = 0;
    string palabra;
    int corte = 0;

    int idLote = 0;
    int fabricante = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;
    while (getline(archivoDosis, palabra)) {
        corte = palabra.find(';');
        id = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        idLote = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find(';');
        fabricante = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        dia = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        corte = palabra.find('/');
        mes = stoi(palabra.substr(0, corte));
        palabra.erase(0, corte + 1);

        anno = stoi(palabra);
        Dosis* nuevaDosis = new Dosis(id, idLote, fabricante, dia, mes, anno);
        listaDosis.insert(listaDosis.begin(), nuevaDosis);
    }
    archivoDosis.close();

    for (int k = 0; k < 4; ++k){
        numVacTipo.push_back(0);
    }

    vacAlmacen = 0;
    for (int i = 0; i < listaDosis.size(); ++i) {
        Dosis *p = listaDosis[i];
        p->setStatus(enAlmacen);
        vacAlmacen++;
        cuantasDosis++;
        numVacTipo[p->getFabricante()]++;
    }

    ifstream archivoUsuarios(fileUsuarios);
    string palabraB;
    corte = 0;
    dia = 0;
    mes = 0;
    anno = 0;
    float longitud, latitud;
    string nombre, apellido, nss;
    while (getline(archivoUsuarios, palabraB)) {
        corte = palabraB.find(';');
        nombre = palabraB.substr(0, corte);
        palabraB.erase(0, corte + 1);

        corte = palabraB.find(';');
        apellido = palabraB.substr(0, corte);
        palabraB.erase(0, corte + 1);

        corte = palabraB.find(';');
        nss = palabraB.substr(0, corte);
        palabraB.erase(0, corte + 1);

        corte = palabraB.find('/');
        dia = stoi(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        corte = palabraB.find('/');
        mes = stoi(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        corte = palabraB.find(';');
        anno = stoi(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        corte = palabraB.find(';');
        longitud = stof(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        latitud = stof(palabraB);
        Fecha fecha;
        fecha.asignarDia(dia, mes, anno);
        UTM ubic(longitud,latitud);
        Usuario* nuevoUsuario = new Usuario(nombre, apellido, nss, fecha, ubic);
        listaUsuarios.insert(pair<string, Usuario*>(nss, nuevoUsuario));
        cuantosUsuarios++;
    }
    archivoUsuarios.close();

    int nuevaId = 0;
    float nuevalatitud = 0.0;
    float nuevalongitud = 0.0;
    ifstream archivoCentros(fileCentros);
    std::string palabraC;
    int contcentro = 0;
    while (getline(archivoCentros, palabraC)) {
        corte = palabraC.find(';');
        nuevaId = stoi(palabraC.substr(0, corte));
        palabraC.erase(0, corte + 1);

        corte = palabraC.find(';');
        nuevalatitud = stof(palabraC.substr(0, corte));
        palabraC.erase(0, corte + 1);

        nuevalongitud = stof(palabraC);

        UTM ubicacionCentro(nuevalatitud, nuevalongitud);
        CentroVacunacion* nuevoCentro = new CentroVacunacion(this, contcentro, ubicacionCentro);

        listaCentros.push_back(nuevoCentro);
        contcentro++;
    }

    cout << "" << endl;
}
/**
* @brief Busca un usuario dependiendo de su nss
* @param[in] string con el nss del usuario
* @param[out] -
* @return Puntero al ususario encontrado dentro del arbol
*
*
*/
Usuario* GestionVacunas::buscarUsuario (string nss){
    Usuario *encontrado= (listaUsuarios.find(nss)->second);
    return encontrado;
}

/**
* @brief Funcion que calcula el porcentaje de personas con pauta completa
* @param[in]
* @param[out] -
* @return Porcentaje de las personas con la pauta completa
*/

float GestionVacunas::pautaCompleta() {
    float numusuarios=this->listaUsuarios.size();
    float numpautascompletas;
    for(std::map<string,Usuario*>::iterator it = listaUsuarios.begin(); it != listaUsuarios.end(); ++it) {
        if (it->second->dosisPorAdministrar() == 0){
            numpautascompletas++;
        }
    }
    float porcentaje = (numpautascompletas/numusuarios)*100;
    return porcentaje;
}

/**
* @brief Devuelve el estado de las listaDosis
* @param[in]
* @param[out] -
* @return -
*
*
*/
void GestionVacunas::printStatus(){
    for (int i = 0; i < listaDosis.size(); ++i){
        std::cout << listaDosis[i]->getStatus() << " | ";
    }
}

/**
* @brief Devuelve la lista de los usuarios con la pauta no recomenda
* @param[in]
* @param[out] -
* @return -
*
*
*/

vector<Usuario*> GestionVacunas::listadoVacunacionNR(){
    vector<Usuario*> vectorDevuelto;
    for(std::map<string,Usuario*>::iterator it = listaUsuarios.begin(); it != listaUsuarios.end(); ++it)  {
        if(!it->second->isDosisRec()){
            vectorDevuelto.push_back(it->second);
        }
    }
}


/**
* @brief Devuelve un vector con los nss de los usuarios del arbol
* @param[in]
* @param[out] -
* @return -
*
*
*/

vector<string> GestionVacunas::listadoNSS(){
    vector<string> resultado;
    for(std::map<string,Usuario*>::iterator it = listaUsuarios.begin(); it != listaUsuarios.end(); ++it) {

        resultado.push_back(it->second->getNss());
    }
    std::sort(resultado.begin(),resultado.end());
    return resultado;
}

void GestionVacunas::suministrarNdosisCentro(CentroVacunacion* centro, int numerovacunas) {
    vector<Dosis*> auxiliar;
    int cont = 0;
    for(int i = 0; cont < numerovacunas; i++) {
        Dosis *p = listaDosis[lecturaVacunas];
        auxiliar.push_back(p);
        lecturaVacunas++;
        cont++;
    }
    centro->anadirNDosisAlmacen(auxiliar);
}

int GestionVacunas::getVacAlmacen() const {
    return vacAlmacen;
}

void GestionVacunas::setVacAlmacen(int vacAlmacen) {
    GestionVacunas::vacAlmacen = vacAlmacen;
}

const map<string,Usuario*> GestionVacunas::getListausuarios() const {
    return listaUsuarios;
}

const vector<Dosis*> GestionVacunas::getDosis() const {
    return listaDosis;
}

vector<CentroVacunacion*> GestionVacunas::getCentros(){
    return listaCentros;
}

int GestionVacunas::numTotalVacunasTipo(nombreFabricante fabricante){
    return numVacTipo[fabricante];
}

vector<int> GestionVacunas::getContadoresVacunasTipo(){
    return numVacTipo;
}

void GestionVacunas::sustraerDosisDisponiblesDeContador(nombreFabricante fab){
    numVacTipo[fab]--;
}

/**
* @brief Destructor por defecto
* @param[in]
* @param[out] -
* @return -
*
*
*/
GestionVacunas::~GestionVacunas() {

}

CentroVacunacion* GestionVacunas::centroMasCercano(Usuario* usuario){
    double distancia = DBL_MAX;
    int centroCercano = -1;
    for(int i = 0; i < listaCentros.size(); ++i){
        double centroDist = listaCentros[i]->getUbicacion().distancia(usuario->getDomicilio());
        if(centroDist < distancia){
            centroCercano = i;
            distancia = centroDist;
        }
    }
    return listaCentros[centroCercano];
}

void GestionVacunas::print(){
    for (int i = 0; i < listaDosis.size(); ++i){
        cout << listaDosis[i]->getStatus() << " | " ;
    }
    cout << endl;
}

std::string GestionVacunas::getNombreFabricanteDado(nombreFabricante fab){
    switch(fab) {
        case (0):
            return "Pfizer";
            break;
        case (1):
            return "Moderna";
            break;
        case (2):
            return "AstraZeneca";
            break;
        case (3):
            return "Johnson";
            break;
    }
}
