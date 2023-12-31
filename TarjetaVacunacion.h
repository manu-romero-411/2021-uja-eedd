//
// Created by Manuel Jesús Romero Mateos on 18/11/21.
//

#ifndef INC_2021_EEDD_PRACTICAS_TARJETAVACUNACION_H
#define INC_2021_EEDD_PRACTICAS_TARJETAVACUNACION_H

#include <cstdlib>
#include <string>
#include "Dosis.h"
#include "Usuario.h"

class TarjetaVacunacion {
private:
    std::string id;
    bool pautaCompleta;
    int idCentroCercano;
    bool pautaRecomendada;
    Usuario* propietario;
    vector<Dosis*> dosisAdministradas;
public:
    TarjetaVacunacion();
    TarjetaVacunacion(Usuario* _usuario);
    Dosis& getDosis(int cual);
    void nuevaDosis(Dosis* nueva);
    vector<Dosis*> getDosisAdministradas();
    nombreFabricante getFabricanteRecomendado(int criterio);
    bool isDosisRec();
    void tieneDosisRec(bool rec);
    int dosisPorAdministrar();
    int dosisPorAdministrar2();
    int dosisPorAdministrar3();

    virtual ~TarjetaVacunacion();

    Usuario& getPropietario();
    const string &getId() const;
    const double getX();
    const double getY();
    void setId(const string &id);
    bool isPautaCompleta() const;
    void setPautaCompleta(bool pautaCompleta);
    int getIdCentroCercano() const;
    void setIdCentroCercano(int idCentroCercano);
    bool isPautaRecomendada() const;
    void setPautaRecomendada(bool pautaRecomendada);
    const vector<Dosis *> &getDosisAdministradas() const;
    void isCompleta();


    string pasaporteCovidCode(bool &valido);
    bool operator==(const TarjetaVacunacion& ladeladerecha );
    std::string getNombreFabricanteDado(nombreFabricante fab);
};


#endif //INC_2021_EEDD_PRACTICAS_TARJETAVACUNACION_H
