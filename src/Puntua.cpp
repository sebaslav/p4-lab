#include <string>

#include "../include/Puntua.h"
#include "../include/ControladorUsuarios.h"

using namespace std;

Puntua::Puntua(int puntaje) {
    this->puntaje = puntaje;
    ControladorUsuarios* cu = ControladorUsuarios::getInstance();
    jugador = cu->getJugadorLogueado();
}

string Puntua::getNickname() {
    return jugador->getNickname();
}

int Puntua::getPuntaje() {
    return puntaje;
}

void Puntua::setPuntaje(int puntaje) {
    this->puntaje = puntaje;
}

