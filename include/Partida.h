#ifndef Partida_H
#define Partida_H

#include <string>
#include "DtFechaHora.h"
#include "DtPartida.h"
#include "Jugador.h"

using namespace std;

class Partida {
	private:
		int id;
		DtFechaHora fechaComienzo;
		float duracion;
		Jugador* creador;

	public:
		Partida(int id);
		virtual DtPartida* getDtPartida(string nombreVideojuego) = 0;
		string getNicknameCreador();
		int getId();
		float getDuracion();
		void setDuracion(float duracion);
		DtFechaHora getFechaComienzo();
		virtual ~Partida();
		virtual float obtenerHorasJugadas() = 0;
		virtual void finalizarPartida() = 0;
};

#endif
