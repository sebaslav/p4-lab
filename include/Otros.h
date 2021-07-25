#ifndef Otros_H
#define Otros_H

#include <string>
#include "Categoria.h"

using namespace std;

class Otros: public Categoria {
    public:
		Otros(string nombre, string descripcion);
		virtual ~Otros();

};

#endif
