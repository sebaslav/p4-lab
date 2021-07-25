#ifndef IControladorPartidas_H
#define IControladorPartidas_H

#include <string>
#include <set>

#include "DtPartidaIndividual.h"
#include "DtPartida.h"
#include <bits/stdc++.h>

using namespace std;

class IControladorPartidas {
	public:
		virtual set<string> obtenerMisVideojuegos() = 0;
        virtual void seleccionarVideojuego(string) = 0;
        virtual set<DtPartidaIndividual*> obtenerPartidasIndividualesFinalizadas() = 0;
        virtual void seleccionarPartidaAContinuar(int) = 0;
        virtual set<string> obtenerJugadoresConSuscripcion() = 0;
        virtual void ingresarDatosPartidaMultijugador(bool, set<string>) = 0;
        virtual void confirmarInicioPartida() = 0;
        virtual void cancelarInicioPartida() = 0;
        virtual set<DtPartida*> obtenerMisPartidasSinFinalizar() = 0;
        virtual void finalizarPartida(int) = 0;
        virtual set<DtPartida*> obtenerMisPartidasMultijugadorSinFinalizar() = 0;
		virtual void abandonarPartida(string nombreVideojuego, int id) = 0;
        virtual ~IControladorPartidas() {}
};

#endif
