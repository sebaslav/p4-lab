#include <iostream>
#include <string>

#include "../include/TotalHorasJugadas.h"

using namespace std;

TotalHorasJugadas::TotalHorasJugadas() {
    nombre = "TotalHorasJugadas";
    descripcion = "Cantidad total de horas jugadas de un videojuego";
}

DtEstadistica* TotalHorasJugadas::obtenerEstadistica(Videojuego* videojuego) {
    float valor = videojuego->obtenerTotalHorasJugadas();
    return new DtEstadistica(nombre, descripcion, valor);
}

DtEstadistica* TotalHorasJugadas::obtenerDtEstadistica() {
    return new DtEstadistica(nombre, descripcion, -1);
}

TotalHorasJugadas::~TotalHorasJugadas() {}