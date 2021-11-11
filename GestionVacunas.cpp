//
// Created by manuel on 28/10/21.
//

#include "GestionVacunas.h"


/**
* @brief Constructor parametrizado
* @param[in] String con los nombres de los ficheros de las dosis y ususarios
* @param[out] -
* @return -
*
*
*/
GestionVacunas::GestionVacunas(std::string fileDosis, std::string fileUsuarios) {
    cuantasDosis = 0;
    cuantosUsuarios = 0;
    primeraDosis = 0;
    segundaDosis = 0;
    terceraDosis = 0;
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
        Dosis nuevaDosis(id, idLote, fabricante, dia, mes, anno);
        dosis.insertar(nuevaDosis, dosis.getTamLogico());
    }
    archivoDosis.close();
    vacAlmacen=0;
    for (int i = 0; i < dosis.getTamLogico(); ++i){
        dosis[i].setStatus(enAlmacen);
        vacAlmacen++;
        cuantasDosis++;
    }

    ifstream archivoUsuarios(fileUsuarios);
    string palabraB;
    corte = 0;
    dia = 0;
    mes = 0;
    anno = 0;
    float longitud, latitud;
    string nombre, apellido, nss;
    AVL<Usuario> listaUsuarios;
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
        longitud = stoi(palabraB.substr(0, corte));
        palabraB.erase(0, corte + 1);

        latitud = stoi(palabraB);
        Fecha fecha;
        fecha.asignarDia(dia, mes, anno);
        Usuario nuevoUsuario(nombre, apellido, nss, fecha);
        listausuarios.inserta(nuevoUsuario);
        cuantosUsuarios++;
    }
    archivoUsuarios.close();
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
    Fecha *nueva= new Fecha(1,1,1,1,1);
    Usuario *buscando= new Usuario("Dondesta", "eltioeste", nss, *nueva);
    Usuario *encontrado= listausuarios.buscaRec(*buscando);
    return encontrado;
}
/**
* @brief Funcion que consigue la dosis recomendable y llama a adiministrarDosis
* @param[in] Un usuario
* @param[out] -
* @return - Bool dependiendo si la vacunación es la recomendada
*
*
*/
bool GestionVacunas::queAdministro(Usuario *vacunando) {
    bool labuena;
    int edad = vacunando->getedad();

    if(!noMenor(vacunando)) return false;
    else {
        nombreFabricante laquetoca = vacunando->getdosisRecomendable();
        labuena = administrarDosis(vacunando,laquetoca);
        return labuena;
    }
}

/**
* @brief Funcion que administra una dosis a un usuario específico
* @param[in] Usuario a vacunar, y fabricante de la vacuna
* @param[out] -
* @return -Bool dependiendo si la vacunación es la recomendada
*
*
*/
bool GestionVacunas::administrarDosis(Usuario* vacunando, nombreFabricante vacunada) {
    if(!this->dosis.getTamLogico() || (this->vacAlmacen == 0))
        throw std::underflow_error("[ERROR] No hay dosis disponibles");

    int fabricanteBuscado;
    try {
        fabricanteBuscado = vacunando->getdosisRecomendable();
    } catch (std::invalid_argument &e){
        return false;
    }

    bool encontrada = false;
    bool noRecomendadaEncontrada = false;
    Dosis* dosisNR = nullptr;
    for(int i=0; i < this->dosis.getTamLogico() && !encontrada; i++){
        if((this->dosis[i].GetFabricante() == fabricanteBuscado) && (this->dosis[i].getStatus() == enAlmacen)){
            vacunando->nuevaDosis(dosis[i]);
            vacAlmacen--;
            return true;
        } else {
            if((this->dosis[i].getStatus() == administrada) && !noRecomendadaEncontrada){
                noRecomendadaEncontrada = true;
                dosisNR = &this->dosis[i];
                dosis[i].setStatus(administrada);

                break;
            }
        }
    }
    vacunando->nuevaDosis(*dosisNR);
    vacAlmacen--;
    return false;
}
/**
* @brief Funcion que calcula el porcentaje de personas con pauta completa
* @param[in]
* @param[out] -
* @return Porcentaje de las personas con la pauta completa
*
*
*/
float GestionVacunas::pautaCompleta() {
    float numusuarios=this->listausuarios.getNumElementos();
    float numpautascompletas;
    VDinamico<Usuario*> tosellos= listausuarios.recorreInorden();
    for(int i=0; i<tosellos.getTamLogico(); i++){
        if(tosellos[i]->getedad()>=75 && tosellos[i]->getmisdosis().getTamLogico()==3)
            numpautascompletas++;
        if(tosellos[i]->getedad()<75 && tosellos[i]->getmisdosis().getTamLogico()==2){
            numpautascompletas++;
        }
    }
    float porcentaje = (numpautascompletas/numusuarios)*100;
    return porcentaje;
}

/**
* @brief Devuelve el estado de las dosis
* @param[in]
* @param[out] -
* @return -
*
*
*/
void GestionVacunas::printStatus(){
    for (int i = 0; i < dosis.getTamLogico(); ++i){
        std::cout << dosis[i].getStatus() << " | ";
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
VDinamico<Usuario*> GestionVacunas::listadoVacunacionNR(){
    return noRecomendados;
}

/**
* @brief Devuelve un vector con los nss de los usuarios del arbol
* @param[in]
* @param[out] -
* @return -
*
*
*/
VDinamico<string> GestionVacunas::listadoNSS(){
    VDinamico<string> resultado;
    VDinamico<Usuario*> listUsu = listausuarios.recorreInorden();
    for(int i = 0; i < listUsu.getTamLogico(); ++i){
        resultado.insertar(listUsu[i]->getNss(),resultado.getTamLogico());
    }
    resultado.ordenar();
    return resultado;
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

int GestionVacunas::getVacAlmacen() const {
    return vacAlmacen;
}

void GestionVacunas::setVacAlmacen(int vacAlmacen) {
    GestionVacunas::vacAlmacen = vacAlmacen;
}

const AVL<Usuario> &GestionVacunas::getListausuarios() const {
    return listausuarios;
}

const VDinamico<Dosis> &GestionVacunas::getDosis() const {
    return dosis;
}

int GestionVacunas::getPrimeraDosis() const {
    return primeraDosis;
}

void GestionVacunas::setPrimeraDosis() {
    primeraDosis++;
}

int GestionVacunas::getSegundaDosis() const {
    return segundaDosis;
}

void GestionVacunas::setSegundaDosis() {
    segundaDosis++;
}

int GestionVacunas::getTerceraDosis() const {
    return terceraDosis;
}

void GestionVacunas::setTerceraDosis() {
    terceraDosis++;
}

bool GestionVacunas::noMenor(Usuario* vacunando){
    if(vacunando->getedad() > 0 && vacunando->getedad() < 12) return false;
    else return true;
}
