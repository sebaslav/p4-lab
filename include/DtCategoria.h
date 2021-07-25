#ifndef DtCategoria_H
#define DtCategoria_H

#include <string>

using namespace std;

class DtCategoria{
	private:
		string nombre, descripcion;

	public:
		DtCategoria(string nombre, string descripcion);
		string getNombre() const;
		string getDescripcion() const;
		friend ostream &operator<<(ostream &o, const DtCategoria &c);
};

#endif
