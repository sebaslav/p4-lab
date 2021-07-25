#ifndef DtVideojuegoAPuntuar_H
#define DtVideojuegoAPuntuar_H

#include <string>
#include <iostream>

using namespace std;

class DtVideojuegoAPuntuar{
	private:
		string nombre, descripcion;

	public:
		DtVideojuegoAPuntuar(string nombre, string descripcion);
		string getNombre() const;
		string getDescripcion() const;
		friend ostream &operator<<(ostream &o, const DtVideojuegoAPuntuar &v);
};

#endif
