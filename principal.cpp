#include "include/Fabrica.h"
#include "include/IControladorVideojuegos.h"
#include "include/IControladorPartidas.h"
#include "include/IControladorUsuarios.h"
#include "include/FechaHoraSistema.h"
#include "include/DtPartidaMultijugador.h"

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//variables globales
IControladorUsuarios* controladorUsuarios;
IControladorVideojuegos* controladorVideojuegos;
IControladorPartidas* controladorPartidas;
FechaHoraSistema* fechaHoraSistema;
Fabrica* fabrica;

//forward declaration de procedimientos
void altaUsuario();
void iniciarSesion();
void sesionJugador();
void suscribirseAVideojuego();
void asignarPuntajeAVideojuego();
void iniciarPartida();
void iniciarPartidaIndividual();
void continuarPartidaAnterior();
void iniciarPartidaMultijugador();
void abandonarPartidaMultijugador();
void finalizarPartida();
void verInformacionDeVideojuego(TipoInicioSesion);
void sesionDesarrollador();
void agregarCategoria();
void publicarVideojuego();
void eliminarVideojuego();
void seleccionarEstadisticas();
void consultarEstadisticas();
void modificarFechaSistema();
void cargarDatosPrueba();
void liberarMemoria();
void init();
bool ingresarDatosJugador();
bool ingresarDatosDesarrollador();
int getNumero(int i, int j);

