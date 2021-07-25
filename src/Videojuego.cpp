#include <string>
#include <bits/stdc++.h>

#include "../include/Videojuego.h"
#include "../include/DtPartidaMultijugador.h"

using namespace std;

Videojuego::Videojuego(DtVideojuegoAPublicar datos) {
    this->nombre = datos.getNombre();
    this->descripcion = datos.getDescripcion();
    this->costoMensual = datos.getCostoMensual();
    this->costoTrimestral = datos.getCostoTrimestral();
    this->costoAnual = datos.getCostoAnual();
    this->costoVitalicio = datos.getCostoVitalicio();
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    Desarrollador* desarrollador = controladorUsuarios->getDesarrollador();
    this->desarrollador = desarrollador;
}

void Videojuego::agregarCategoria(Categoria* categoria) {
    categorias.insert(categoria);
}

DtSuscripcionVideojuego* Videojuego::getDtSuscripcionVideojuego() {
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
    set<RegistroSuscripcion*>::iterator it;
    bool esActiva = false;
    for (it=registrosSuscripcion.begin(); it!=registrosSuscripcion.end();it++) {
        string nickSuscripcion = (*it)->getNicknameJugador();
        if (nickJugadorLogueado == nickSuscripcion) {
            esActiva = (*it)->getEsActiva();
            break;
        }
    }
    return new DtSuscripcionVideojuego(nombre, costoMensual, costoTrimestral, costoAnual, costoVitalicio, esActiva);
}

EstadoSuscripcion Videojuego::getEstadoSuscripcion() {
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
    set<RegistroSuscripcion*>::iterator it;
    EstadoSuscripcion estado = EstadoSuscripcion::Inexistente;
    for (it=registrosSuscripcion.begin(); it!=registrosSuscripcion.end();it++) {
        string nickSuscripcion = (*it)->getNicknameJugador();
        if (nickJugadorLogueado == nickSuscripcion) {
            estado = (*it)->getEstadoSuscripcion();
            break;
        }
    }
    return estado;
}

void Videojuego::darDeAltaSuscripcion(TipoSuscripcion tipoSuscripcion, TipoPago tipoPago, EstadoSuscripcion estadoSuscripcion) {
    float costo;
    switch (tipoSuscripcion) {
        case TipoSuscripcion::Mensual:
            costo = costoMensual;
            break;
        case TipoSuscripcion::Trimensual:
            costo = costoTrimestral;
            break;
        case TipoSuscripcion::Anual:
            costo = costoAnual;
            break;
        case TipoSuscripcion::Vitalicia:
            costo = costoVitalicio;
            break;
    }
    if (estadoSuscripcion == EstadoSuscripcion::Inexistente) {
        RegistroSuscripcion* nuevoRegistro = new RegistroSuscripcion(tipoSuscripcion, tipoPago, costo);
        registrosSuscripcion.insert(nuevoRegistro);
    } else {
        ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
        string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
        set<RegistroSuscripcion*>::iterator it;
        for (it=registrosSuscripcion.begin(); it!=registrosSuscripcion.end();it++) {
            string nickSuscripcion = (*it)->getNicknameJugador();
            if (nickJugadorLogueado == nickSuscripcion) {
                (*it)->darDeAltaSuscripcion(tipoSuscripcion, tipoPago, costo, estadoSuscripcion);
                break;
            }
        }
    }
}

bool Videojuego::estaSuscriptoJugadorLogueado() {
    bool estaSuscripto = false;
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
    set<RegistroSuscripcion*>::iterator it;
    for (it=registrosSuscripcion.begin(); it!=registrosSuscripcion.end();it++) {
        string nickSuscripcion = (*it)->getNicknameJugador();
        if (nickJugadorLogueado == nickSuscripcion) {
            estaSuscripto = (*it)->getEsActiva();
            break;
        }
    }
    return estaSuscripto;
}

