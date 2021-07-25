#ifndef DtJugador_H
#define DtJugador_H

#include <string>
#include "DtUsuario.h"

using namespace std;

class DtJugador : public DtUsuario{
    private:
        string nickname, descripcion;
	public:
		DtJugador(string email, string contrasenia, string nickname, string descripcion);
		~DtJugador();
        string getNickname();
        string getDescripcion();
};

#endif
