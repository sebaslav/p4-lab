#ifndef DtPartidaIndividual_H
#define DtPartidaIndividual_H
#include "DtPartida.h"

class DtPartidaIndividual: public DtPartida{
	private:
		bool continuacion;
	public:
        DtPartidaIndividual(int id, DtFechaHora fechaComienzo, string nombreVideojuego, float duracion, bool continuacion);
		~DtPartidaIndividual();
		bool getContinuacion() const;
};


#endif
