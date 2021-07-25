#ifndef IControladorVideojuegos_H
#define IControladorVideojuegos_H

#include <string>


#include "DtVideojuegoAPublicar.h"
#include "DtCategoria.h"
#include "DtSuscripcionVideojuego.h"
#include "DtEstadistica.h"
#include "EstadoSuscripcion.h"
#include "TipoSuscripcion.h"
#include "TipoPago.h"
#include "TipoCategoria.h"
#include "Videojuego.h"

using namespace std;

class IControladorVideojuegos {
	public:
		virtual set<string> obtenerNombresVideojuegos() = 0;
        virtual void ingresarDatosVideojuego(DtVideojuegoAPublicar) = 0;
        virtual set<DtCategoria*> obtenerCategoriasGenero() = 0;
        virtual void seleccionarGeneros(set<string>) = 0;
        virtual set<DtCategoria*> obtenerCategoriasPlataforma() = 0;
        virtual void seleccionarPlataformas(set<string>) = 0;
        virtual set<DtCategoria*> obtenerCategoriasOtro() = 0;
        virtual void seleccionarOtras(set<string>) = 0;
        virtual void confirmarAltaVideojuego() = 0;
        virtual void cancelarAltaVideojuego() = 0;
        virtual set<DtSuscripcionVideojuego*> obtenerSuscripciones() = 0;
        virtual EstadoSuscripcion obtenerEstadoActual(string) = 0;
        virtual void confirmarSuscripcion(TipoSuscripcion, TipoPago) = 0;
        virtual void cancelarSuscripcion() = 0;
        virtual set<string> obtenerVideojuegosEliminables() = 0;
        virtual void seleccionarVideojuegoAEliminar(string) = 0;
        virtual void confirmarEliminacion() = 0;
        virtual void cancelarEliminacion() = 0;
        virtual set<string> obtenerMisVideojuegosDesarrollados() = 0;
        virtual set<DtEstadistica*> obtenerEstadisticas(string) = 0;
        virtual set<string> obtenerCategorias() = 0;
        virtual void ingresarDatosCategoria(string nombre, string descripcion, TipoCategoria tipo) = 0;
        virtual void confirmarAgregarCategoria() = 0;
		virtual void cancelarAgregarCategoria() = 0;
        virtual set<DtVideojuegoAPuntuar*> obtenerDtVideojuegos() = 0;
        virtual void asignarPuntaje(string videojuego, int puntaje) = 0;
        virtual DtVideojuegoAMostrar obtenerDtVideojuego(string nombre) = 0;
        virtual set<DtEstadistica*> obtenerEstadisticasDelSistema() = 0;
		virtual void seleccionarEstadisticas(set<string> nombres) = 0;
        virtual ~IControladorVideojuegos() {}
};

#endif
