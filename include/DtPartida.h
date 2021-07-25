#ifndef DtPartida_H
#define DtPartida_H

#include <string>
#include "DtFechaHora.h"

using namespace std;

class DtPartida {
    private:
		int id;
        DtFechaHora fechaComienzo;
        string nombreVideojuego;
		float duracion;
    public:
        DtPartida(int id, DtFechaHora fechaComienzo, string nombreVideojuego, float duracion);
        virtual ~DtPartida();
		int getId() const;
		DtFechaHora getFechaComienzo() const;
		string getNombreVideojuego() const;
		float getDuracion() const;
        /* friend ostream &operator<<(ostream &o, DtPartida* &partida); */
};

#endif
