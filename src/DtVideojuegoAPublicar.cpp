#include "../include/DtVideojuegoAPublicar.h"

DtVideojuegoAPublicar::DtVideojuegoAPublicar() {}

DtVideojuegoAPublicar::DtVideojuegoAPublicar(string nombre, string descripcion, float costoMensual, float costoTrimestral, float costoAnual, float costoVitalicio){
	this->nombre = nombre;
	this->descripcion = descripcion;
	this->costoMensual = costoMensual;
	this->costoTrimestral = costoTrimestral;
	this->costoAnual = costoAnual;
	this->costoVitalicio = costoVitalicio;
}

string DtVideojuegoAPublicar::getNombre(){ return nombre; }

string DtVideojuegoAPublicar::getDescripcion(){ return descripcion; }

float DtVideojuegoAPublicar::getCostoMensual(){ return costoMensual; }

float DtVideojuegoAPublicar::getCostoTrimestral(){ return costoTrimestral; }

float DtVideojuegoAPublicar::getCostoAnual(){ return costoAnual; }

float DtVideojuegoAPublicar::getCostoVitalicio(){  return costoVitalicio; }
