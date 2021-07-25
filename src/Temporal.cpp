#include "../include/Temporal.h"
#include "../include/FechaHoraSistema.h"

Temporal::Temporal(float costo, DtFechaHora fecha, TipoPago metodoPago, TipoSuscripcion duracion) : Suscripcion(costo, fecha, metodoPago){
	this->duracion = duracion;
	this->fueCancelada = false;
}
bool Temporal::getActiva(){
	if (fueCancelada)
		return false;
	DtFechaHora fechaActual = FechaHoraSistema::getInstance()->getFechaSistema();
	float tiempoTranscurrido = fechaActual - getFecha();
	if (duracion == TipoSuscripcion::Mensual)
		return tiempoTranscurrido < 720; //30*24 horas
	if (duracion == TipoSuscripcion::Trimensual)
		return tiempoTranscurrido < 2160; //90*24 horas
	return tiempoTranscurrido < 8760; //365*24 horas
}

TipoSuscripcion Temporal::getDuracion(){
	return this->duracion;
}

void Temporal::setDuracion(TipoSuscripcion dur){
	this->duracion = dur;
}

bool Temporal::getFueCancelada(){
	return this->fueCancelada;
}

void Temporal::setFueCancelada(bool estado){
	this->fueCancelada = estado;
}

Temporal::~Temporal() {}