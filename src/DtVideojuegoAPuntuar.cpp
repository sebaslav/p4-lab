#include "../include/DtVideojuegoAPuntuar.h"

DtVideojuegoAPuntuar::DtVideojuegoAPuntuar(string nombre, string descripcion){
	this->nombre = nombre;
	this->descripcion = descripcion;
}

string DtVideojuegoAPuntuar::getNombre() const{ return nombre; }

string DtVideojuegoAPuntuar::getDescripcion() const{ return descripcion; }

ostream &operator<<(ostream &o, const DtVideojuegoAPuntuar &v) {
	o << "Nombre: " + v.getNombre() + "\n";
    o << "Descripcion: " + v.getDescripcion() + "\n\n";
	return o;
}