#include "../include/Fabrica.h"

Fabrica* Fabrica::instancia = NULL;

Fabrica::Fabrica(){}

Fabrica* Fabrica::getInstance(){
	if(instancia == NULL)
		instancia = new Fabrica();
	return instancia;
}

IControladorUsuarios* Fabrica::getIUsuarios(){
	return ControladorUsuarios::getInstance(); 
}

IControladorVideojuegos* Fabrica::getIVideojuegos(){
	return ControladorVideojuegos::getInstance();

}

IControladorPartidas* Fabrica::getIPartidas(){
	return ControladorPartidas::getInstance(); 
}

Fabrica::~Fabrica() {}
