#include "../include/FechaHoraSistema.h"
#include <string>

FechaHoraSistema* FechaHoraSistema::instancia = NULL;

FechaHoraSistema::FechaHoraSistema(){}
FechaHoraSistema* FechaHoraSistema::getInstance(){
	if(instancia == NULL)
		instancia = new FechaHoraSistema();
	return instancia;
}
DtFechaHora FechaHoraSistema::getFechaSistema(){
	return fechaSistema;
}
void FechaHoraSistema::setFechaSistema(DtFechaHora fecha){
	this->fechaSistema = fecha;
}
