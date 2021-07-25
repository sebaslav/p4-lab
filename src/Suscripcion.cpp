#include "../include/Suscripcion.h"

Suscripcion::Suscripcion(float costoAlSuscribirse, DtFechaHora fecha, TipoPago metodoPago){
	this->costoAlSuscribirse = costoAlSuscribirse;
	this->fecha = fecha;
	this->metodoPago = metodoPago;
}

float Suscripcion::getCostoAlSuscribirse(){
	return costoAlSuscribirse;
}

void Suscripcion::setCostoAlSuscribirse(float costo){
	costoAlSuscribirse = costo;
}

DtFechaHora Suscripcion::getFecha(){
	return this->fecha;
}

void Suscripcion::setFecha(DtFechaHora fecha){
	this->fecha = fecha;
}

TipoPago Suscripcion::getMetodoPago(){
	return this->metodoPago;
}

void Suscripcion::setMetodoPago(TipoPago metodoPago){
	this->metodoPago = metodoPago;
}

Suscripcion::~Suscripcion() {}