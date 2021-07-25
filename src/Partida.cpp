#include <iostream>
#include <string>
#include "../include/Videojuego.h"
#include "../include/Partida.h"
#include "../include/Multijugador.h"
#include "../include/DtPartidaMultijugador.h"
#include "../include/FechaHoraSistema.h"

using namespace std;


Partida::Partida(int id) {
	this->id = id;
	duracion = -1; //Valor inválido
	ControladorUsuarios* ctrU = ControladorUsuarios::getInstance();
	creador = ctrU->getJugadorLogueado();
	FechaHoraSistema* instanciaFechaHoraSistema = FechaHoraSistema::getInstance();
	fechaComienzo = instanciaFechaHoraSistema->getFechaSistema();
}

string Partida::getNicknameCreador(){
	return creador->getNickname();
}

float Partida::getDuracion(){
    return duracion;
}

void Partida::setDuracion(float duracion) {
	this->duracion = duracion;
}
DtFechaHora Partida::getFechaComienzo() {
    return fechaComienzo;
}

int Partida::getId() {
	return id;
}

Partida::~Partida() {}
