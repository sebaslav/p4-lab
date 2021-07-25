#include <iostream>
#include <string>
#include "../include/Videojuego.h"
#include "../include/Partida.h"
#include "../include/Multijugador.h"
#include "../include/DtFechaHora.h"
#include "../include/Jugador.h"
#include "../include/FechaHoraSistema.h"

using namespace std;


Multijugador::Multijugador(DtPartidaMultijugador datosPartidaMultijugador, int id): Partida(id) {
	estaEnVivo = datosPartidaMultijugador.getEnVivo();
	ControladorUsuarios* ctrU = ControladorUsuarios::getInstance();
	set<string> participantes = datosPartidaMultijugador.getParticipantes();
	set<string>::iterator it;
	for (it = participantes.begin(); it != participantes.end(); it++) {
		Jugador* jugador = ctrU->getJugador((*it));
		PartidaInfo* partidaInfo = new PartidaInfo(jugador);
		infoDePartidaPorJugador.insert(partidaInfo);
	}
}

float Multijugador::obtenerHorasJugadas(){
	float resultado = 0;
	DtFechaHora fechaActual = FechaHoraSistema::getInstance()->getFechaSistema();
	DtFechaHora fechaComienzo = getFechaComienzo();
  	for (set<PartidaInfo*>::iterator it = infoDePartidaPorJugador.begin(); it != infoDePartidaPorJugador.end(); ++it)  {
		DtFechaHora fechaAbandono = (*it)->getFechaAbandono();
    	if (fechaAbandono.getAnio() != -1){
			resultado += fechaAbandono - fechaComienzo;
		} else {
			resultado += fechaActual - fechaComienzo;
		}
  	}
	//sumo las horas jugadas por el creador
	if (getDuracion() != -1){
		resultado += getDuracion();
	} else {
		resultado += fechaActual - fechaComienzo;
	}
  	return resultado;
}

void Multijugador::finalizarPartida(){
	DtFechaHora fechaActual = FechaHoraSistema::getInstance()->getFechaSistema();
	float duracion =  fechaActual - getFechaComienzo();
	setDuracion(duracion);
  	for (set<PartidaInfo*>::iterator it = infoDePartidaPorJugador.begin(); it != infoDePartidaPorJugador.end(); ++it)  {
    	PartidaInfo* info = *it;
    	if (info->getFechaAbandono().getAnio() == -1){
			info->setFechaAbandono(fechaActual);
		}
  	}
}

void Multijugador::abandonarPartida(string nickname){
  	for (set<PartidaInfo*>::iterator it = infoDePartidaPorJugador.begin(); it != infoDePartidaPorJugador.end(); ++it)  {
    	PartidaInfo* info = *it;
    	if (info->getNickname() == nickname){
			info->abandonar();
			break;
		}
  	}
}

bool Multijugador::getEstaEnVivo(){
	return estaEnVivo;
}

Multijugador::~Multijugador() {
	set<PartidaInfo*>::iterator it;
	for (it = infoDePartidaPorJugador.begin(); it != infoDePartidaPorJugador.end(); it++) {
		delete (*it);
	}
}

DtPartida* Multijugador::getDtPartida(string nombreVideojuego) {
	set<PartidaInfo*>::iterator it;
	set<string> participantes;
	for (it = infoDePartidaPorJugador.begin(); it != infoDePartidaPorJugador.end(); it++) {
		participantes.insert((*it)->getNickname());
	}
	DtPartidaMultijugador* res = new DtPartidaMultijugador(getId(), getFechaComienzo(), nombreVideojuego, getDuracion(), estaEnVivo, participantes, getNicknameCreador());
	return res;
}
