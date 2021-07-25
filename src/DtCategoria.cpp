#include "../include/DtCategoria.h"

DtCategoria::DtCategoria(string nombre, string descripcion){
	this->nombre = nombre;
	this->descripcion = descripcion;
}

string DtCategoria::getNombre() const { return nombre; }

string DtCategoria::getDescripcion() const { return descripcion; }

ostream &operator<<(ostream &o, const DtCategoria &c) {
	o << "Nombre: " + c.getNombre() + "\n";
    o << "Descripcion: " + c.getDescripcion() + "\n\n";
	return o;
}