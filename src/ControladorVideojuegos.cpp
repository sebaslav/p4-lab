#include "../include/ControladorVideojuegos.h"
#include "../include/ControladorUsuarios.h"
#include "../include/Genero.h"
#include "../include/Plataforma.h"
#include "../include/Otros.h"
#include "../include/Estadistica.h"
#include "../include/TotalHorasJugadas.h"
#include "../include/TotalJugadores.h"
#include "../include/Desarrollador.h"
#include<bits/stdc++.h>

#include <string>

using namespace std;

ControladorVideojuegos* ControladorVideojuegos::instancia = NULL;

ControladorVideojuegos::ControladorVideojuegos(){
  this->videojuegoRecordado = NULL;
  Estadistica* estadistica = new TotalHorasJugadas();
  estadisticas.insert({"TotalHorasJugadas", estadistica});
  estadistica = new TotalJugadores();
  estadisticas.insert({"TotalJugadores", estadistica});
}

ControladorVideojuegos* ControladorVideojuegos::getInstance(){
    if (instancia == NULL)
      {
        instancia = new ControladorVideojuegos();
      }
    return instancia;
}

set<string> ControladorVideojuegos::obtenerNombresVideojuegos(){
    set<string> res;
    map<string,Videojuego*>::iterator it;
    string nombre;

    for(it = coleccionVideojuegos.begin(); it != coleccionVideojuegos.end(); ++it){
        nombre = it->second->getNombre();
        res.insert(nombre);
    }
    return res;
}

void ControladorVideojuegos::ingresarDatosVideojuego(DtVideojuegoAPublicar data){
    datos = data;
}

set<DtCategoria*> ControladorVideojuegos::obtenerCategoriasGenero(){
    set<DtCategoria*> res;
    map<string,Categoria*>::iterator it;

    for(it = categoriasEnSistema.begin();it != categoriasEnSistema.end();++it){
        Categoria* cat = it->second;
        Genero* elem = dynamic_cast<Genero*>(cat);
        if (elem != NULL)
            res.insert(elem->getDtCategoria()); //Pedir un constructor
    }
    return res;
}

void ControladorVideojuegos::seleccionarGeneros(set<string> generos){
    set<string>::iterator it_string;
    string clave;
    Categoria* elem;
    for(it_string = generos.begin();it_string != generos.end();++it_string){
        clave = *it_string;
        elem = (categoriasEnSistema.find(clave))->second;
        categoriasRecordadas.insert(elem);
    }
}


set<DtCategoria*> ControladorVideojuegos::obtenerCategoriasPlataforma(){
    set<DtCategoria*> res;
    map<string,Categoria*>::iterator it;
    Plataforma *elem;

    for(it = categoriasEnSistema.begin();it != categoriasEnSistema.end();++it){
        elem = dynamic_cast<Plataforma*>(it->second);
        if (elem != NULL)
            res.insert(elem->getDtCategoria()); //Pedir un constructor
    }
    return res;
}

void ControladorVideojuegos::seleccionarPlataformas(set<string> plataformas){
    set<string>::iterator it_string;
    string clave;
    Categoria* elem;
    for(it_string = plataformas.begin();it_string != plataformas.end();++it_string){
        clave = *it_string;
        elem = (categoriasEnSistema.find(clave))->second;
        categoriasRecordadas.insert(elem);
    }
}


set<DtCategoria*> ControladorVideojuegos::obtenerCategoriasOtro(){
    set<DtCategoria*> res;
    map<string,Categoria*>::iterator it;
    Otros *elem;

    for(it = categoriasEnSistema.begin();it != categoriasEnSistema.end();++it){
        elem = dynamic_cast<Otros*>(it->second);
        if (elem != NULL)
            res.insert(elem->getDtCategoria()); //Pedir un constructor
    }
    return res;
}

void ControladorVideojuegos::seleccionarOtras(set<string> otros){
    set<string>::iterator it_string;
    string clave;
    Categoria* elem;
    for(it_string = otros.begin();it_string != otros.end();++it_string){
        clave = *it_string;
        elem = (categoriasEnSistema.find(clave))->second;
        categoriasRecordadas.insert(elem);
    }
}

