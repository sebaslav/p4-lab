#ifndef Suscripcion_H
#define Suscripcion_H
#include <string>

#include "DtFechaHora.h"
#include "TipoPago.h"


class Suscripcion{
	private:
		float costoAlSuscribirse;
		DtFechaHora fecha;
		TipoPago metodoPago;
	public:
		Suscripcion(float costoAlSuscribirse, DtFechaHora fecha, TipoPago metodoPago);
		virtual bool getActiva() = 0;// pure virtual
		float getCostoAlSuscribirse();
		void setCostoAlSuscribirse(float costo);
		DtFechaHora getFecha();
		void setFecha(DtFechaHora fecha);
		TipoPago getMetodoPago();
		void setMetodoPago(TipoPago tipoPago);
		virtual ~Suscripcion();
};

#endif
