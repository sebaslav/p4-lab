#include "../include/DtEstadistica.h"

DtEstadistica::DtEstadistica(string nombre, string descripcion, float valor){
	this->nombre = nombre;
	this->descripcion = descripcion;
	this->valor = valor;
}

string DtEstadistica::getNombre() const { return nombre; }

string DtEstadistica::getDescripcion() const { return descripcion; }

float DtEstadistica::getValor() const { return valor; }
