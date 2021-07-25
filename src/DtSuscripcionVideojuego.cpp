#include "../include/DtSuscripcionVideojuego.h"

DtSuscripcionVideojuego::DtSuscripcionVideojuego(string videojuego, float costoMensual, float costoTrimestral, float costoAnual, float costoVitalicio, bool esActiva){
	 this->videojuego = videojuego;
	 this->costoMensual = costoMensual;
	 this->costoTrimestral = costoTrimestral;
	 this->costoAnual = costoAnual;
	 this->costoVitalicio = costoVitalicio;
	 this->esActiva = esActiva;
}

string DtSuscripcionVideojuego::getVideojuego() const{ return videojuego; }

float DtSuscripcionVideojuego::getCostoMensual() const{ return costoMensual; }

float DtSuscripcionVideojuego::getCostoTrimestral() const{ return costoTrimestral; }

float DtSuscripcionVideojuego::getCostoAnual() const{ return costoAnual; }

float DtSuscripcionVideojuego::getCostoVitalicio() const{ return costoVitalicio; }

bool DtSuscripcionVideojuego::getEsActiva() const{ return esActiva; }

ostream &operator<<(ostream &o, const DtSuscripcionVideojuego &s) {
	o << "Nombre: " << s.getVideojuego() << "\n";
	o << "Costo mensual: " << s.getCostoMensual() << "\n";
	o << "Costo trimestral: " << s.getCostoTrimestral() << "\n";
	o << "Costo anual: " << s.getCostoAnual() << "\n";
	o << "Costo vitalicio: " << s.getCostoVitalicio() << "\n\n";
	return o;
}