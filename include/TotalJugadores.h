#ifndef TotalJugadores_H
#define TotalJugadores_H
#include <string>

#include "Videojuego.h"
#include "DtEstadistica.h"
#include "Estadistica.h"

using namespace std;

class TotalJugadores: public Estadistica {
        private:
        string nombre, descripcion;
        
	public:
        TotalJugadores();
        DtEstadistica* obtenerEstadistica(Videojuego* videojuego);
        DtEstadistica* obtenerDtEstadistica();
        virtual ~TotalJugadores();
};

#endif
