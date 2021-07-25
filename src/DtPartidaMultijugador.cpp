#include "../include/DtPartidaMultijugador.h"
#include <string>

using namespace std;

DtPartidaMultijugador::DtPartidaMultijugador(int id, DtFechaHora fechaComienzo, string nombreVideojuego, float duracion, bool enVivo, set<string> participantes, string creador): DtPartida(id, fechaComienzo, nombreVideojuego, duracion){
	this->enVivo = enVivo;
	this->participantes = participantes;
	this->creador = creador;
}

DtPartidaMultijugador::~DtPartidaMultijugador(){}

bool DtPartidaMultijugador::getEnVivo(){ return enVivo; }

set<string> DtPartidaMultijugador::getParticipantes(){ return participantes; }

string DtPartidaMultijugador::getCreador(){ return creador; }
