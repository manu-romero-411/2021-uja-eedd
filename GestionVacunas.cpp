//
// Created by manuel on 28/10/21.
//

#include <algorithm>
#include "GestionVacunas.h"
#include <float.h>

/**
* @brief Constructor parametrizado
* @param[in] String con los nombres de los ficheros de las dosis, usuarios y centros
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
    float longitudMayor = INT32_MIN;
    float latitudMayor = INT32_MIN;
    float longitudMenor = UINT_MAX;
    float latitudMenor = UINT_MAX;

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
        if (latitud < latitudMenor) latitudMenor = latitud;
        if (longitud < longitudMenor) longitudMenor = longitud;
        if (latitud > latitudMayor) latitudMayor = latitud;
        if (longitud > longitudMayor) longitudMayor = longitud;

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
    malla = new MallaRegular<TarjetaVacunacion*>(longitudMenor, latitudMenor, longitudMayor, latitudMayor, 20, 20); // hemos calculado que así la media de elementos por celda es 25
    generaTarjetas();
    //vector<TarjetaVacunacion*> vec = malla->buscarRadio(38, -3, 0.3);
    //cout << "Num elementos por cada link hembra: " << malla->mediaElementosPorCelda() << endl;
}

void GestionVacunas::generaTarjetas(){
    int i = 0;
    for(std::map<string,Usuario*>::iterator it = listaUsuarios.begin(); it != listaUsuarios.end(); ++it){
        Usuario* elquetoca = it->second;

        TarjetaVacunacion *nueva = new TarjetaVacunacion(elquetoca);
        //tablaTarjetas.insert(pair<string,TarjetaVacunacion*>(nueva->getId(), nueva));
        malla->insertar(nueva->getPropietario().getDomicilio().latitud,nueva->getPropietario().getDomicilio().longitud,nueva);
    }
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

Usuario* GestionVacunas::buscarUsuario (TarjetaVacunacion* tarjeta){
    // POTENCIAL PROBLEMA CON PUNTEROS
    TarjetaVacunacion* encontrado = *malla->buscar(tarjeta->getPropietario().getDomicilio().getLatitud(),
                                        tarjeta->getPropietario().getDomicilio().getLongitud(),
                                        tarjeta);
    Usuario* usuario = &encontrado->getPropietario();
    return usuario;
}

/*TarjetaVacunacion* GestionVacunas::buscarTarjeta (Usuario* us){
    TarjetaVacunacion* encontrado = *malla.buscar(us->getDomicilio().getLatitud(),
                                                  us->getDomicilio().getLongitud(),
                                                  tarjeta);

}*/

/**
* @brief Funcion que calcula el porcentaje de personas con pauta completa
* @param[in]
* @param[out] -
* @return Porcentaje de las personas con la pauta completa
*/

