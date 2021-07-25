#ifndef DtVideojuegoAPublicar_H
#define DtVideojuegoAPublicar_H

#include <string>

using namespace std;

class DtVideojuegoAPublicar{
	private:
		string nombre, descripcion;
		float costoMensual, costoTrimestral, costoAnual, costoVitalicio;

	public:
		DtVideojuegoAPublicar();
		DtVideojuegoAPublicar(string nombre, string descripcion, float costoMensual, float costoTrimestral, float costoAnual, float costoVitalicio);
		string getNombre();
		string getDescripcion();
		float getCostoMensual();
		float getCostoTrimestral();
		float getCostoAnual();
		float getCostoVitalicio();
};

#endif