//copy pate para Plataforma y otros

void ControladorVideojuegos::confirmarAltaVideojuego() {
    set<Categoria*>::iterator it;
    Videojuego *vid = new Videojuego(datos);
    for(it = categoriasRecordadas.begin();it != categoriasRecordadas.end();it++){
      vid->agregarCategoria(*it);
    }
    categoriasRecordadas.clear();
    coleccionVideojuegos.insert({datos.getNombre(), vid});
}

void ControladorVideojuegos::cancelarAltaVideojuego() {
    categoriasRecordadas.clear();
}

//Suscribirse a Videojuego

set<DtSuscripcionVideojuego*> ControladorVideojuegos::obtenerSuscripciones() {
    map<string,Videojuego*>::iterator it;
    set<DtSuscripcionVideojuego*> res;

    for(it = coleccionVideojuegos.begin(); it != coleccionVideojuegos.end(); ++it){
        res.insert((it->second)->getDtSuscripcionVideojuego());
    }
	return res;
}

EstadoSuscripcion ControladorVideojuegos::obtenerEstadoActual(string nombre) {
     EstadoSuscripcion est;
     Videojuego *elem = (coleccionVideojuegos.find(nombre))->second;
     setVideojuego(elem);
     est = elem->getEstadoSuscripcion();
     setEstado(est);
	 return est;
}

void ControladorVideojuegos::setEstado(EstadoSuscripcion estado){
    estadoSuscripcion = estado;
}

void ControladorVideojuegos::setVideojuego(Videojuego* videojuego) {
    videojuegoRecordado = videojuego;
}
void ControladorVideojuegos::confirmarSuscripcion(TipoSuscripcion tipoSuscripcion, TipoPago tipoPago) {
    videojuegoRecordado->darDeAltaSuscripcion(tipoSuscripcion,tipoPago,estadoSuscripcion);
    setVideojuego(NULL);
}

void ControladorVideojuegos::cancelarSuscripcion() {
    setVideojuego(NULL);

}

set<string> ControladorVideojuegos::obtenerVideojuegosEliminables() {
    set<string> res;
    map<string,Videojuego*>::iterator it;
    Videojuego *elem;
    bool b1,b2;
    for(it = coleccionVideojuegos.begin(); it != coleccionVideojuegos.end(); ++it){
        elem = it->second;
        b1 = elem->desarrolladorEstaLogueado();
        if (b1) {
            b2 = elem->tienePartidasSinFinalizar();
            if (!b2) {
                res.insert(elem->getNombre());
            }
        }
    }
    return res;
}

void ControladorVideojuegos::seleccionarVideojuegoAEliminar(string nombre){
    videojuegoRecordado = (coleccionVideojuegos.find(nombre))->second;
}

void ControladorVideojuegos::confirmarEliminacion() {
    string clave = videojuegoRecordado->getNombre();
    coleccionVideojuegos.erase(clave);
    delete videojuegoRecordado;
}

void ControladorVideojuegos::cancelarEliminacion() {
   videojuegoRecordado = NULL;
}

set<string> ControladorVideojuegos::obtenerMisVideojuegosDesarrollados() {
    set<string> res;
    map<string,Videojuego*>::iterator it;
    Videojuego *elem;
    for(it = coleccionVideojuegos.begin(); it != coleccionVideojuegos.end(); ++it){
        elem = it->second;
        if (elem->desarrolladorEstaLogueado()) {
            res.insert(elem->getNombre());
        }
    }
	return res;
}

Videojuego* ControladorVideojuegos::getVideojuego(string nombre) {
    Videojuego* res = (coleccionVideojuegos.find(nombre))->second;
    return res;
}

set<DtEstadistica*> ControladorVideojuegos::obtenerEstadisticas(string nombreVideojuego){
    set<DtEstadistica*> res;
    Videojuego* vid;
    vid = (coleccionVideojuegos.find(nombreVideojuego))->second;
    ControladorUsuarios* cont = ControladorUsuarios::getInstance();
    Desarrollador* dev;
    dev = cont->getDesarrollador();
    set<Estadistica*> estadisticasDelDev = dev->getEstadisticas();
    set<Estadistica*>::iterator it;
    for(it = estadisticasDelDev.begin(); it != estadisticasDelDev.end(); ++it){
       res.insert((*it)->obtenerEstadistica(vid)); //calcula estadisticas...
    }
	return res;
}

