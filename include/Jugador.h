#ifndef Jugador_H
#define Jugador_H

#include "Usuario.h"
#include "DtJugador.h"
#include <string>

using namespace std;

class Jugador : public Usuario{
    private:
        string nickname, descripcion;
    public:
        Jugador(DtJugador* datos);
        ~Jugador();
        string getNickname();
        string getDescripcion();
};

#endif
