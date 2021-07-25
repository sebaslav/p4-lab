#ifndef TotalHorasJugadas_H
#define TotalHorasJugadas_H
#include <string>

#include "Videojuego.h"
#include "DtEstadistica.h"
#include "Estadistica.h"

using namespace std;

class TotalHorasJugadas: public Estadistica {
        private:
        string nombre, descripcion;
        
        public:
        TotalHorasJugadas();
        DtEstadistica* obtenerEstadistica(Videojuego* videojuego);
        DtEstadistica* obtenerDtEstadistica();
        virtual ~TotalHorasJugadas();
};

#endif
