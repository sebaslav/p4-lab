#include "../include/Desarrollador.h"

Desarrollador::Desarrollador(DtDesarrollador* datos): Usuario(datos->getEmail(), datos->getContrasenia()){
	this->empresa = datos->getEmpresa();
}
Desarrollador::~Desarrollador(){}
string Desarrollador::getEmpresa(){ return empresa; }
void Desarrollador::removerEstadisticas(){ estadisticas.clear(); }
void Desarrollador::agregarEstadistica(Estadistica* estadistica){ estadisticas.insert(estadistica); }
set<Estadistica*> Desarrollador::getEstadisticas(){	return estadisticas; }
