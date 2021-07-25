#include "../include/DtJugador.h"

using namespace std;

DtJugador::DtJugador(string email, string contrasenia, string nickname, string descripcion): DtUsuario(email, contrasenia){
    this->nickname = nickname;
    this->descripcion = descripcion;
}
DtJugador::~DtJugador(){}

string DtJugador::getNickname() { return nickname; }

string DtJugador::getDescripcion() { return descripcion; }
