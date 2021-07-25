#ifndef ControladorVideojuegos_H
#define ControladorVideojuegos_H
#include <string>

#include "DtVideojuegoAPublicar.h"
#include "IControladorVideojuegos.h"
#include "Videojuego.h"
#include "Categoria.h"
#include "DtCategoria.h"
#include "TipoCategoria.h"
#include<bits/stdc++.h>


using namespace std;

class ControladorVideojuegos: public IControladorVideojuegos {
	private:
		static ControladorVideojuegos* instancia;
		DtVideojuegoAPublicar datos;
		EstadoSuscripcion estadoSuscripcion;
		map<string,Videojuego*> coleccionVideojuegos;
		Videojuego* videojuegoRecordado;
		map<string, Estadistica*> estadisticas;
		map<string,Categoria*> categoriasEnSistema;
		set<Categoria*> categoriasRecordadas;
		string nombreCategoria;
		string descripcionCategoria;
		TipoCategoria tipoCategoria;
		ControladorVideojuegos();
    public:
		static ControladorVideojuegos* getInstance();
		virtual ~ControladorVideojuegos();
		set<string> obtenerNombresVideojuegos();
		virtual void ingresarDatosVideojuego(DtVideojuegoAPublicar data);
		set<DtCategoria*> obtenerCategoriasGenero();
		void seleccionarGeneros(set<string> generos);
		set<DtCategoria*> obtenerCategoriasPlataforma();
		void seleccionarPlataformas(set<string> plataformas);
		set<DtCategoria*> obtenerCategoriasOtro();
		void seleccionarOtras(set<string> otras);
		void confirmarAltaVideojuego();
		void cancelarAltaVideojuego();
		set<DtSuscripcionVideojuego*> obtenerSuscripciones();
		EstadoSuscripcion obtenerEstadoActual(string nombre);
		void setEstado(EstadoSuscripcion estado);
		void setVideojuego(Videojuego* videojuego);
		void confirmarSuscripcion(TipoSuscripcion tipoSuscripcion, TipoPago tipoPago);
		void cancelarSuscripcion();
		Videojuego* getVideojuego(string nombre);
		set<string> obtenerVideojuegosEliminables();
		void seleccionarVideojuegoAEliminar(string nombre);
		void confirmarEliminacion();
		void cancelarEliminacion();
		set<string> obtenerMisVideojuegosDesarrollados();
		set<DtEstadistica*> obtenerEstadisticas(string nombreVideojuego);
		set<string> obtenerCategorias();
		void ingresarDatosCategoria(string nombre, string descripcion, TipoCategoria tipo);
		void confirmarAgregarCategoria();
		void cancelarAgregarCategoria();
		set<DtVideojuegoAPuntuar*> obtenerDtVideojuegos();
		void asignarPuntaje(string videojuego, int puntaje);
		//set<string> obtenerVideojuegos();
		map<string,Videojuego*> getColeccionVideojuegos();
		DtVideojuegoAMostrar obtenerDtVideojuego(string nombre);
		set<DtEstadistica*> obtenerEstadisticasDelSistema();
		void seleccionarEstadisticas(set<string> nombres);
};

#endif
