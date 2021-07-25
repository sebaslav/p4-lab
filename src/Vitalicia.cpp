#include "../include/Vitalicia.h"

Vitalicia::Vitalicia(TipoPago tipoPago, float costo, DtFechaHora fecha): Suscripcion(costo, fecha, tipoPago) {}

bool Vitalicia::getActiva(){
	return true;
}

Vitalicia::~Vitalicia() {}