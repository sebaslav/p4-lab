#ifndef Puntua_H
#define Puntua_H
#include <string>

#include "Jugador.h"

using namespace std;

class Puntua {

    private:
        int puntaje;
        Jugador* jugador;

	public:
		Puntua(int puntaje);
        int getPuntaje();
        void setPuntaje(int puntaje);
        string getNickname();
};

#endif
