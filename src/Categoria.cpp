#include "../include/Categoria.h"

Categoria::Categoria(string name, string des) {
	nombre = name;
	descripcion = des;
}

DtCategoria* Categoria::getDtCategoria(){
	return new DtCategoria(this->nombre, this->descripcion);
}

Categoria::~Categoria(){}

void Categoria::setNombre(string name){
	this->nombre = name;
}

string Categoria::getNombre(){
	return this->nombre;
}

void Categoria::setDescripcion(string des){
	this->descripcion = des;
}

string Categoria::getDescripcion(){
	return this->descripcion;
}


