#ifndef Estadistica_H
#define Estadistica_H
#include <string>

#include "DtEstadistica.h"

using namespace std;

class Videojuego; //Forward declaration para romper dependencias circulares

class Estadistica {
	public:
		virtual DtEstadistica* obtenerEstadistica(Videojuego *videojuego) = 0;
		virtual DtEstadistica* obtenerDtEstadistica() = 0;
		virtual ~Estadistica() {}
};

#endif
