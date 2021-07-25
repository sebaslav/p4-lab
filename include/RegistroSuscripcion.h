#ifndef RegistroSuscripcion_H
#define RegistroSuscripcion_H
#include <string>
#include "ControladorUsuarios.h"
#include <bits/stdc++.h>
#include "Suscripcion.h"
#include "TipoSuscripcion.h"
#include "TipoPago.h"
#include "EstadoSuscripcion.h"
#include "Temporal.h"
#include "Vitalicia.h"

using namespace std;

class RegistroSuscripcion {
	private:
		Jugador* jug;
		set<Suscripcion*> suscripciones;
	public:
		RegistroSuscripcion(TipoSuscripcion tipoSuscripcion, TipoPago tipoPago, float costo);
		string getNicknameJugador();
		bool getEsActiva();
		EstadoSuscripcion getEstadoSuscripcion();
		void darDeAltaSuscripcion(TipoSuscripcion tipoSuscripcion, TipoPago tipoPago, float costo, EstadoSuscripcion estado);
		~RegistroSuscripcion();
};

#endif
