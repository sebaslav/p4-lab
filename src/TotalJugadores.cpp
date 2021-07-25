#include <iostream>
#include <string>

#include "../include/TotalJugadores.h"

using namespace std;

TotalJugadores::TotalJugadores() {
    nombre = "TotalJugadores";
    descripcion = "Cantidad total de jugadores que se han suscrito a un videojuego";
}

DtEstadistica* TotalJugadores::obtenerEstadistica(Videojuego* videojuego) {
    float valor = videojuego->obtenerTotalJugadores();
    return new DtEstadistica(nombre, descripcion, valor);
}

DtEstadistica* TotalJugadores::obtenerDtEstadistica() {
    return new DtEstadistica(nombre, descripcion, -1);
}

TotalJugadores::~TotalJugadores() {}