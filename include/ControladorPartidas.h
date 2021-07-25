#ifndef ControladorPartidas_H
#define ControladorPartidas_H

#include <string>
#include <bits/stdc++.h>
#include "DtPartidaIndividual.h"
#include "DtPartidaMultijugador.h"
#include "Videojuego.h"
#include "IControladorPartidas.h"
#include "ControladorVideojuegos.h"
#include "Partida.h"
#include "Multijugador.h"
#include "Individual.h"


using namespace std;

class ControladorPartidas : public IControladorPartidas{
	private:
		static ControladorPartidas* instancia;
		Videojuego* videojuegoAIniciarPartida;
		Individual* partidaAContinuar;
		DtPartidaMultijugador* datosPartidaMultijugador;
		ControladorPartidas();
		int contador;

	public:
		static ControladorPartidas* getInstance();
		set<string> obtenerMisVideojuegos();
		void seleccionarVideojuego(string nombre);
		set<DtPartidaIndividual*> obtenerPartidasIndividualesFinalizadas();
		void seleccionarPartidaAContinuar(int id);
		set<string> obtenerJugadoresConSuscripcion();
		void ingresarDatosPartidaMultijugador(bool enVivo, set<string> participantes);
		void confirmarInicioPartida();
		void cancelarInicioPartida();
		set<DtPartida*> obtenerMisPartidasSinFinalizar();
		void finalizarPartida(int id);
		set<DtPartida*> obtenerMisPartidasMultijugadorSinFinalizar();
		void abandonarPartida(string nombreVideojuego, int id);
		int getContador();
		void setContador(int contador);
		virtual ~ControladorPartidas();
};

#endif
