#ifndef Vitalicia_H 
#define Vitalicia_H

#include "Suscripcion.h"

class Vitalicia: public Suscripcion{
	public:
		Vitalicia(TipoPago p, float costo, DtFechaHora fecha);
		virtual bool getActiva();	 
		virtual ~Vitalicia();
};

#endif

