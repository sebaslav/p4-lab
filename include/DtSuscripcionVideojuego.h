#ifndef DtSuscripcionVideojuego_H
#define DtSuscripcionVideojuego_H

#include <string>
#include <iostream>

using namespace std;

class DtSuscripcionVideojuego{
	private:
		string videojuego;
		float costoMensual, costoTrimestral, costoAnual, costoVitalicio;
		bool esActiva;

	public:
		DtSuscripcionVideojuego(string videojuego, float costoMensual, float costoTrimestral, float costoAnual, float costoVitalicio, bool esActiva);
		string getVideojuego() const;
		float getCostoMensual() const;
		float getCostoTrimestral() const;
		float getCostoAnual() const;
		float getCostoVitalicio() const;
		bool getEsActiva() const;
		friend ostream &operator<<(ostream &o, const DtSuscripcionVideojuego &s);
};

#endif
