#ifndef Fabrica_H
#define Fabrica_H
#include <string>

#include "IControladorUsuarios.h"
#include "IControladorVideojuegos.h"
#include "IControladorPartidas.h"
#include "ControladorPartidas.h"
#include "ControladorVideojuegos.h"
#include "ControladorUsuarios.h"

class Fabrica {
	private:
		static Fabrica* instancia;
		Fabrica();
	public:
		static Fabrica* getInstance();
		IControladorUsuarios* getIUsuarios();
		IControladorVideojuegos* getIVideojuegos();
		IControladorPartidas* getIPartidas();
		~Fabrica();
};


#endif
