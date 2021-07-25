#ifndef DtEstadistica_H
#define DtEstadistica_H

#include <string>

using namespace std;

class DtEstadistica{
	private:
		string nombre, descripcion;
		float valor;

	public:
		DtEstadistica(string nombre, string descripcion, float valor);
		string getNombre() const;
		string getDescripcion() const;
		float getValor() const;
};

#endif
