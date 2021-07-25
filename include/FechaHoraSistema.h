#ifndef FechaHoraSistema_H
#define FechaHoraSistema_H

#include "DtFechaHora.h"

class FechaHoraSistema{
	private:
		DtFechaHora fechaSistema;
		static FechaHoraSistema* instancia;
		FechaHoraSistema();

	public:
		static FechaHoraSistema* getInstance();
		DtFechaHora getFechaSistema();
		void setFechaSistema(DtFechaHora fecha);
};

#endif
