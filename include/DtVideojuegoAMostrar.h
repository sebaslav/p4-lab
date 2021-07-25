#ifndef DtVideojuegoAMostrar_H
#define DtVideojuegoAMostrar_H

#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class DtVideojuegoAMostrar{
	private:
		string nombre, descripcion, empresaDesarrollador;
		set<string> categorias;
		float costoMensual, costoTrimestral, costoAnual, costoVitalicio, puntajePromedio, totalHorasJugadas;

	public:
		DtVideojuegoAMostrar(string nombre, string descripcion, string empresaDesarrollador, set<string> categorias, float costoMensual, float costoTrimestral, float costoAnual, float costoVitalicio, float puntajePromedio, float totalHorasJugadas);
		string getNombre() const;
		string getDescripcion() const;
		string getEmpresaDesarrollador() const;
		set<string> getCategorias() const;
		float getCostoMensual() const;
		float getCostoTrimestral() const;
		float getCostoAnual() const;
		float getCostoVitalicio() const;
		float getPuntajePromedio() const;
		float getTotalHorasJugadas() const;
		friend ostream &operator<<(ostream &o, const DtVideojuegoAMostrar &v);
};

#endif
