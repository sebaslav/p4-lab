#include "../include/DtVideojuegoAMostrar.h"

DtVideojuegoAMostrar::DtVideojuegoAMostrar(string nombre, string descripcion, string empresaDesarrollador, set<string> categorias, float costoMensual, float costoTrimestral, float costoAnual, float costoVitalicio, float puntajePromedio, float totalHorasJugadas){
	this->nombre = nombre;
	this->descripcion = descripcion;
	this->empresaDesarrollador = empresaDesarrollador;
	this->categorias = categorias;
	this->costoMensual = costoMensual;
	this->costoTrimestral = costoTrimestral;
	this->costoAnual = costoAnual;
	this->costoVitalicio = costoVitalicio;
	this->puntajePromedio = puntajePromedio;
	this->totalHorasJugadas = totalHorasJugadas;
}

string DtVideojuegoAMostrar::getNombre() const { return nombre; }

string DtVideojuegoAMostrar::getDescripcion() const { return descripcion; }

string DtVideojuegoAMostrar::getEmpresaDesarrollador() const { return empresaDesarrollador; }

set<string> DtVideojuegoAMostrar::getCategorias() const { return categorias; }

float DtVideojuegoAMostrar::getCostoMensual() const { return costoMensual; }

float DtVideojuegoAMostrar::getCostoTrimestral() const { return costoTrimestral; }

float DtVideojuegoAMostrar::getCostoAnual() const { return costoAnual; }

float DtVideojuegoAMostrar::getCostoVitalicio() const { return costoVitalicio; }

float DtVideojuegoAMostrar::getPuntajePromedio() const { return puntajePromedio; }

float DtVideojuegoAMostrar::getTotalHorasJugadas() const { return totalHorasJugadas; }

ostream &operator<<(ostream &o, const DtVideojuegoAMostrar &v) {
	o << "Descripcion: " + v.getDescripcion() + "\n";
    o << "Costo mensual: " <<v.getCostoMensual() << "\n";
    o << "Costo trimestral: " << v.getCostoTrimestral() << "\n";
    o << "Costo anual: " << v.getCostoAnual() << "\n";
    o << "Costo vitalicio: " << v.getCostoVitalicio() << "\n";
    o << "Categorias a las que pertenece:\n";
    set<string> categorias = v.getCategorias();
	set<string>::iterator it;
    for (it=categorias.begin(); it!=categorias.end();it++) {
        o << (*it) << "\n";
    }
    o << "Empresa que lo desarrollo: " + v.getEmpresaDesarrollador() + "\n";
    o << "Puntaje promedio: " << v.getPuntajePromedio() << "\n";
	return o;
}