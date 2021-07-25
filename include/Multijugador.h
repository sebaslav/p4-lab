#ifndef Multijugador_H
#define Multijugador_H

#include <string>
#include "DtFechaHora.h"
#include "Partida.h"
#include "PartidaInfo.h"
#include "DtPartidaMultijugador.h"

using namespace std;

class Multijugador: public Partida {
    private:
        set<PartidaInfo*> infoDePartidaPorJugador;
        bool estaEnVivo;

    public:
        Multijugador(DtPartidaMultijugador datosPartidaMultijugador, int id);
        void finalizarPartida();
		void abandonarPartida(string nick);
        float obtenerHorasJugadas();
        bool getEstaEnVivo();
        virtual DtPartida* getDtPartida(string nombreVideojuego);
        virtual ~Multijugador();
};

#endif
