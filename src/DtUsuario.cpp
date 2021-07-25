#include "../include/DtUsuario.h"

DtUsuario::DtUsuario(string email, string contrasenia){
	this->email = email;
	this->contrasenia = contrasenia;
}

DtUsuario::DtUsuario() {}

DtUsuario::~DtUsuario(){}

string DtUsuario::getEmail(){ return email; }

string DtUsuario::getContrasenia(){ return contrasenia; }
