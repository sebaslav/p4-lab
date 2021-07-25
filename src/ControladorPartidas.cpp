#include <iostream>
#include <string>
#include "../include/ControladorPartidas.h"
#include "../include/ControladorUsuarios.h"
#include "../include/FechaHoraSistema.h"

using namespace std;

ControladorPartidas* ControladorPartidas::instancia = NULL;

ControladorPartidas::ControladorPartidas(){
  videojuegoAIniciarPartida = NULL;
  partidaAContinuar = NULL;
  datosPartidaMultijugador = NULL;
  contador = 1;
}

ControladorPartidas* ControladorPartidas::getInstance(){
    if (instancia == NULL)
      {
        instancia = new ControladorPartidas();
      }
    return instancia;
}

set<string> ControladorPartidas::obtenerMisVideojuegos(){
  ControladorVideojuegos* controladorVideojuegos = ControladorVideojuegos::getInstance();
  map<string,Videojuego*>  coleccionVideojuegos = controladorVideojuegos->getColeccionVideojuegos();
  set<string> resultado;
  string nombre;
  for (map<string,Videojuego*>::iterator it = coleccionVideojuegos.begin(); it != coleccionVideojuegos.end(); ++it)  {
    Videojuego *videojuego = it->second;
    if (videojuego->estaSuscriptoJugadorLogueado()){
      nombre = videojuego->getNombre();
      resultado.insert(nombre);
    }
  }
  return resultado;
}		

void ControladorPartidas::seleccionarVideojuego(string nombre){
  ControladorVideojuegos* controladorVideojuegos = ControladorVideojuegos::getInstance();
  Videojuego* videojuego = controladorVideojuegos->getVideojuego(nombre);
  videojuegoAIniciarPartida = videojuego;
}

set<DtPartidaIndividual*> ControladorPartidas::obtenerPartidasIndividualesFinalizadas(){
  set<DtPartidaIndividual*> coleccionDtPartidaIndividual = videojuegoAIniciarPartida->getPartidasIndividualesFinalizadas();
  return coleccionDtPartidaIndividual;
}

void ControladorPartidas::seleccionarPartidaAContinuar(int id){
  Partida* partidaAContinuar = videojuegoAIniciarPartida->obtenerPartida(id);
  Individual* individualAContinuar = dynamic_cast<Individual*>(partidaAContinuar);
  this->partidaAContinuar = individualAContinuar;
}

set<string> ControladorPartidas::obtenerJugadoresConSuscripcion(){
  set<string> jugadoresConSuscripcion = videojuegoAIniciarPartida->obtenerJugadoresConSuscripcion();
  return jugadoresConSuscripcion;
}

void ControladorPartidas::ingresarDatosPartidaMultijugador(bool enVivo, set<string> participantes){
  DtPartidaMultijugador* datosPartidaMultijugador = new DtPartidaMultijugador(0, DtFechaHora(), "", 0, enVivo, participantes, "");
  this->datosPartidaMultijugador = datosPartidaMultijugador;
}

void ControladorPartidas::confirmarInicioPartida(){
  Partida* nuevaPartida;
  if(datosPartidaMultijugador == NULL){
    nuevaPartida = new Individual(partidaAContinuar, contador);
  } else {
    nuevaPartida = new Multijugador(*datosPartidaMultijugador, contador);
  }
  videojuegoAIniciarPartida->agregarPartida(nuevaPartida);
  videojuegoAIniciarPartida = NULL;
  partidaAContinuar = NULL;
  delete datosPartidaMultijugador;
  datosPartidaMultijugador = NULL;
  contador++;
}


void ControladorPartidas::cancelarInicioPartida(){
  videojuegoAIniciarPartida = NULL;
  partidaAContinuar = NULL;
  if (datosPartidaMultijugador != NULL){
    delete datosPartidaMultijugador;
    datosPartidaMultijugador = NULL;
  }
}

set<DtPartida*> ControladorPartidas::obtenerMisPartidasSinFinalizar(){
  map<string,Videojuego*> coleccionVideojuegos = ControladorVideojuegos::getInstance()->getColeccionVideojuegos();
  set<DtPartida*> resultado;
  for (map<string,Videojuego*>::iterator vj = coleccionVideojuegos.begin(); vj != coleccionVideojuegos.end(); ++vj)  {
    Videojuego* videojuego = vj->second;
    set<DtPartida*> partidasDeVideojuegos = videojuego->obtenerMisPartidasSinFinalizar();
    for (set<DtPartida*>::iterator dt = partidasDeVideojuegos.begin(); dt != partidasDeVideojuegos.end(); ++dt)  {
      resultado.insert(*dt);
    }
  }
  return resultado;
}

void ControladorPartidas::finalizarPartida(int id){
  map<string,Videojuego*> coleccionVideojuegos = ControladorVideojuegos::getInstance()->getColeccionVideojuegos();
  Partida* partidaAFinalizar;
  for (map<string,Videojuego*>::iterator vj = coleccionVideojuegos.begin(); vj != coleccionVideojuegos.end(); ++vj)  {
    Videojuego* videojuego = vj->second;
    partidaAFinalizar = videojuego->obtenerPartida(id);
    if (partidaAFinalizar != NULL){
      break;
    }
  }
  partidaAFinalizar->finalizarPartida();
}

set<DtPartida*> ControladorPartidas::obtenerMisPartidasMultijugadorSinFinalizar(){
  map<string,Videojuego*> coleccionVideojuegos = ControladorVideojuegos::getInstance()->getColeccionVideojuegos();
  set<DtPartida*> resultado;
  for (map<string,Videojuego*>::iterator vj = coleccionVideojuegos.begin(); vj != coleccionVideojuegos.end(); ++vj)  {
    Videojuego* videojuego = vj->second;
    set<DtPartida*> partidasDeVideojuegos = videojuego->obtenerMisPartidasMultijugadorSinFinalizar();
    for (set<DtPartida*>::iterator dt = partidasDeVideojuegos.begin(); dt != partidasDeVideojuegos.end(); ++dt)  {
      resultado.insert(*dt);
    }
  }
  return resultado;
}

void ControladorPartidas::abandonarPartida(string nombreVideojuego, int id){
  string jugadorLogueado = ControladorUsuarios::getInstance()->getNicknameUsuario();
  map<string,Videojuego*> coleccionVideojuegos = ControladorVideojuegos::getInstance()->getColeccionVideojuegos();
  Videojuego* videojuego = coleccionVideojuegos.find(nombreVideojuego)->second;
  Partida* partidaAAbandonar = videojuego->obtenerPartida(id);
  Multijugador* multijugadorAAbandonar = dynamic_cast<Multijugador*>(partidaAAbandonar);
  multijugadorAAbandonar->abandonarPartida(jugadorLogueado);
}

ControladorPartidas::~ControladorPartidas(){
  instancia = NULL;
}

