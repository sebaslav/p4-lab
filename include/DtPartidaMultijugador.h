#ifndef DtPartidaMultijugador_H
#define DtPartidaMultijugador_H
#include <string>
#include <bits/stdc++.h>
#include "DtPartida.h"

using namespace std;

class DtPartidaMultijugador: public DtPartida{
    private:
		bool enVivo;
		set<string> participantes;
		string creador;

    public:
        DtPartidaMultijugador(int id, DtFechaHora fechaComienzo, string nombreVideojuego, float duracion, bool enVivo, set<string> participantes, string creador);
		~DtPartidaMultijugador();
		bool getEnVivo();
		set<string> getParticipantes();
		string getCreador();
};

#endif