int main() {
    init(); //inicializa variables globales
    int opcion;
    cout << "\nBienvenido!\n";
    do {
        cout << "\nIngresar una opcion\n1. Alta de usuario\n2. Iniciar sesion\n3. Cargar datos de prueba\n4. Salir\n";
	opcion = getNumero(1,4);
	cout << endl;
        switch (opcion) {
            case 1:
                altaUsuario();
                break;
            case 2:
                iniciarSesion();
                break;
            case 3:
                cargarDatosPrueba();
                break;
            case 4:
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 4);
    liberarMemoria();
    cout << "\nGracias, vuelva pronto!\n";
    return 0;
}

void init() {
    fabrica = Fabrica::getInstance();
    controladorUsuarios = fabrica->getIUsuarios();
    controladorVideojuegos = fabrica->getIVideojuegos();
    controladorPartidas = fabrica->getIPartidas();
    fechaHoraSistema = FechaHoraSistema::getInstance();
    fechaHoraSistema->setFechaSistema(DtFechaHora(2021, 6, 21, 20, 0, 0)); //fecha de la defensa
}

void liberarMemoria() {
    delete fabrica;
    delete controladorVideojuegos;
    delete controladorPartidas;
    delete controladorUsuarios;
    delete fechaHoraSistema;
}

void altaUsuario() {
    bool repetido = false;
    int opcion;
    do {
        cout << "Ingresar tipo de usuario a dar de alta\n1. Jugador\n2. Desarrollador\n3. Cancelar operacion\n";
	opcion = getNumero(1,3);
	cout << endl;
        repetido = false;
        switch (opcion) {
            case 1:
                repetido = ingresarDatosJugador();
                if (repetido)
                     cout << "Email o nickname ingresados ya existen en el sistema. Intentelo nuevamente\n";
                break;
            case 2:
                repetido = ingresarDatosDesarrollador();
                if (repetido)
                     cout << "Email ingresado ya existe en el sistema. Intentelo nuevamente\n";
                break;
            case 3:
                controladorUsuarios->cancelarAltaUsuario();
                cout << "La operacion Alta de usuario fue cancelada\n";
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while ((opcion != 1 && opcion != 2 && opcion != 3) || repetido);
    if (opcion != 3 && !repetido) { //si es posible crear el usuario
        int confirma;
        do {
            cout << "Ingrese si quiere confirmar el alta de usuario\n1. Si\n2. No\n";
	    confirma = getNumero(1,2); 
	    cout << endl;
	    switch (confirma) {
                case 1:
                    controladorUsuarios->confirmarAltaUsuario();
                    cout << "El usuario se dio de alta correctamente\n";
                    break;
                case 2:
                    controladorUsuarios->cancelarAltaUsuario();
                    cout << "La operacion Alta de usuario fue cancelada\n";
                    break;
                default:
                    cout << endl;//"Por favor ingrese una opcion valida\n";
            }
        } while (confirma != 1 && confirma != 2);
    }
}

bool ingresarDatosJugador() {
    string email, contrasenia, nickname, descripcion;
    cout << "Ingresar email\n";
    getline(cin >> ws, email);
    cout << "Ingresar contrasenia\n";
    getline(cin >> ws, contrasenia);
    cout << "Ingresar nickname\n";
    getline(cin >> ws, nickname);
    cout << "Ingresar descripcion\n";
    getline(cin >> ws, descripcion);
    DtUsuario* dtUsuario = new DtJugador(email, contrasenia, nickname, descripcion);
    return controladorUsuarios->nuevoIngreso(dtUsuario);
}

bool ingresarDatosDesarrollador() {
    string email, contrasenia, empresa;
    cout << "Ingresar email\n";
    getline(cin >> ws, email);
    cout << "Ingresar contrasenia\n";
    getline(cin >> ws, contrasenia);
    cout << "Ingresar empresa\n";
    getline(cin >> ws, empresa);
    DtUsuario* dtUsuario = new DtDesarrollador(email, contrasenia, empresa);
    return controladorUsuarios->nuevoIngreso(dtUsuario);
}

void iniciarSesion() {
    int reintenta;
    string email, contrasenia;
    do {
        cout << "Ingrese el email\n";
        getline(cin >> ws, email);
        cout << "Ingrese la contrasenia\n";
        getline(cin >> ws, contrasenia);
        DtUsuario dtUsuario = DtUsuario(email, contrasenia);
        TipoInicioSesion sesion = controladorUsuarios->iniciarSesion(dtUsuario);
        if (sesion == TipoInicioSesion::SesionIncorrecta) {
            cout << "No se ha podido iniciar sesion con los datos ingresados\n";
            do {
                cout << "Quiere intentar iniciar sesion nuevamente?\n1. Si\n2. No\n";
                reintenta = getNumero(1,2);
                if (reintenta != 1 && reintenta != 2)
                    cout << endl;//"Por favor ingrese una opcion valida\n";
            } while (reintenta != 1 && reintenta != 2);
        } else { //se inicia sesion correctamente
            cout << "La sesion permanecera iniciada hasta que un nuevo usuario inicie sesion en el sistema\n";
            if (sesion == TipoInicioSesion::SesionJugador)
                sesionJugador();
            else
                sesionDesarrollador();
            return; //retorna al menu principal
        }
    } while (reintenta == 1);
}

void sesionJugador() {
    cout << "Se ha iniciado sesion como Jugador\n";
    int opcion;
    do {
        cout << "\nIngresar una opcion\n1. Suscribirse a videojuego\n2. Asignar puntaje a videojuego\n3. Iniciar partida\n4. Abandonar partida multijugador\n5. Finalizar partida\n6. Ver informacion de videojuego\n7. Modificar fecha del sistema\n8. Salir\n";
	opcion = getNumero(1,8);
	cout << endl;
        switch (opcion) {
            case 1:
                suscribirseAVideojuego();
                break;
            case 2:
                asignarPuntajeAVideojuego();
                break;
            case 3:
                iniciarPartida();
                break;
            case 4:
                abandonarPartidaMultijugador();
                break;
            case 5:
                finalizarPartida();
                break;
            case 6:
                verInformacionDeVideojuego(TipoInicioSesion::SesionJugador);
                break;
            case 7:
                modificarFechaSistema();
                break;
            case 8:
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 8);
}

void suscribirseAVideojuego() {
    set<DtSuscripcionVideojuego*> dtSuscripciones = controladorVideojuegos->obtenerSuscripciones();
    set<DtSuscripcionVideojuego*>::iterator it;
    if (dtSuscripciones.size() == 0) {
        cout << "\nNo hay videojuegos en el sistema\n";
        return;
    }
    cout << "Videojuegos con el que el jugador tiene suscripcion activa:\n\n";
    for (it=dtSuscripciones.begin(); it!=dtSuscripciones.end();it++) {
        if ((*it)->getEsActiva()) {
            cout << *(*it);
        }
    }
    cout << "Videojuegos con el que el jugador no tiene suscripcion activa:\n\n";
    for (it=dtSuscripciones.begin(); it!=dtSuscripciones.end();it++) {
        if (!(*it)->getEsActiva()) {
            cout << *(*it);
        }
    }
    string nombre;
    bool pertenece = false;
    do {
        cout << "Ingrese el nombre del videojuego al cual suscribirse\n";
        getline(cin >> ws, nombre);
        for (it=dtSuscripciones.begin(); it!=dtSuscripciones.end();it++) {
            if (nombre == (*it)->getVideojuego()) {
                pertenece = true;
                break;
            }
        }
        if (!pertenece)
            cout << "No existe un videojuego con ese nombre. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    EstadoSuscripcion estado = controladorVideojuegos->obtenerEstadoActual(nombre);
    if (estado == EstadoSuscripcion::Vitalicia) {
        cout << "El jugador ya cuenta con una suscripcion vitalicia a este videojuego\n";
        controladorVideojuegos->cancelarSuscripcion();
        return;
    }
    if (estado == EstadoSuscripcion::Temporal) {
        cout << "Ya se cuenta con una suscripcion temporal activa a este videojuego\n";
        int cancelaAnterior;
        cout << "Quiere cancelar la suscripcion actual?\n1. Si\n2. No\n";
	cancelaAnterior = getNumero(1,2);
        if (cancelaAnterior == 2) {
            controladorVideojuegos->cancelarSuscripcion();
            return;
        } 
    }
    TipoSuscripcion tipoSuscripcion;
    int tipoS;
    do {
        cout << "Ingrese el tipo de suscripcion que desea contratar\n1. Mensual\n2. Trimestral\n3. Anual\n4. Vitalicia\n";
	tipoS = getNumero(1,4);
        switch (tipoS) {
            case 1:
                tipoSuscripcion = TipoSuscripcion::Mensual;
                break;
            case 2:
                tipoSuscripcion = TipoSuscripcion::Trimensual;
                break;
            case 3:
                tipoSuscripcion = TipoSuscripcion::Anual;
                break;
            case 4:
                tipoSuscripcion = TipoSuscripcion::Vitalicia;
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (tipoS != 1 && tipoS != 2 && tipoS != 3 && tipoS != 4);
    TipoPago tipoPago;
    int tipoP;
    do {
        cout << "Ingrese el metodo de pago\n1. Tarjeta\n2. Paypal\n";
	tipoP = getNumero(1,2);
        switch (tipoP) {
            case 1:
                tipoPago = TipoPago::Tarjeta;
                break;
            case 2:
                tipoPago = TipoPago::Paypal;
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (tipoP != 1 && tipoP != 2);
    int confirma;
    do {
        cout << "Ingrese si quiere confirmar la suscripcion\n1. Si\n2. No\n";
	confirma = getNumero(1,2);
        switch (confirma) {
            case 1:
                controladorVideojuegos->confirmarSuscripcion(tipoSuscripcion, tipoPago);
                cout << "La suscripcion se realizo correctamente\n";
                break;
            case 2:
                controladorVideojuegos->cancelarSuscripcion();
                cout << "Se ha cancelado la operacion Suscribirse a videojuego\n";
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (confirma != 1 && confirma != 2);
    for (it=dtSuscripciones.begin(); it!=dtSuscripciones.end();it++) {
        delete (*it);
    }
}

void asignarPuntajeAVideojuego() {
    set<DtVideojuegoAPuntuar*> dtVideojuegosAPuntuar = controladorVideojuegos->obtenerDtVideojuegos();
    set<DtVideojuegoAPuntuar*>::iterator it;
    if (dtVideojuegosAPuntuar.size() == 0) {
        cout << "\nNo hay videojuegos en el sistema\n";
        return;
    }
    cout << "Videojuegos en el sistema:\n\n";
    for (it=dtVideojuegosAPuntuar.begin(); it!=dtVideojuegosAPuntuar.end();it++) {
        cout << *(*it);
    }
    string nombre;
    bool pertenece = false;
    do {
        cout << "Ingrese el nombre del videojuego que desea puntuar\n";
        getline(cin >> ws, nombre);
        for (it=dtVideojuegosAPuntuar.begin(); it!=dtVideojuegosAPuntuar.end();it++) {
            if (nombre == (*it)->getNombre()) {
                pertenece = true;
                break;
            }
        }
        if (!pertenece)
            cout << "No existe un videojuego con ese nombre. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    int puntaje;
    do {
        cout << "Ingrese el puntaje a asignar (numero entero del 1 al 5)\n";
	puntaje = getNumero(1,5);
        if (puntaje != 1 && puntaje != 2 && puntaje != 3 && puntaje != 4 && puntaje != 5) {
            cout << "El puntaje debe ser un numero entero entre 1 y 5. Por favor intentelo nuevamente\n";
        }
    } while (puntaje != 1 && puntaje != 2 && puntaje != 3 && puntaje != 4 && puntaje != 5);
    int puntajeConvertido = puntaje - 0;
    controladorVideojuegos->asignarPuntaje(nombre, puntajeConvertido);
    cout << "Se ha asignado el puntaje correctamente\n";
    for (it=dtVideojuegosAPuntuar.begin(); it!=dtVideojuegosAPuntuar.end();it++) {
        delete (*it);
    }
}

void iniciarPartida() {
    set<string> misVideojuegos = controladorPartidas->obtenerMisVideojuegos();
    set<string>::iterator it;
    if (misVideojuegos.size() == 0) {
        cout << "\nEl jugador no tiene suscripcion activa a ningun videojuego\n";
        return;
    }
    cout << "Videojuegos con los que el jugador tiene una suscripcion activa:\n\n";
    for (it=misVideojuegos.begin(); it!=misVideojuegos.end();it++) {
        cout << (*it) << "\n";
    }
    string nombreVideojuego;
    bool pertenece = false;
    do {
        cout << "Ingrese el nombre del videojuego en el que desea iniciar la partida\n";
        getline(cin >> ws, nombreVideojuego);
        if (misVideojuegos.find(nombreVideojuego) != misVideojuegos.end()) {
            pertenece = true;
            controladorPartidas->seleccionarVideojuego(nombreVideojuego);
        }
        else
            cout << "El jugador no tiene una suscripcion activa a un videojuego con ese nombre. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    int tipoPartida;
    int cantidadDeJugadoresConSuscripcion = controladorPartidas->obtenerJugadoresConSuscripcion().size();
    do {
        cout << "Ingrese el tipo de partida que desea iniciar\n1. Individual\n2. Multijugador (Debe haber por lo menos un jugador con suscripcion activa al videojuego)\n";
	tipoPartida = getNumero(1,2);
        switch (tipoPartida) {
            case 1:
                iniciarPartidaIndividual();
                break;
            case 2:
                if(cantidadDeJugadoresConSuscripcion > 0){
                    iniciarPartidaMultijugador();
                } else {
                    cout << "No hay otros jugadores con suscripcion activa para unirse a una partida multijugador\n";
                }
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (tipoPartida != 1 && (tipoPartida != 2 || cantidadDeJugadoresConSuscripcion == 0));
    int confirma;
    do {
        cout << "Ingrese si quiere confirmar el inicio de la partida\n1. Si\n2. No\n";
	confirma = getNumero(1,2);
        switch (confirma) {
            case 1:
                controladorPartidas->confirmarInicioPartida();
                cout << "La partida fue iniciada correctamente\n";
                break;
            case 2:
                controladorPartidas->cancelarInicioPartida();
                cout << "Se ha cancelado la operacion Iniciar partida\n";
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (confirma != 1 && confirma != 2);
}

void iniciarPartidaIndividual() {
    int continua;
    set<DtPartidaIndividual*> dtPartInd = controladorPartidas->obtenerPartidasIndividualesFinalizadas();
    if (dtPartInd.size() > 0){
        do {
            cout << "Ingrese si se desea continuar una partida anterior\n1. Si\n2. No\n";
	    continua = getNumero(1,2);
            switch (continua) {
                case 1:
                    continuarPartidaAnterior();
                    break;
                case 2:
                    break;
                default:
                    cout << endl;//"Por favor ingrese una opcion valida\n";
            }
        } while (continua != 1 && continua != 2);
        set<DtPartidaIndividual*>::iterator it;
        for (it=dtPartInd.begin(); it!=dtPartInd.end();it++) {
            delete (*it);
        }
    }
}

void continuarPartidaAnterior() {
    set<DtPartidaIndividual*> dtPartInd = controladorPartidas->obtenerPartidasIndividualesFinalizadas();
    set<DtPartidaIndividual*>::iterator it;
    cout << "Partidas individuales ya finalizadas, creadas por el jugador:\n\n";
    //falta ordenar cronologicamente las partidas al mostrarlas
    for (it=dtPartInd.begin(); it!=dtPartInd.end();it++) {
        cout << "Id: " << (*it)->getId() << "\n";
        cout << "Fecha y hora de comienzo: " << (*it)->getFechaComienzo() << "\n";
        cout << "Duracion: " << (*it)->getDuracion() << "\n\n";
    }
    int id;
    bool pertenece = false;
    do {
        cout << "Ingresar identificador de la partida que se desea continuar\n";
	id = getNumero(0,-1);
        for (it=dtPartInd.begin(); it!=dtPartInd.end();it++) {
            if (id == (*it)->getId()) {
                controladorPartidas->seleccionarPartidaAContinuar(id);
                pertenece = true;
                break;
            }
        }
        if (!pertenece)
            cout << "El identificador no es correcto. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    for (it=dtPartInd.begin(); it!=dtPartInd.end();it++) {
        delete (*it);
    }
}

void iniciarPartidaMultijugador() {
    set<string> jugadoresSuscritos = controladorPartidas->obtenerJugadoresConSuscripcion();
    int transmitir;
    bool enVivo;
    do {
        cout << "Ingrese si se desea que la partida se transmita en vivo\n1. Si\n2. No\n";
	transmitir = getNumero(1,2);
        switch (transmitir) {
            case 1:
                enVivo = true;
                break;
            case 2:
                enVivo = false;
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (transmitir != 1 && transmitir != 2);
    set<string>::iterator it;
    set<string> jugadoresUnidos;
    cout << "Jugadores con suscripcion activa al videojuego que pueden unirse:\n\n";
    for (it=jugadoresSuscritos.begin(); it!=jugadoresSuscritos.end();it++) {
        cout << (*it) << "\n";
    }
    string nickJugadorAUnirse;
    bool pertenece = false;
    do {
        cout << "Ingrese el nickname de un jugador a unirse\n";
        getline(cin >> ws, nickJugadorAUnirse);
        if (jugadoresSuscritos.find(nickJugadorAUnirse) != jugadoresSuscritos.end()) {
            pertenece = true;
            jugadoresUnidos.insert(nickJugadorAUnirse);
        } else {
            cout << "No puede unirse a la partida un jugador con ese nickname. Por favor intentelo nuevamente\n";
        }
    } while (!pertenece);
    int opcion;
    do {
        cout << "Desea seleccionar otro jugador para unirse a la partida?\n1. Si\n2. No\n";
	opcion = getNumero(1,2);
	cout << endl;
        switch (opcion) {
            case 1:
                cout << "Ingrese el nickname del jugador a unirse\n";
                getline(cin >> ws, nickJugadorAUnirse);
                if (jugadoresUnidos.find(nickJugadorAUnirse) != jugadoresUnidos.end()) {
                    cout << "Este jugador ya fue seleccionado\n";
                    break;
                }
                if (jugadoresSuscritos.find(nickJugadorAUnirse) != jugadoresSuscritos.end()) {
                    jugadoresUnidos.insert(nickJugadorAUnirse);
                } else {
                    cout << "No puede unirse a la partida un jugador con ese nickname. Por favor intentelo nuevamente\n";
                }
                break;
            case 2:
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 2);
    controladorPartidas->ingresarDatosPartidaMultijugador(enVivo, jugadoresUnidos);
}

void abandonarPartidaMultijugador() {
    set<DtPartida*> dtPartidas = controladorPartidas->obtenerMisPartidasMultijugadorSinFinalizar();
    set<DtPartida*>::iterator it;
    if (dtPartidas.size() == 0) {
        cout << "\nNo hay partidas multijugador sin finalizar a las que el jugador este unido\n";
        return;
    }
    cout << "Partidas multijugador sin finalizar a las que el jugador esta unido:\n\n";
    for (it=dtPartidas.begin(); it!=dtPartidas.end();it++) {
        DtPartidaMultijugador* dtPartidaMultijugador = dynamic_cast<DtPartidaMultijugador*>((*it));
        cout << "Id: " << dtPartidaMultijugador->getId() << "\n";
        cout << "Fecha y hora de comienzo: " << dtPartidaMultijugador->getFechaComienzo() << "\n";
        cout << "Nombre del videojuego: " << dtPartidaMultijugador->getNombreVideojuego() << "\n";
        cout << "Transmitida en vivo: ";
        if (dtPartidaMultijugador->getEnVivo())
            cout << "Si\n";
        else
            cout << "No\n";
        cout << "Nickname del creador: " << dtPartidaMultijugador->getCreador() << "\n";
        cout << "Nicknames de los participantes unidos a la partida:\n";
        set<string> participantes = dtPartidaMultijugador->getParticipantes();
        set<string>::iterator itNicks;
        for (itNicks=participantes.begin(); itNicks!=participantes.end();itNicks++) {
            cout << (*itNicks) << "\n";
        }
        cout << "\n";
    }
    int id;
    string nombreVideojuego;
    bool pertenece = false;
    do {
        cout << "Ingresar identificador de la partida que se desea abandonar\n";
	id = getNumero(0,-1);
        for (it=dtPartidas.begin(); it!=dtPartidas.end();it++) {
            if (id == (*it)->getId()) {
                pertenece = true;
                nombreVideojuego = (*it)->getNombreVideojuego();
                break;
            }
        }
        if (!pertenece)
            cout << "El identificador no es correcto. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    for (it=dtPartidas.begin(); it!=dtPartidas.end();it++) {
        delete (*it);
    }
    controladorPartidas->abandonarPartida(nombreVideojuego, id);
    cout << "La partida fue abandonada correctamente\n";
}

void finalizarPartida() {
    set<DtPartida*> dtPartidas = controladorPartidas->obtenerMisPartidasSinFinalizar();
    set<DtPartida*>::iterator it;
    if (dtPartidas.size() == 0) {
        cout << "\nNo hay partidas iniciadas por el jugador que esten sin finalizar\n";
        return;
    }
    cout << "Partidas iniciadas por el jugador que esten sin finalizar:\n\n";
    for (it=dtPartidas.begin(); it!=dtPartidas.end();it++) {
        cout << "Id: " << (*it)->getId() << "\n";
        cout << "Fecha y hora de comienzo: " << (*it)->getFechaComienzo() << "\n";
        cout << "Nombre del videojuego: " << (*it)->getNombreVideojuego() << "\n";
        DtPartidaMultijugador* dtPartidaMultijugador = dynamic_cast<DtPartidaMultijugador*>((*it));
        if (dtPartidaMultijugador) {
            cout << "Transmitida en vivo: ";
            if (dtPartidaMultijugador->getEnVivo())
                cout << "Si\n";
            else
                cout << "No\n";
            cout << "Nickname del creador: " << dtPartidaMultijugador->getCreador() << "\n";
            cout << "Nicknames de los participantes unidos a la partida:\n";
            set<string> participantes = dtPartidaMultijugador->getParticipantes();
            set<string>::iterator itNicks;
            for (itNicks=participantes.begin(); itNicks!=participantes.end();itNicks++) {
                cout << (*itNicks) << "\n";
            }
        } else {
            DtPartidaIndividual* dtPartidaIndividual = dynamic_cast<DtPartidaIndividual*>((*it));
            cout << "Es continuacion de una partida anterior: ";
            if (dtPartidaIndividual->getContinuacion())
                cout << "Si\n";
            else
                cout << "No\n";
        }
        cout << "\n";
    }
    int id;
    bool pertenece = false;
    do {
        cout << "Ingresar identificador de la partida que se desea finalizar\n";
	id = getNumero(0,-1);
        for (it=dtPartidas.begin(); it!=dtPartidas.end();it++) {
            if (id == (*it)->getId()) {
                pertenece = true;
                break;
            }
        }
        if (!pertenece)
            cout << "El identificador no es correcto. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    for (it=dtPartidas.begin(); it!=dtPartidas.end();it++) {
        delete (*it);
    }
    controladorPartidas->finalizarPartida(id);
    cout << "La partida fue finalizada correctamente\n";
}

void verInformacionDeVideojuego(TipoInicioSesion sesion) {
    set<string> videojuegos = controladorVideojuegos->obtenerNombresVideojuegos();
    set<string>::iterator it;
    if (videojuegos.size() == 0) {
        cout << "\nNo hay videojuegos en el sistema\n";
        return;
    }
    cout << "Videojuegos en el sistema:\n\n";
    for (it=videojuegos.begin(); it!=videojuegos.end();it++) {
        cout << (*it) << "\n";
    }
    string nombre;
    bool pertenece = false;
    do {
        cout << "Ingrese el nombre del videojuego cuya informacion desea ver\n";
        getline(cin >> ws, nombre);
        if (videojuegos.find(nombre) != videojuegos.end())
            pertenece = true;
        else
            cout << "No existe un videojuego con ese nombre. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    DtVideojuegoAMostrar dtVideojuego = controladorVideojuegos->obtenerDtVideojuego(nombre);
    cout << dtVideojuego; //imprime toda la informacion del datatype menos el total de horas jugadas
    if (sesion == TipoInicioSesion::SesionDesarrollador)
        cout << "Total de horas jugadas al videojuego: " << dtVideojuego.getTotalHorasJugadas() << "\n";
}

void sesionDesarrollador() {
    cout << "Se ha iniciado sesion como Desarrollador\n";
    int opcion;
    do {
        cout << "\nIngresar una opcion\n1. Agregar categoria\n2. Publicar videojuego\n3. Eliminar videojuego\n4. Seleccionar estadisticas\n5. Consultar estadisticas\n6. Ver informacion de videojuego\n7. Modificar fecha del sistema\n8. Salir\n";
	opcion = getNumero(1,8);
	cout << endl;
        switch (opcion) {
            case 1:
                agregarCategoria();
                break;
            case 2:
                publicarVideojuego();
                break;
            case 3:
                eliminarVideojuego();
                break;
            case 4:
                seleccionarEstadisticas();
                break;
            case 5:
                consultarEstadisticas();
                break;
            case 6:
                verInformacionDeVideojuego(TipoInicioSesion::SesionDesarrollador);
                break;
            case 7:
                modificarFechaSistema();
                break;
            case 8:
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 8);
}

void agregarCategoria() {
    set<string> categorias = controladorVideojuegos->obtenerCategorias();
    set<string>::iterator it;
    cout << "Categorias en el sistema:\n\n";
    for (it=categorias.begin(); it!=categorias.end();it++) {
        cout << (*it) << "\n";
    }
    string nombre;
    bool yaExiste = true;
    do {
        cout << "Ingrese el nombre de la nueva categoria\n";
        getline(cin >> ws, nombre);
        if (categorias.find(nombre) == categorias.end())
            yaExiste = false;
        else
            cout << "Ya existe una categoria con ese nombre. Por favor intentelo nuevamente\n";
    } while (yaExiste);
    string descripcion;
    cout << "Ingrese la descripcion de la nueva categoria\n";
    getline(cin >> ws, descripcion);
    TipoCategoria tipoCategoria;
    int opcion;
    do {
        cout << "Ingresar tipo de la nueva categoria\n1. Genero\n2. Plataforma\n3. Otro\n";
	opcion = getNumero(1,3);
	cout << endl;
        switch (opcion) {
            case 1:
                tipoCategoria = TipoCategoria::genero;
                break;
            case 2:
                tipoCategoria = TipoCategoria::plataforma;
                break;
            case 3:
                tipoCategoria = TipoCategoria::otroTipo;
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 1 && opcion != 2 && opcion != 3);
    controladorVideojuegos->ingresarDatosCategoria(nombre, descripcion, tipoCategoria);
    int confirma;
    do {
        cout << "Ingrese si quiere confirmar la operacion\n1. Si\n2. No\n";
	confirma = getNumero(1,2);
        switch (confirma) {
            case 1:
                controladorVideojuegos->confirmarAgregarCategoria();
                cout << "La categoria fue agregada correctamente\n";
                break;
            case 2:
                controladorVideojuegos->cancelarAgregarCategoria();
                cout << "Se ha cancelado la operacion Agregar categoria\n";
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (confirma != 1 && confirma != 2);
}

void publicarVideojuego() {
    set<DtCategoria*>::iterator itCats;
    set<DtCategoria*> dtCategorias = controladorVideojuegos->obtenerCategoriasGenero();
    if (dtCategorias.size() == 0) {
        cout << "\nDebe haber al menos una categoria de genero en el sistema para publicar un videojuego\n";
        return;
    }
    for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
        delete (*itCats);
    }
    dtCategorias = controladorVideojuegos->obtenerCategoriasPlataforma();
    if (dtCategorias.size() == 0) {
        cout << "\nDebe haber al menos una categoria de plataforma en el sistema para publicar un videojuego\n";
        return;
    }
    for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
        delete (*itCats);
    }

    set<string> videojuegos = controladorVideojuegos->obtenerNombresVideojuegos();
    set<string>::iterator it;
    cout << "Videojuegos en el sistema:\n\n";
    for (it=videojuegos.begin(); it!=videojuegos.end();it++) {
        cout << (*it) << "\n";
    }
    string nombre, descripcion;
    float costoMensual, costoTrimestral, costoAnual, costoVitalicio;
    bool yaExiste = true;
    do {
        cout << "\nIngrese el nombre del nuevo videojuego\n";
        getline(cin >> ws, nombre);
        if (videojuegos.find(nombre) == videojuegos.end())
            yaExiste = false;
        else
            cout << "Ya existe un videojuego con ese nombre. Por favor intentelo nuevamente\n";
    } while (yaExiste);
    cout << "Ingrese la descripcion del nuevo videojuego\n";
    getline(cin >> ws, descripcion);
    cout << "Ingrese el costo mensual del nuevo videojuego\n";
    costoMensual = getNumero(0,-1);
    cout << "Ingrese el costo trimestral del nuevo videojuego\n";
    costoTrimestral = getNumero(0,-1);
    cout << "Ingrese el costo anual del nuevo videojuego\n";
    costoAnual = getNumero(0,-1);
    cout << "Ingrese el costo vitalicio del nuevo videojuego\n";
    costoVitalicio = getNumero(0,-1);
    DtVideojuegoAPublicar dtVideojuegoAPublicar = DtVideojuegoAPublicar(nombre, descripcion, costoMensual, costoTrimestral, costoAnual, costoVitalicio);
    controladorVideojuegos->ingresarDatosVideojuego(dtVideojuegoAPublicar);
    //seleccion de categorias de genero
    dtCategorias = controladorVideojuegos->obtenerCategoriasGenero();
    cout << "Categorias de genero en el sistema:\n\n";
    for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
        cout << *(*itCats);
    }
    set<string> generos;
    string nombreCategoria;
    bool pertenece = false;
    do {
        cout << "Ingrese el nombre de una categoria de genero a seleccionar para este videojuego\n";
        getline(cin >> ws, nombreCategoria);
        for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
            if (nombreCategoria == (*itCats)->getNombre()) {
                pertenece = true;
                generos.insert(nombreCategoria);
                break;
            }
        }
        if (!pertenece)
            cout << "No existe una categoria de genero con ese nombre. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    int opcion;
    do {
        cout << "Desea seleccionar otra categoria de genero para este videojuego?\n1. Si\n2. No\n";
        opcion = getNumero(1,2);
	cout << endl;
        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre de otra categoria de genero a seleccionar para este videojuego\n";
                getline(cin >> ws, nombreCategoria);
                if (generos.find(nombreCategoria) != generos.end()) {
                    cout << "Esta categoria ya fue seleccionada\n";
                    break;
                }
                pertenece = false;
                for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
                    if (nombreCategoria == (*itCats)->getNombre()) {
                        pertenece = true;
                        generos.insert(nombreCategoria);
                        break;
                    }
                }
                if (!pertenece)
                    cout << "No existe una categoria de genero con ese nombre. Por favor intentelo nuevamente\n";
                break;
            case 2:
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 2);
    controladorVideojuegos->seleccionarGeneros(generos);
    for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
        delete (*itCats);
    }
    //repito para categorias de plataforma
    dtCategorias = controladorVideojuegos->obtenerCategoriasPlataforma();
    cout << "Categorias de plataforma en el sistema:\n\n";
    for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
        cout << *(*itCats);
    }
    set<string> plataformas;
    pertenece = false;
    do {
        cout << "Ingrese el nombre de una categoria de plataforma a seleccionar para este videojuego\n";
        getline(cin >> ws, nombreCategoria);
        for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
            if (nombreCategoria == (*itCats)->getNombre()) {
                pertenece = true;
                plataformas.insert(nombreCategoria);
                break;
            }
        }
        if (!pertenece)
            cout << "No existe una categoria de plataforma con ese nombre. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    do {
        cout << "Desea seleccionar otra categoria de plataforma para este videojuego?\n1. Si\n2. No\n";
        opcion = getNumero(1,2);
	cout << endl;
        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre de otra categoria de plataforma a seleccionar para este videojuego\n";
                getline(cin >> ws, nombreCategoria);
                if (plataformas.find(nombreCategoria) != plataformas.end()) {
                    cout << "Esta categoria ya fue seleccionada\n";
                    break;
                }
                pertenece = false;
                for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
                    if (nombreCategoria == (*itCats)->getNombre()) {
                        pertenece = true;
                        plataformas.insert(nombreCategoria);
                        break;
                    }
                }
                if (!pertenece)
                    cout << "No existe una categoria de plataforma con ese nombre. Por favor intentelo nuevamente\n";
                break;
            case 2:
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 2);
    controladorVideojuegos->seleccionarPlataformas(plataformas);
    for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
        delete (*itCats);
    }
    //analogo para otras categorias
    dtCategorias = controladorVideojuegos->obtenerCategoriasOtro();
    cout << "Otras categorias en el sistema:\n\n";
    for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
        cout << *(*itCats);
    }
    set<string> otras;
    do {
        cout << "Desea seleccionar otra categoria para este videojuego?\n1. Si\n2. No\n";
        opcion = getNumero(1,2);
	cout << endl;
        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre de la categoria a seleccionar para este videojuego\n";
                getline(cin >> ws, nombreCategoria);
                if (otras.find(nombreCategoria) != otras.end()) {
                    cout << "Esta categoria ya fue seleccionada\n";
                    break;
                }
                pertenece = false;
                for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
                    if (nombreCategoria == (*itCats)->getNombre()) {
                        pertenece = true;
                        otras.insert(nombreCategoria);
                        break;
                    }
                }
                if (!pertenece)
                    cout << "No existe la categoria con ese nombre. Por favor intentelo nuevamente\n";
                break;
            case 2:
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 2);
    controladorVideojuegos->seleccionarOtras(otras);
    for (itCats=dtCategorias.begin(); itCats!=dtCategorias.end();itCats++) {
        delete (*itCats);
    }
    //despliego informacion del nuevo videojuego al usuario
    cout << "Informacion del videojuego a publicar:\n";
    cout << "Nombre: " + nombre + "\n";
    cout << "Descripcion: " + descripcion + "\n";
    cout << "Costo mensual: " << costoMensual << "\n";
    cout << "Costo trimestral: " << costoTrimestral << "\n";
    cout << "Costo anual: " << costoAnual << "\n";
    cout << "Costo vitalicio: " << costoVitalicio << "\n";
    cout << "Categorias de genero:\n";
    for (it=generos.begin(); it!=generos.end();it++) {
        cout << (*it) << "\n";
    }
    cout << "Categorias de plataforma:\n";
    for (it=plataformas.begin(); it!=plataformas.end();it++) {
        cout << (*it) << "\n";
    }
    cout << "Otras categorias:\n";
    for (it=otras.begin(); it!=otras.end();it++) {
        cout << (*it) << "\n";
    }
    int confirma;
    do {
        cout << "\nIngrese si quiere confirmar la publicacion del videojuego\n1. Si\n2. No\n";
        confirma = getNumero(1,2);
        switch (confirma) {
            case 1:
                controladorVideojuegos->confirmarAltaVideojuego();
                cout << "El videojuego fue dado de alta correctamente\n";
                break;
            case 2:
                controladorVideojuegos->cancelarAltaVideojuego();
                cout << "Se ha cancelado la operacion Alta de videojuego\n";
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (confirma != 1 && confirma != 2);
}

void eliminarVideojuego() {
    set<string> videojuegosEliminables = controladorVideojuegos->obtenerVideojuegosEliminables();
    set<string>::iterator it;
    if (videojuegosEliminables.size() == 0) {
        cout << "\nNo hay videojuegos que puedan ser eliminados por el desarrollador\n";
        return;
    }
    cout << "Videojuegos que pueden ser eliminados por el desarrollador:\n\n";
    for (it=videojuegosEliminables.begin(); it!=videojuegosEliminables.end();it++) {
        cout << (*it) << "\n";
    }
    cout << "\n";
    string nombreVideojuego;
    bool pertenece = false;
    do {
        cout << "Ingrese el nombre del videojuego que desea eliminar\n";
        getline(cin >> ws, nombreVideojuego);
        if (videojuegosEliminables.find(nombreVideojuego) != videojuegosEliminables.end()) {
            controladorVideojuegos->seleccionarVideojuegoAEliminar(nombreVideojuego);
            pertenece = true;
        }
        else
            cout << "No es posible eliminar un videojuego con ese nombre. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    int confirma;
    do {
        cout << "Ingrese si quiere confirmar la eliminacion del videojuego\n1. Si\n2. No\n";
        confirma = getNumero(1,2);
        switch (confirma) {
            case 1:
                controladorVideojuegos->confirmarEliminacion();
                cout << "El videojuego fue eliminado correctamente\n";
                break;
            case 2:
                controladorVideojuegos->cancelarEliminacion();
                cout << "Se ha cancelado la operacion Eliminar videojuego\n";
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (confirma != 1 && confirma != 2);
}

void seleccionarEstadisticas() {
    set<DtEstadistica*> dtEstadisticas = controladorVideojuegos->obtenerEstadisticasDelSistema();
    set<DtEstadistica*>::iterator it;
    cout << "Tipos de estadistica en el sistema:\n\n";
    for (it=dtEstadisticas.begin(); it!=dtEstadisticas.end();it++) {
        cout << "Nombre: " << (*it)->getNombre() << "\n";
        cout << "Descripcion: " << (*it)->getDescripcion() << "\n\n";
    }
    set<string> estadisticasSeleccionadas;
    string nombreEstadistica;
    int opcion;
    bool pertenece;
    do {
        if (estadisticasSeleccionadas.size() > 0)
            cout << "Desea seleccionar otra estadistica?\n1. Si\n2. No\n";
        else
            cout << "Desea seleccionar una estadistica?\n1. Si\n2. No\n";
        opcion = getNumero(1,2);
	cout << endl;
        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre de la estadistica a seleccionar\n";
                getline(cin >> ws, nombreEstadistica);
                if (estadisticasSeleccionadas.find(nombreEstadistica) != estadisticasSeleccionadas.end()) {
                    cout << "Esta estadistica ya fue seleccionada\n";
                    break;
                }
                pertenece = false;
                for (it=dtEstadisticas.begin(); it!=dtEstadisticas.end();it++) {
                    if (nombreEstadistica == (*it)->getNombre()) {
                        pertenece = true;
                        estadisticasSeleccionadas.insert(nombreEstadistica);
                    }
                }
                if (!pertenece)
                    cout << "No existe una estadistica con ese nombre. Por favor intentelo nuevamente\n";
                break;
            case 2:
                break;
            default:
                cout << endl;//"Por favor ingrese una opcion valida\n";
        }
    } while (opcion != 2);
    controladorVideojuegos->seleccionarEstadisticas(estadisticasSeleccionadas);
    cout << "La seleccion de estadisticas se realizo correctamente\n";
    for (it=dtEstadisticas.begin(); it!=dtEstadisticas.end();it++) {
        delete (*it);
    }
}

void consultarEstadisticas() {
    set<string> videojuegosDesarrollados = controladorVideojuegos->obtenerMisVideojuegosDesarrollados();
    set<string>::iterator it;
    if (videojuegosDesarrollados.size() == 0) {
        cout << "\nNo hay videojuegos publicados por el desarrollador\n";
        return;
    }
    cout << "Videojuegos publicados por el desarrollador:\n\n";
    for (it=videojuegosDesarrollados.begin(); it!=videojuegosDesarrollados.end();it++) {
        cout << (*it) << "\n";
    }
    cout << "\n";
    string nombreVideojuego;
    bool pertenece = false;
    do {
        cout << "Ingrese el nombre del videojuego cuyas estadisticas desea ver\n";
        getline(cin >> ws, nombreVideojuego);
        if (videojuegosDesarrollados.find(nombreVideojuego) != videojuegosDesarrollados.end())
            pertenece = true;
        else
            cout << "No existe un videojuego publicado por el desarrollador con ese nombre. Por favor intentelo nuevamente\n";
    } while (!pertenece);
    set<DtEstadistica*> dtEstadisticas = controladorVideojuegos->obtenerEstadisticas(nombreVideojuego);
    set<DtEstadistica*>::iterator itEst;
    if (dtEstadisticas.size() > 0) {
        cout << "\nEstadisticas del videojuego:\n";
        for (itEst=dtEstadisticas.begin(); itEst!=dtEstadisticas.end();itEst++) {
            cout << (*itEst)->getNombre() << ": " << (*itEst)->getValor() << "\n";
        }
        for (itEst=dtEstadisticas.begin(); itEst!=dtEstadisticas.end();itEst++) {
            delete (*itEst);
        }
    } else {
        cout << "\nNo hay estadisticas seleccionadas por el desarrollador\n";
    }
}

void modificarFechaSistema() {
    cout << "\nLa fecha actual es: " << fechaHoraSistema->getFechaSistema() << "\n";
    int anio, mes, dia, hora, minuto, segundo;
    cout << "Ingrese el anio: ";
    anio = getNumero(0,-1);
    cout << "Ingrese el mes: ";
    mes = getNumero(0,11); 
    cout << "Ingrese el dia: ";
    dia = getNumero(0,30);
    cout << "Ingrese la hora: ";
    hora = getNumero(0,59);
    cout << "Ingrese el minuto: ";
    minuto = getNumero(0,59);
    cout << "Ingrese el segundo: ";
    segundo = getNumero(0,59);
    DtFechaHora nuevaFecha = DtFechaHora(anio, mes, dia, hora, minuto, segundo);
    fechaHoraSistema->setFechaSistema(nuevaFecha);
    cout << "\nLa nueva fecha y hora es: " << nuevaFecha << "\n";
}

void cargarDatosPrueba() {
    //altas de desarrollador
    DtUsuario* dtNuevoUsuario;
    dtNuevoUsuario = new DtDesarrollador("ironhide@mail.com", "123", "Ironhide Game Studio");
    controladorUsuarios->nuevoIngreso(dtNuevoUsuario);
    controladorUsuarios->confirmarAltaUsuario();
    
    dtNuevoUsuario = new DtDesarrollador("epic@mail.com", "123", "Epic Games");
    controladorUsuarios->nuevoIngreso(dtNuevoUsuario);
    controladorUsuarios->confirmarAltaUsuario();
    
    dtNuevoUsuario = new DtDesarrollador("mojang@mail.com", "123", "Mojang Studios");
    controladorUsuarios->nuevoIngreso(dtNuevoUsuario);
    controladorUsuarios->confirmarAltaUsuario();
    
    dtNuevoUsuario = new DtDesarrollador("ea@mail.com", "123", "EA Sports");
    controladorUsuarios->nuevoIngreso(dtNuevoUsuario);
    controladorUsuarios->confirmarAltaUsuario();
    
    //altas de jugador
    dtNuevoUsuario = new DtJugador("gamer@mail.com", "123", "gamer", "Soy el jugador gamer");
    controladorUsuarios->nuevoIngreso(dtNuevoUsuario);
    controladorUsuarios->confirmarAltaUsuario();
    
    dtNuevoUsuario = new DtJugador("ari@mail.com", "123", "ari", "Soy la jugadora ari");
    controladorUsuarios->nuevoIngreso(dtNuevoUsuario);
    controladorUsuarios->confirmarAltaUsuario();
    
    dtNuevoUsuario = new DtJugador("ibai@mail.com", "123", "ibai", "Soy le jugadore ibai");
    controladorUsuarios->nuevoIngreso(dtNuevoUsuario);
    controladorUsuarios->confirmarAltaUsuario();
    
    dtNuevoUsuario = new DtJugador("camila@mail.com", "123", "camila", "Soy la jugadora camila");
    controladorUsuarios->nuevoIngreso(dtNuevoUsuario);
    controladorUsuarios->confirmarAltaUsuario();
    
    //altas de categoria
    controladorVideojuegos->ingresarDatosCategoria("PC", "PC master race", TipoCategoria::plataforma);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("PS4", "Soy mejor que la play 5", TipoCategoria::plataforma);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Xbox One", "One Xbox to rule them all", TipoCategoria::plataforma);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Deporte", "Sali a correr y hace deporte de verdad", TipoCategoria::genero);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Supervivencia", "Zombies y vampiresas de 2.9 metros de alto", TipoCategoria::genero);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Estrategia", "Conoce a tu enemigo, conocete a ti mismo", TipoCategoria::genero);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Teen", "Su contenido esta dirigido a jovenes de 13 anios en adelante", TipoCategoria::otroTipo);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("E", "Su contenido esta dirigido para todo publico", TipoCategoria::otroTipo);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Accion", "1. f. Ejercicio de la posibilidad de hacer (segun la RAE)", TipoCategoria::genero);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Aventura", "I'm going on an adventure!", TipoCategoria::genero);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Switch", "It's-a me Switch!", TipoCategoria::plataforma);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("Xbox X", "Sobredosis de equis", TipoCategoria::plataforma);
    controladorVideojuegos->confirmarAgregarCategoria();
    controladorVideojuegos->ingresarDatosCategoria("PS5", "Soy mejor que la play 4", TipoCategoria::plataforma);
    controladorVideojuegos->confirmarAgregarCategoria();
    
    //altas de videojuego
    DtVideojuegoAPublicar dtVideojuegoAPublicar;
    set<string> categorias;
    DtUsuario dtUsuario;
    dtUsuario = DtUsuario("ironhide@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    dtVideojuegoAPublicar = DtVideojuegoAPublicar("KingdomRush", "Made in Uruguay", 1, 2, 7, 14);
    controladorVideojuegos->ingresarDatosVideojuego(dtVideojuegoAPublicar);
    
    categorias.insert("Estrategia");
    controladorVideojuegos->seleccionarGeneros(categorias);
    categorias.clear();
    categorias.insert("PC");
    categorias.insert("PS4");
    controladorVideojuegos->seleccionarPlataformas(categorias);
    categorias.clear();
    categorias.insert("E");
    controladorVideojuegos->seleccionarOtras(categorias);
    categorias.clear();
    controladorVideojuegos->confirmarAltaVideojuego();
    
    dtUsuario = DtUsuario("epic@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    dtVideojuegoAPublicar = DtVideojuegoAPublicar("Fortnite", "FPS para prepuberes", 3, 8, 30, 60);
    controladorVideojuegos->ingresarDatosVideojuego(dtVideojuegoAPublicar);
    
    categorias.insert("Supervivencia");
    controladorVideojuegos->seleccionarGeneros(categorias);
    categorias.clear();
    categorias.insert("PC");
    categorias.insert("PS4");
    categorias.insert("Xbox One");
    controladorVideojuegos->seleccionarPlataformas(categorias);
    categorias.clear();
    categorias.insert("Teen");
    controladorVideojuegos->seleccionarOtras(categorias);
    categorias.clear();
    controladorVideojuegos->confirmarAltaVideojuego();

    dtUsuario = DtUsuario("mojang@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    dtVideojuegoAPublicar = DtVideojuegoAPublicar("Minecraft", "Cuna de los ninios rata", 2, 5, 20, 40);
    controladorVideojuegos->ingresarDatosVideojuego(dtVideojuegoAPublicar);
    
    categorias.insert("Supervivencia");
    controladorVideojuegos->seleccionarGeneros(categorias);
    categorias.clear();
    categorias.insert("PC");
    controladorVideojuegos->seleccionarPlataformas(categorias);
    categorias.clear();
    categorias.insert("E");
    controladorVideojuegos->seleccionarOtras(categorias);
    categorias.clear();
    controladorVideojuegos->confirmarAltaVideojuego();

    dtUsuario = DtUsuario("ea@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    dtVideojuegoAPublicar = DtVideojuegoAPublicar("FIFA 21", "Que novedad, hay un nuevo FIFA!", 3, 8, 28, 50);
    controladorVideojuegos->ingresarDatosVideojuego(dtVideojuegoAPublicar);
    
    categorias.insert("Deporte");
    controladorVideojuegos->seleccionarGeneros(categorias);
    categorias.clear();
    categorias.insert("PC");
    categorias.insert("PS4");
    categorias.insert("Xbox One");
    controladorVideojuegos->seleccionarPlataformas(categorias);
    categorias.clear();
    categorias.insert("E");
    controladorVideojuegos->seleccionarOtras(categorias);
    categorias.clear();
    controladorVideojuegos->confirmarAltaVideojuego();
    
    //altas de suscripcion
    DtFechaHora nuevaFechaHora;
    nuevaFechaHora = DtFechaHora(2021, 6, 1, 9, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    dtUsuario = DtUsuario("gamer@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    controladorVideojuegos->obtenerEstadoActual("KingdomRush");
    controladorVideojuegos->confirmarSuscripcion(TipoSuscripcion::Trimensual, TipoPago::Paypal);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 2, 11, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorVideojuegos->obtenerEstadoActual("Fortnite");
    controladorVideojuegos->confirmarSuscripcion(TipoSuscripcion::Trimensual, TipoPago::Tarjeta);

    nuevaFechaHora = DtFechaHora(2021, 6, 4, 9, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    dtUsuario = DtUsuario("ari@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    controladorVideojuegos->obtenerEstadoActual("Fortnite");
    controladorVideojuegos->confirmarSuscripcion(TipoSuscripcion::Mensual, TipoPago::Paypal);

    nuevaFechaHora = DtFechaHora(2021, 6, 11, 9, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorVideojuegos->obtenerEstadoActual("Minecraft");
    controladorVideojuegos->confirmarSuscripcion(TipoSuscripcion::Anual, TipoPago::Tarjeta);

    nuevaFechaHora = DtFechaHora(2021, 6, 3, 7, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    dtUsuario = DtUsuario("ibai@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    controladorVideojuegos->obtenerEstadoActual("Fortnite");
    controladorVideojuegos->confirmarSuscripcion(TipoSuscripcion::Mensual, TipoPago::Tarjeta);

    nuevaFechaHora = DtFechaHora(2020, 12, 21, 15, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorVideojuegos->obtenerEstadoActual("Minecraft");
    controladorVideojuegos->confirmarSuscripcion(TipoSuscripcion::Vitalicia, TipoPago::Tarjeta);
    
    //asignacion de puntajes
    dtUsuario = DtUsuario("gamer@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    controladorVideojuegos->asignarPuntaje("KingdomRush", 4);
    controladorVideojuegos->asignarPuntaje("Fortnite", 5);

    dtUsuario = DtUsuario("ari@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    controladorVideojuegos->asignarPuntaje("Fortnite", 5);
    controladorVideojuegos->asignarPuntaje("Minecraft", 3);
    
    //alta de partidas individuales
    dtUsuario = DtUsuario("gamer@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 2, 9, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->seleccionarVideojuego("KingdomRush");
    controladorPartidas->confirmarInicioPartida();
    nuevaFechaHora = DtFechaHora(2021, 6, 2, 10, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->finalizarPartida(1);

    nuevaFechaHora = DtFechaHora(2021, 6, 3, 15, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->seleccionarVideojuego("KingdomRush");
    controladorPartidas->seleccionarPartidaAContinuar(1);
    controladorPartidas->confirmarInicioPartida();
    nuevaFechaHora = DtFechaHora(2021, 6, 3, 16, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->finalizarPartida(2);

    dtUsuario = DtUsuario("ari@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 12, 16, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->seleccionarVideojuego("Minecraft");
    controladorPartidas->confirmarInicioPartida();
    
    //alta de partidas multijugador
    set<string> jugadoresAUnirse;
    dtUsuario = DtUsuario("gamer@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 5, 17, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->seleccionarVideojuego("Fortnite");
    jugadoresAUnirse.insert("ari");
    jugadoresAUnirse.insert("ibai");
    controladorPartidas->ingresarDatosPartidaMultijugador(true, jugadoresAUnirse);
    jugadoresAUnirse.clear();
    controladorPartidas->confirmarInicioPartida();
    dtUsuario = DtUsuario("ari@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 5, 18, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->abandonarPartida("Fortnite", 4);
    dtUsuario = DtUsuario("gamer@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 5, 19, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->finalizarPartida(4);

    nuevaFechaHora = DtFechaHora(2021, 6, 6, 17, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->seleccionarVideojuego("Fortnite");
    jugadoresAUnirse.insert("ari");
    jugadoresAUnirse.insert("ibai");
    controladorPartidas->ingresarDatosPartidaMultijugador(true, jugadoresAUnirse);
    jugadoresAUnirse.clear();
    controladorPartidas->confirmarInicioPartida();
    dtUsuario = DtUsuario("ari@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 6, 17, 30, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->abandonarPartida("Fortnite", 5);
    dtUsuario = DtUsuario("gamer@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 6, 19, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->finalizarPartida(5);

    dtUsuario = DtUsuario("ari@mail.com", "123");
    controladorUsuarios->iniciarSesion(dtUsuario);
    
    nuevaFechaHora = DtFechaHora(2021, 6, 12, 20, 0, 0);
    fechaHoraSistema->setFechaSistema(nuevaFechaHora);
    controladorPartidas->seleccionarVideojuego("Minecraft");
    jugadoresAUnirse.insert("ibai");
    controladorPartidas->ingresarDatosPartidaMultijugador(false, jugadoresAUnirse);
    jugadoresAUnirse.clear();
    controladorPartidas->confirmarInicioPartida();
    
    cout << "Datos cargados correctamente\n";
    
}

int getNumero(int i, int j){

	string opcion;
	bool op_valida = false;
	bool check;

	do{
		cin >> opcion;
		check = true;
		for(unsigned int i = 0; i < opcion.length(); i++){
			if(! isdigit(opcion[i])){
				check = false;
				continue;
			}
		}
		if(check){	
			stringstream ind(opcion);
			int xind = 0;
			ind >> xind;
			if(i == -1 and j == -1){
				op_valida = true;
			}else if(i == -1 and xind <= j){
				op_valida = true;
			}else if(i <= xind and j == -1){
				op_valida = true;
			}else if(i <= xind and xind <= j){
				op_valida = true;
			}
		}

		if(!op_valida){
			cout << "Por favor ingrese una opcion valida ..." << endl;
		}

	}while(!op_valida);
	stringstream res(opcion);
	int xres = 0;
	res >> xres;
	return xres;
};
