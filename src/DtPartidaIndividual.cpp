#include "../include/DtPartidaIndividual.h"
#include "../include/DtPartida.h"
#include <iostream>
#include <string>

using namespace std;

DtPartidaIndividual::DtPartidaIndividual(int id, DtFechaHora fechaComienzo, string nombreVideojuego, float duracion, bool continuacion): DtPartida(id, fechaComienzo, nombreVideojuego, duracion){
	this->continuacion = continuacion;
}
DtPartidaIndividual::~DtPartidaIndividual(){}
bool DtPartidaIndividual::getContinuacion() const { return continuacion; }
