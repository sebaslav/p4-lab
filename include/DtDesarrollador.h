#ifndef DtDesarrollador_H
#define DtDesarrollador_H

#include <string>
#include "DtUsuario.h"

using namespace std;

class DtDesarrollador : public DtUsuario{
    private:
        string empresa;
	public:
		DtDesarrollador(string email, string contrasenia, string empresa);
		~DtDesarrollador();
        string getEmpresa();
};

#endif
