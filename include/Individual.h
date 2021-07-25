#ifndef Individual_H
#define Individual_H

#include <string>
#include "DtFechaHora.h"
#include "DtPartidaIndividual.h"
#include "Partida.h"

using namespace std;

class Individual: public Partida {
    private:
        Individual* partidaAContinuar;

    public:
        Individual(Individual* partidaAContinuar, int id);
        void finalizarPartida();
        float obtenerHorasJugadas();
        Individual* getPartidaAContinuar();
        virtual DtPartida* getDtPartida(string nombreVideojuego);
        virtual ~Individual();
};

#endif
