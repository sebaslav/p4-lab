#include "../include/ControladorUsuarios.h"
using namespace std;

ControladorUsuarios* ControladorUsuarios::instancia = NULL;

ControladorUsuarios::ControladorUsuarios(){
	du = NULL;
	usuarioLogueado = NULL;
}
ControladorUsuarios* ControladorUsuarios::getInstance(){
	if(instancia == NULL)
		instancia = new ControladorUsuarios();
	return instancia;
}
bool ControladorUsuarios::nuevoIngreso(DtUsuario* datos){
	if (du != NULL) {
		delete du;
		du = NULL;
	}
	bool e1 = (usuariosEnSistema.find(datos->getEmail()) != usuariosEnSistema.end());
	bool e2 = false;
	DtJugador* datosCasteados = dynamic_cast<DtJugador*>(datos);
	if(datosCasteados) //Si datos es DtJugador...
		e2 = (jugadoresEnSistema.find(datosCasteados->getNickname()) != jugadoresEnSistema.end());
	if(e1 || e2)
		return true;
	du = datos;
	return false;
}
void ControladorUsuarios::confirmarAltaUsuario(){
	Usuario* u;

	DtJugador* datosCasteados1 = dynamic_cast<DtJugador*>(du);
	if(datosCasteados1){
		Jugador* j = new Jugador(datosCasteados1);
		jugadoresEnSistema.insert({j->getNickname(), j});
		u = j;
	}

	DtDesarrollador* datosCasteados2 = dynamic_cast<DtDesarrollador*>(du);
	if(datosCasteados2)
		u = new Desarrollador(datosCasteados2);

	usuariosEnSistema.insert({du->getEmail(), u});
	delete du;
	du = NULL;
}
void ControladorUsuarios::cancelarAltaUsuario(){
	if (du != NULL) {
		delete du;
		du = NULL;
	}
}

Desarrollador* ControladorUsuarios::getDesarrollador(){
	Desarrollador* desarrollador = dynamic_cast<Desarrollador*>(usuarioLogueado);
	return desarrollador;
}
string ControladorUsuarios::getNicknameUsuario(){
	Jugador* jugador = dynamic_cast<Jugador*>(usuarioLogueado);
	return jugador->getNickname();
}
Jugador* ControladorUsuarios::getJugadorLogueado(){
	Jugador* jugador = dynamic_cast<Jugador*>(usuarioLogueado);
	return jugador;
}
Jugador* ControladorUsuarios::getJugador(string nickname){
	return jugadoresEnSistema.find(nickname)->second;
}
string ControladorUsuarios::getEmailUsuarioLogueado(){
	return usuarioLogueado->getEmail();
}
TipoInicioSesion ControladorUsuarios::iniciarSesion(DtUsuario infoUsuario){
	bool existeUsuario = (usuariosEnSistema.find(infoUsuario.getEmail()) != usuariosEnSistema.end());
	if(existeUsuario){
		Usuario* usuario = usuariosEnSistema.find(infoUsuario.getEmail())->second;
		string password = usuario->getContrasenia();
		if(infoUsuario.getContrasenia() == password) {
			usuarioLogueado = usuario;
			Jugador* jugador = dynamic_cast<Jugador*>(usuario);
			if (jugador)
				return TipoInicioSesion::SesionJugador;
			else
				return TipoInicioSesion::SesionDesarrollador;
		}
	}
	return TipoInicioSesion::SesionIncorrecta;
}

ControladorUsuarios::~ControladorUsuarios(){
	map<string, Usuario*>::iterator it;
    for(it = usuariosEnSistema.begin(); it != usuariosEnSistema.end(); ++it){
        delete it->second;
    }
	if(du != NULL){ delete du;}
	instancia = NULL;
}