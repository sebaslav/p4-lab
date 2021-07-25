#include "../include/Jugador.h"
#include <iostream>
#include <string>

using namespace std;

Jugador::Jugador(DtJugador* datos): Usuario(datos->getEmail(), datos->getContrasenia()){
    this->nickname = datos->getNickname();
    this->descripcion = datos->getDescripcion();
}

Jugador::~Jugador(){}

string Jugador::getNickname(){
    return nickname;
}

string Jugador::getDescripcion(){
    return descripcion;
}
