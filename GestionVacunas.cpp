//
// Created by manuel on 28/10/21.
//

#include "GestionVacunas.h"

GestionVacunas::GestionVacunas(ifstream archivoDosis, ifstream archivoUsuarios) {
    int id = 0;
    string palabra;
    int corte = 0;

    int idLote = 0;
    int fabricante = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;

    clock_t t_ini = clock();
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
        Dosis nuevaDosis(id, idLote, fabricante, anno, mes, dia, enAlmacen);
        dosis.insertar(nuevaDosis, dosis.getTamLogico());
    }
    archivoDosis.close();


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


    }

}



Usuario* GestionVacunas::buscarUsuario (string nss){
    Fecha *nueva= new Fecha(1,1,1,1,1);
Usuario *buscando= new Usuario("Dondesta", "eltioeste", nss, *nueva);
Usuario *encontrado= listausuarios.buscaRec(buscando);
}

return encontrado;

}


bool GestionVacunas::queAdministro(Usuario *vacunando) {
    bool labuena;
    int edad= vacunando->getedad();

    if(edad>0 && edad<12)
    return false;
    else {
        nombreFabricante laquetoca=vacunando->getdosisRecomendable();
        labuena= administrarDosis(vacunando,laquetoca);
    return labuena;
    }

}


bool GestionVacunas::administrarDosis(Usuario* vacunando, nombreFabricante vacunada) {
    bool noencontrada = true;


    for (int i = 0; i < dosis.getTamLogico() && noencontrada; ++i) {
        if (dosis[i].GetFabricante() == vacunada && dosis[i].getStatus() == enAlmacen) {
            Dosis* p= &dosis[i];
            vacunando->nuevaDosis(*p);
            dosis[i].setStatus(administrada);
            noencontrada = false;
        }

    }
    if (noencontrada) {
        for (int i = 0; i < dosis.getTamLogico() ; ++i) {

            if (dosis[i].getStatus() == enAlmacen && noencontrada) {
                Dosis* p= &dosis[i];
                vacunando->nuevaDosis(*p);
                dosis[i].setStatus(administrada);
                noRecomendados.insertar(vacunando, noRecomendados.getTamLogico());
                noencontrada=false;
                return false;

            }

        }
    }
    return true;
}

float GestionVacunas::pautaCompleta() {
float  numusuarios=this->listausuarios.getNumElementos();
float numpautascompletas;
VDinamico<Usuario*> tosellos= listausuarios.recorreInorden();

    for(int i=0; i<tosellos.getTamLogico(); i++){

        if(tosellos[i]->getedad()>=75 && tosellos[i]->getmisdosis().getTamLogico()==3)
            numpautascompletas;
        if(tosellos[i]->getedad()<75 && tosellos[i]->getmisdosis().getTamLogico()==2){
            numpautascompletas++;
        }
    }
    numpautascompletas= (numpautascompletas/numusuarios)*100;
    return numpautascompletas;
}


VDinamico<Usuario*> GestionVacunas::listadoVacunacionNR(){
    return noRecomendados;

}


GestionVacunas::~GestionVacunas() {

}