set<DtPartidaIndividual*> Videojuego::getPartidasIndividualesFinalizadas() {
    set<DtPartidaIndividual*> datos;
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
    map<int, Partida*>::iterator it;
    for (it=partidas.begin(); it!=partidas.end();it++) {
        Individual* partidaIndividual = dynamic_cast<Individual*>(it->second);
        if (partidaIndividual) {
            string nickCreador = partidaIndividual->getNicknameCreador();
            if (nickCreador == nickJugadorLogueado) {
                float duracion = partidaIndividual->getDuracion();
                if (duracion != -1) {
                    DtPartida* dtPartida = partidaIndividual->getDtPartida(nombre);
                    DtPartidaIndividual* dtPartidaIndividual = dynamic_cast<DtPartidaIndividual*>(dtPartida);
                    datos.insert(dtPartidaIndividual);
                }
            }
        }
    }
    return datos;
}

set<string> Videojuego::obtenerJugadoresConSuscripcion() {
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
    set<string> nicknames;
    set<RegistroSuscripcion*>::iterator it;
    for (it=registrosSuscripcion.begin(); it!=registrosSuscripcion.end();it++) {
        if ((*it)->getEsActiva() && (nickJugadorLogueado != (*it)->getNicknameJugador())) {
            nicknames.insert((*it)->getNicknameJugador());
        }
    }
    return nicknames;
}

void Videojuego::agregarPartida(Partida* partida) {
    partidas.insert({partida->getId(), partida});
}

set<DtPartida*> Videojuego::obtenerMisPartidasSinFinalizar() {
    set<DtPartida*> datos;
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
    map<int, Partida*>::iterator it;
    for (it=partidas.begin(); it!=partidas.end();it++) {
        Partida* partida = it->second;
        string nickCreador = partida->getNicknameCreador();
        if (nickCreador == nickJugadorLogueado) {
            float duracion = partida->getDuracion();
            if (duracion == -1) {
                datos.insert(partida->getDtPartida(nombre));
            }
        }
    }
    return datos;
}

Partida* Videojuego::obtenerPartida(int id) {
    map<int, Partida*>::iterator it;
    it = partidas.find(id);
    if (it != partidas.end()) {
        return it->second;
    } else {
        return NULL;
    }
}

bool Videojuego::desarrolladorEstaLogueado() {
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string emailUsuarioLogueado = controladorUsuarios->getEmailUsuarioLogueado();
    return emailUsuarioLogueado == desarrollador->getEmail();
}

bool Videojuego::tienePartidasSinFinalizar() {
    map<int, Partida*>::iterator it;
    for (it=partidas.begin(); it!=partidas.end();it++) {
        Partida* partida = it->second;
        float duracion = partida->getDuracion();
        if (duracion == -1) {
            return true;
        }
    }
    return false;
}

float Videojuego::obtenerTotalHorasJugadas() {
    float total = 0;
    map<int, Partida*>::iterator it;
    for (it=partidas.begin(); it!=partidas.end();it++) {
        Partida* partida = it->second;
        total += partida->obtenerHorasJugadas();
    }
    return total;
}

int Videojuego::obtenerTotalJugadores() {
    return registrosSuscripcion.size();
}

DtVideojuegoAPuntuar* Videojuego::obtenerDtVideojuegoAPuntuar() {
    return new DtVideojuegoAPuntuar(nombre, descripcion);
}

void Videojuego::asignarPuntaje(int puntaje) {
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
    set<Puntua*>::iterator it;
    for (it=puntajes.begin(); it!=puntajes.end();it++) {
        string nickPuntua = (*it)->getNickname();
        if (nickJugadorLogueado == nickPuntua) {
            (*it)->setPuntaje(puntaje);
            return;
        }
    }
    if (it == puntajes.end()) {
        Puntua* nuevoPuntua = new Puntua(puntaje);
        puntajes.insert(nuevoPuntua);
    }
}

set<DtPartida*> Videojuego::obtenerMisPartidasMultijugadorSinFinalizar() {
    set<DtPartida*> res;
    ControladorUsuarios* controladorUsuarios = ControladorUsuarios::getInstance();
    string nickJugadorLogueado = controladorUsuarios->getNicknameUsuario();
    map<int, Partida*>::iterator it;
    for (it=partidas.begin(); it!=partidas.end();it++) {
        Partida* partida = it->second;
        float duracion = partida->getDuracion();
        if (duracion == -1) {
            DtPartida* dtPartida = partida->getDtPartida(nombre);
            DtPartidaMultijugador* dtPartidaMultijugador = dynamic_cast<DtPartidaMultijugador*>(dtPartida);
            if (dtPartidaMultijugador) {
                set<string> participantes = dtPartidaMultijugador->getParticipantes();
                set<string>::iterator itP;
                for (itP=participantes.begin(); itP!=participantes.end();itP++) {
                    if (nickJugadorLogueado == *itP) {
                        res.insert(dtPartida);
                        break;
                    }
                }
                if (itP != participantes.end()) {
                    continue;
                }
            }
            delete dtPartida;
        }
    }
    return res;
}