float GestionVacunas::pautaCompleta() {
    float numusuarios=this->listaUsuarios.size();
    float numpautascompletas;
    for(std::map<string,TarjetaVacunacion*>::iterator it = tablaTarjetas.begin(); it != tablaTarjetas.end(); ++it) {
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
    for(std::map<string,TarjetaVacunacion*>::iterator it = tablaTarjetas.begin(); it != tablaTarjetas.end(); ++it) {
        if(!it->second->isDosisRec()){
            Usuario* nuevo = &(it->second->getPropietario());
            vectorDevuelto.push_back(nuevo);
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

/**
* @brief Suministra un numero de dosis a un centro
* @param[in] Puntero al centro que recibe las dosis, numero de vacunas a recibir
* @param[out] -
* @return -
*
*
*/
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

const map<string,Usuario*> GestionVacunas::getListaUsuarios() const {
    return listaUsuarios;
}

const vector<Dosis*> GestionVacunas::getListaDosis() const {
    return listaDosis;
}
/**
* @brief Devuelve el vector con los centros
* @param[in]
* @param[out] -
* @return -
*
*
*/
vector<CentroVacunacion*> GestionVacunas::getCentros(){
    return listaCentros;
}
/**
* @brief Devuelve el numero de vacunas de un fabricante
* @param[in] Fabricante a comprobar
* @param[out] -
* @return -
*
*
*/
int GestionVacunas::numTotalVacunasTipo(nombreFabricante fabricante){
    return numVacTipo[fabricante];
}

vector<int> GestionVacunas::getContadoresVacunasTipo(){
    return numVacTipo;
}
/**
* @brief Decrementa el numero de vacunas de un fabricante en el vector
* @param[in]
* @param[out] -
* @return -
*
*
*/
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
    for(int i=0; i<listaCentros.size();i++){
        delete listaCentros[i];
    }
}
/**
* @brief Devuelve el centro mas cercano a un usuario
* @param[in]
* @param[out] -
* @return -
*
*
*/
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
/**
* @brief Devuelve el estado de todas las dosis, 0 si está administrada, 1 si está en el almacén
* @param[in]
* @param[out] -
* @return -
*
*
*/
void GestionVacunas::print(){
    for (int i = 0; i < listaDosis.size(); ++i){
        cout << listaDosis[i]->getStatus() << " | " ;
    }
    cout << endl;
}
/**
* @brief Devuelve un string de un enum de fabricante
* @param[in]
* @param[out] -
* @return -
*
*
*/
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
        default:
            return "ninguna";
            break;
    }
}

map<string,TarjetaVacunacion*> GestionVacunas::getListaTarjetas()  {
    return tablaTarjetas;
}

const vector<Dosis*> GestionVacunas::getDosis() const {
    return listaDosis;
}


void GestionVacunas::generarMapaMalla(){
    /*RGBColor blanco (255,255,255);

    Img img(1300, 700, blanco);

    int nfilas = img.numFilas();
    int ncol = img.numColumnas();

    cout << "Imagen creada con " << nfilas << "filas y " << ncol << " columnas." <<endl;

    int r = 0; // azul
    int g = 0;
    int b = 255;

    // sabemos el tamaño de la caja envolvente de los datos, pero volver a calcular

    double minlat = malla.getYMin();
    double maxlat = malla.getYMax();
    double minlon = malla.getXMin();
    double maxlon = malla.getXMax();

    // Calculamos el número de pixeles asociados a un grado

    cout << "lat: xmin = " << minlat <<  ", " << "xmax = " << maxlat << endl;
    cout << "lon: ymin = " << minlon <<  ", " << "ymax = " << maxlon << endl;

    double rangox = maxlat - minlat;
    double rangoy = maxlon - minlon;

    cout << "rango x = " << rangox << endl;
    cout << "rango y = " << rangoy << endl;

    cout << "nfilas = " << nfilas << endl;
    cout << "ncol = " << ncol << endl;

    double pixelPorGradoX = (double) (nfilas - 1) / rangox;
    double pixelPorGradoY = (double) (ncol - 1) / rangoy;


    cout << "Pixel por Grado X = " << pixelPorGradoX << endl;
    cout << "Pixel por Grado Y = " << pixelPorGradoY << endl;


    // elegimos las coordenada de un recuadro cualquiera

    double lat1 = 40;
    double lon1 = -8;

    double lat2 = 42.0;
    double lon2 = -5.0;

    img.pintarRecuadro((lat1 - minlat) * pixelPorGradoX, ncol - 1 - ((lon1 - minlon) * pixelPorGradoY),
                       (lat2 - minlat) * pixelPorGradoX, ncol - 1 - ((lon2 - minlon) * pixelPorGradoY), 255, 0, 0);


    // ejemplo de punto que debe estar por el centro, lo pintamos acto seguido

    double vlat = 39.569748;
    double vlon = -3.002585;

    int posX = (vlat - minlat) * pixelPorGradoX;
    int posY = ncol - 1 - ((vlon -minlon) * pixelPorGradoY);
    img.pintarPixelGrande(posX,posY,r,g,b);
    //img.pintarPixel(posX,posY,r,g,b);


    try {
        img.guardar("./mapaUsaResult.ppm");
    }
    catch(ErrorEscrituraFichero &e) {
        cout << "Error al escribir fichero" << endl;
    }

    cout << "Operación realizada con exito, ahora visualizarlo con cualquier visor de imágenes" << endl;*/
}