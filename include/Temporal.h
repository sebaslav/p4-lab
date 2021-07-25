#ifndef Temporal_H
#define Temporal_H

#include "Suscripcion.h"
#include "TipoSuscripcion.h"
class Temporal: public Suscripcion{
	private:
		TipoSuscripcion duracion;
		bool fueCancelada;
	public:
		Temporal(float costo, DtFechaHora fecha, TipoPago metodoPago, TipoSuscripcion duracion);
		virtual bool getActiva();
		TipoSuscripcion getDuracion();
		void setDuracion(TipoSuscripcion duracion);
		bool getFueCancelada();
		void setFueCancelada(bool estado);
		virtual ~Temporal();
};
#endif
