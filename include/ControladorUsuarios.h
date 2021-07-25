#ifndef ControladorUsuarios_H
#define ControladorUsuarios_H

#include "Jugador.h"
#include "Desarrollador.h"
#include "IControladorUsuarios.h"
#include "TipoInicioSesion.h"
#include <string>

using namespace std;

class ControladorUsuarios : public IControladorUsuarios{
    private:
		static ControladorUsuarios* instancia;
		DtUsuario* du;
		map<string,Usuario*> usuariosEnSistema; // <email,usuario>
		map<string,Jugador*> jugadoresEnSistema; // <nickname,usuario>
		Usuario* usuarioLogueado;
		ControladorUsuarios();

    public:
		static ControladorUsuarios* getInstance();
		bool nuevoIngreso(DtUsuario* datos);
		void confirmarAltaUsuario();
		void cancelarAltaUsuario();
		Desarrollador* getDesarrollador();
		string getNicknameUsuario();
		Jugador* getJugadorLogueado();
		Jugador* getJugador(string nickname);
		string getEmailUsuarioLogueado();
		TipoInicioSesion iniciarSesion(DtUsuario infoUsuario);
		virtual ~ControladorUsuarios();
};

#endif