set<string> ControladorVideojuegos::obtenerCategorias(){
    set<string> res;
    map<string,Categoria*>::iterator it;
    string elem;

    for(it = categoriasEnSistema.begin();it != categoriasEnSistema.end();++it){
        elem = (it->second)->getNombre();
        res.insert(elem);
    }
    return res;
}

void ControladorVideojuegos::ingresarDatosCategoria(string nombre, string descripcion, TipoCategoria tipo){
    nombreCategoria = nombre;
    descripcionCategoria = descripcion;
    tipoCategoria = tipo;
}

void ControladorVideojuegos::confirmarAgregarCategoria() {
    Categoria* elem;
    switch(tipoCategoria) {
        case plataforma:
            elem = new Plataforma(nombreCategoria,descripcionCategoria);
            break;
        case genero:
            elem = new Genero(nombreCategoria,descripcionCategoria);
            break;
        case otroTipo:
            elem = new Otros(nombreCategoria,descripcionCategoria);
            break;
    }
    categoriasEnSistema.insert({nombreCategoria, elem});
}

void ControladorVideojuegos::cancelarAgregarCategoria(){

}

set<DtVideojuegoAPuntuar*> ControladorVideojuegos::obtenerDtVideojuegos() {
    set<DtVideojuegoAPuntuar*> res;
    map<string,Videojuego*>::iterator it;
    for(it = coleccionVideojuegos.begin(); it != coleccionVideojuegos.end(); ++it){
        DtVideojuegoAPuntuar* elem = (it->second)->obtenerDtVideojuegoAPuntuar();
        res.insert(elem);
    }
    return res;
}

void ControladorVideojuegos::asignarPuntaje(string videojuego, int puntaje){
    Videojuego* elem =(coleccionVideojuegos.find(videojuego))->second;
    elem->asignarPuntaje(puntaje);
}

map<string,Videojuego*> ControladorVideojuegos::getColeccionVideojuegos(){
    return coleccionVideojuegos;
}

DtVideojuegoAMostrar ControladorVideojuegos::obtenerDtVideojuego(string nombre){
    Videojuego* elem = (coleccionVideojuegos.find(nombre))->second;
    return elem->getDtVideojuegoAMostrar();
}

set<DtEstadistica*> ControladorVideojuegos::obtenerEstadisticasDelSistema(){
    set<DtEstadistica*> res;
    map<string, Estadistica*>::iterator it;
    for(it = estadisticas.begin(); it != estadisticas.end(); ++it){
        res.insert(it->second->obtenerDtEstadistica());
    }
    return res;
}

void ControladorVideojuegos::seleccionarEstadisticas(set<string> nombres){
    ControladorUsuarios* cont =ControladorUsuarios::getInstance();
    Desarrollador* dev = cont->getDesarrollador();
    dev->removerEstadisticas();
    set<string>::iterator it;
    for(it = nombres.begin(); it!= nombres.end(); ++it){
        Estadistica* estadisticaAAgregar = estadisticas.find(*it)->second;
        dev->agregarEstadistica(estadisticaAAgregar);
    }
}

ControladorVideojuegos::~ControladorVideojuegos() {

    map<string, Videojuego*>::iterator it1;
    for(it1 = coleccionVideojuegos.begin(); it1 != coleccionVideojuegos.end(); ++it1){
        delete it1->second;
    }


    map<string, Estadistica*>::iterator it2;
    for(it2 = estadisticas.begin(); it2 != estadisticas.end(); ++it2){
        delete it2->second;
    }

    map<string, Categoria*>::iterator it3;
    for(it3 = categoriasEnSistema.begin(); it3 != categoriasEnSistema.end(); ++it3){
        delete it3->second;
    }

    videojuegoRecordado = NULL;
    instancia = NULL;

}
