#ifndef Videojuego_H
#define Videojuego_H
#include <string>
#include <bits/stdc++.h>

#include "DtPartidaIndividual.h"
#include "ControladorUsuarios.h"
#include "DtVideojuegoAPublicar.h"
#include "DtVideojuegoAPuntuar.h"
#include "DtVideojuegoAMostrar.h"
#include "DtSuscripcionVideojuego.h"
#include "Puntua.h"
#include "Partida.h"
#include "RegistroSuscripcion.h"
#include "Desarrollador.h"
#include "EstadoSuscripcion.h"
#include "TipoPago.h"
#include "TipoSuscripcion.h"
#include "Categoria.h"
#include "ControladorUsuarios.h"
#include "Individual.h"

using namespace std;

class Videojuego {
	private:
		string nombre, descripcion;
		float costoMensual, costoTrimestral, costoAnual, costoVitalicio;
		map<int, Partida*> partidas;
		Desarrollador* desarrollador;
		set<Puntua*> puntajes;
		set<RegistroSuscripcion*> registrosSuscripcion;
		set<Categoria*> categorias;

	public:
		Videojuego(DtVideojuegoAPublicar datos);
		void agregarCategoria(Categoria* categoria);
		DtSuscripcionVideojuego* getDtSuscripcionVideojuego();
		EstadoSuscripcion getEstadoSuscripcion();
		void darDeAltaSuscripcion(TipoSuscripcion tipoSuscripcion, TipoPago tipoPago, EstadoSuscripcion estadoSuscripcion);
		bool estaSuscriptoJugadorLogueado();
		set<DtPartidaIndividual*> getPartidasIndividualesFinalizadas();
		set<string> obtenerJugadoresConSuscripcion();
		void agregarPartida(Partida* partida);
		set<DtPartida*> obtenerMisPartidasSinFinalizar();
		Partida* obtenerPartida(int id);
		bool desarrolladorEstaLogueado();
		bool tienePartidasSinFinalizar();
		float obtenerTotalHorasJugadas();
		int obtenerTotalJugadores();
		DtVideojuegoAPuntuar* obtenerDtVideojuegoAPuntuar();
		void asignarPuntaje(int puntaje);
		set<DtPartida*> obtenerMisPartidasMultijugadorSinFinalizar();
		DtVideojuegoAMostrar getDtVideojuegoAMostrar();
		string getNombre();
		string getDescripcion();
		float getCostoMensual();
		float getCostoTrimestral();
		float getCostoAnual();
		float getCostoVitalicio();
		map<int, Partida*> getPartidas();
		Desarrollador* getDesarrollador();
		set<Puntua*> getPuntajes();
		set<RegistroSuscripcion*> getRegistrosSuscripcion();
		set<Categoria*> getCategorias();
		void setNombre(string nombre);
		void setDescripcion(string descripcion);
		void setCostoMensual(float costoMensual);
		void setCostoTrimestral(float costoTrimestral);
		void setCostoAnual(float costoAnual);
		void setCostoVitalicio(float costoVitalicio);
		void setPartidas(map<int, Partida*> partidas);
		void setPuntajes(set<Puntua*> puntajes);
		void setRegistrosSuscripcion(set<RegistroSuscripcion*> registrosSuscripcion);
		void setCategorias(set<Categoria*> categorias);
		~Videojuego();
};

#endif
