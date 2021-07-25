#ifndef Genero_H
#define Genero_H

#include <string>
#include "Categoria.h"

using namespace std;

class Genero: public Categoria{
    public:
        Genero(string name, string des);
        ~Genero();
};

#endif
