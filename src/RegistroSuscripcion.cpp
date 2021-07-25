#include "../include/RegistroSuscripcion.h"
#include "../include/Temporal.h"
#include "../include/Vitalicia.h"
#include "../include/FechaHoraSistema.h"

RegistroSuscripcion::RegistroSuscripcion(TipoSuscripcion tipoSuscripcion, TipoPago tipoPago, float costo){
	ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
	Jugador* jugadorLogueado = controladorUsuarios->getJugadorLogueado();
	jug = jugadorLogueado;
	DtFechaHora fechaActual = FechaHoraSistema::getInstance()->getFechaSistema();
	Suscripcion* nuevaSuscripcion;
	if(tipoSuscripcion != TipoSuscripcion::Vitalicia)
		nuevaSuscripcion = new Temporal(costo, fechaActual, tipoPago, tipoSuscripcion);
	else//tipoSuscripcion == Vitalicia
		nuevaSuscripcion = new Vitalicia(tipoPago, costo, fechaActual);
	this->suscripciones.insert(nuevaSuscripcion);
}

string RegistroSuscripcion::getNicknameJugador(){
	return this->jug->getNickname();
}

bool RegistroSuscripcion::getEsActiva(){
	set<Suscripcion*>::iterator it = suscripciones.begin();
	while(it != suscripciones.end() && !(*it)->getActiva()){it++;}
	if (it != suscripciones.end())
		return true;
	else
		return false;
}

EstadoSuscripcion RegistroSuscripcion::getEstadoSuscripcion(){
	set<Suscripcion*>::iterator it = suscripciones.begin();
	while(it != suscripciones.end() and !(*it)->getActiva()){it++;}
	if (it == suscripciones.end())
		return EstadoSuscripcion::Vencida;
	if(dynamic_cast<Vitalicia*>(*it))
		return EstadoSuscripcion::Vitalicia;
	return EstadoSuscripcion::Temporal;
}

void RegistroSuscripcion::darDeAltaSuscripcion(TipoSuscripcion tipoSuscripcion, TipoPago tipoPago, float costo, EstadoSuscripcion estado){
	if(estado == EstadoSuscripcion::Temporal){
		set<Suscripcion*>::iterator it = suscripciones.begin();

		while(it != suscripciones.end() and !(*it)->getActiva()){ it++; }

		Temporal* temporal = dynamic_cast<Temporal*>(*it);
		temporal->setFueCancelada(true);
	}
	FechaHoraSistema* horaSistema = FechaHoraSistema::getInstance();

	Suscripcion* nuevaSuscripcion;
	if(tipoSuscripcion != TipoSuscripcion::Vitalicia){
		nuevaSuscripcion = new Temporal(costo, horaSistema->getFechaSistema(), tipoPago, tipoSuscripcion);
	}
	else{ // tipoSuscripcion == TipoSuscripcion::Vitalicia
		nuevaSuscripcion = new Vitalicia(tipoPago, costo, horaSistema->getFechaSistema());
	}
	this->suscripciones.insert(nuevaSuscripcion);
}

RegistroSuscripcion::~RegistroSuscripcion() {
	set<Suscripcion*>::iterator it;
	for (it = suscripciones.begin(); it != suscripciones.end(); it++) {
		delete (*it);
	}
}