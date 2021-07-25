#include "../include/Usuario.h"

Usuario::Usuario(string email, string contrasenia){
	this->email = email;
	this->contrasenia = contrasenia;
}
Usuario::~Usuario(){}
string Usuario::getEmail(){ return email; }
string Usuario::getContrasenia(){ return contrasenia; }
