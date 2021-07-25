#include <iostream>
#include <string>
#include "../include/Videojuego.h"
#include "../include/Partida.h"
#include "../include/DtPartidaIndividual.h"
#include "../include/Individual.h"
#include "../include/FechaHoraSistema.h"

using namespace std;

Individual::Individual(Individual* partidaAContinuar, int id): Partida(id) {
	this->partidaAContinuar = partidaAContinuar;
}

void Individual::finalizarPartida(){
	DtFechaHora fechaActual = FechaHoraSistema::getInstance()->getFechaSistema();
	float duracion =  fechaActual - getFechaComienzo();
	setDuracion(duracion);
}

float Individual::obtenerHorasJugadas(){
	if (getDuracion() != -1)
		return getDuracion();
	else {
		DtFechaHora fechaActual = FechaHoraSistema::getInstance()->getFechaSistema();
		return fechaActual - getFechaComienzo();
	} 
}

Individual* Individual::getPartidaAContinuar(){
	return partidaAContinuar;
}

Individual::~Individual() {}

DtPartida* Individual::getDtPartida(string nombreVideojuego) {
	bool continuacion = partidaAContinuar != NULL;
	DtPartida* res = new DtPartidaIndividual(getId(), getFechaComienzo(), nombreVideojuego, getDuracion(), continuacion);
	return res;
}