DtVideojuegoAMostrar Videojuego::getDtVideojuegoAMostrar() {
    string empresa = desarrollador->getEmpresa();
    set<string> nombresCategorias;
    set<Categoria*>::iterator it;
    for (it=categorias.begin(); it!=categorias.end();it++) {
        string nombreCategoria = (*it)->getNombre();
        nombresCategorias.insert(nombreCategoria);
    }
    float sumaPuntajes = 0;
    set<Puntua*>::iterator itP;
    for (itP=puntajes.begin(); itP!=puntajes.end();itP++) {
        sumaPuntajes += (*itP)->getPuntaje();
    }
    float puntajePromedio = 0;
    if (puntajes.size() > 0) {
        puntajePromedio = sumaPuntajes/puntajes.size();
    }
     
    float totalHorasJugadas = obtenerTotalHorasJugadas();

    return DtVideojuegoAMostrar(nombre, descripcion, empresa, nombresCategorias, costoMensual, costoTrimestral, costoAnual, costoVitalicio, puntajePromedio, totalHorasJugadas);
}

string Videojuego::getNombre() {
    return nombre;
}

string Videojuego::getDescripcion() {
    return descripcion;
}

float Videojuego::getCostoMensual() {
    return costoMensual;
}

float Videojuego::getCostoTrimestral() {
    return costoTrimestral;
}

float Videojuego::getCostoAnual() {
    return costoAnual;
}

float Videojuego::getCostoVitalicio() {
    return costoVitalicio;
}

map<int, Partida*> Videojuego::getPartidas() {
    return partidas;
}

Desarrollador* Videojuego::getDesarrollador() {
    return desarrollador;
}

set<Puntua*> Videojuego::getPuntajes() {
    return puntajes;
}

set<RegistroSuscripcion*> Videojuego::getRegistrosSuscripcion() {
    return registrosSuscripcion;
}

set<Categoria*> Videojuego::getCategorias() {
    return categorias;
}

void Videojuego::setNombre(string nombre) {
    this->nombre = nombre;
}

void Videojuego::setDescripcion(string descripcion) {
    this->descripcion = descripcion;
}

void Videojuego::setCostoMensual(float costoMensual) {
    this->costoMensual = costoMensual;
}

void Videojuego::setCostoTrimestral(float costoTrimestral) {
    this->costoTrimestral = costoTrimestral;
}

void Videojuego::setCostoAnual(float costoAnual) {
    this->costoAnual = costoAnual;
}

void Videojuego::setCostoVitalicio(float costoVitalicio) {
    this->costoVitalicio = costoVitalicio;
}

void Videojuego::setPartidas(map<int, Partida*> partidas) {
    this->partidas = partidas;
}


void Videojuego::setPuntajes(set<Puntua*> puntajes) {
    this->puntajes = puntajes;
}

void Videojuego::setRegistrosSuscripcion(set<RegistroSuscripcion*> registrosSuscripcion) {
    this->registrosSuscripcion = registrosSuscripcion;
}

void Videojuego::setCategorias(set<Categoria*> categorias) {
    this->categorias = categorias;
}

Videojuego::~Videojuego() {
    set<Puntua*>::iterator itPuntajes;
    for (itPuntajes=puntajes.begin(); itPuntajes!=puntajes.end();itPuntajes++) {
        delete (*itPuntajes);
    }
    set<RegistroSuscripcion*>::iterator itRegistros;
    for (itRegistros=registrosSuscripcion.begin(); itRegistros!=registrosSuscripcion.end();itRegistros++) {
        delete (*itRegistros);
    }
    map<int, Partida*>::iterator itPartidas;
    for (itPartidas=partidas.begin(); itPartidas!=partidas.end();itPartidas++) {
        delete itPartidas->second;
    }
}

