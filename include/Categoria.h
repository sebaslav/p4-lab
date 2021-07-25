#ifndef Categoria_H
#define Categoria_H
#include <string>

#include "DtCategoria.h"

using namespace std;

class Categoria {
	private:
		string nombre;
		string descripcion;
	public:
		Categoria(string, string);
		DtCategoria* getDtCategoria();
		virtual ~Categoria() = 0;
		void setNombre(string name);
		string getNombre();
		void setDescripcion(string des);
		string getDescripcion();
};

#endif
