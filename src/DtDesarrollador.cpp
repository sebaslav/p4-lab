#include "../include/DtDesarrollador.h"

using namespace std;

DtDesarrollador::DtDesarrollador(string email, string contrasenia, string empresa): DtUsuario(email, contrasenia){
    this->empresa = empresa;
}

DtDesarrollador::~DtDesarrollador(){}

string DtDesarrollador::getEmpresa() { return empresa; }
