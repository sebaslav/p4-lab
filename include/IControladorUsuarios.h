#ifndef IControladorUsuarios_H
#define IControladorUsuarios_H

#include <string>

#include "DtUsuario.h"
#include "TipoInicioSesion.h"

using namespace std;

class IControladorUsuarios {
	public:
		virtual bool nuevoIngreso(DtUsuario*) = 0;
        virtual void confirmarAltaUsuario() = 0;
        virtual void cancelarAltaUsuario() = 0;
        virtual TipoInicioSesion iniciarSesion(DtUsuario) = 0;
        virtual ~IControladorUsuarios() {}
};

#endif
