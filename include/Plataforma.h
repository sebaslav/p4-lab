#ifndef Platafoma_H
#define Platafoma_H

#include <string>
#include "Categoria.h"

using namespace std;

class Plataforma: public Categoria{
    public:
        Plataforma(string nombre, string descripcion);
	    virtual ~Plataforma();

};

#endif
