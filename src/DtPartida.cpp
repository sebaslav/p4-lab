#include <iostream>
#include <string>
#include <cstdlib>
#include "../include/DtFechaHora.h"
#include "../include/DtPartida.h"

using namespace std;

DtPartida::DtPartida(int id, DtFechaHora fechaComienzo, string nombreVideojuego, float duracion){
	this->id = id;
	this->fechaComienzo = fechaComienzo;
	this->nombreVideojuego = nombreVideojuego;
	this->duracion = duracion;
}

DtPartida::~DtPartida(){}

int DtPartida::getId() const { return id; }

DtFechaHora DtPartida::getFechaComienzo() const {	return fechaComienzo; }

string DtPartida::getNombreVideojuego() const { return nombreVideojuego; }

float DtPartida::getDuracion() const {	return duracion; }

