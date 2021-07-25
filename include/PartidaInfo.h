#ifndef PartidaInfo_H
#define PartidaInfo_H

#include <string>
#include "DtFechaHora.h"
#include "Jugador.h"

using namespace std;

class PartidaInfo{
    private:
        DtFechaHora fechaAbandono;
        Jugador* jugadorAsociadoAInfo;

    public:
        PartidaInfo(Jugador* jugadorAsociadoAInfo);
		string getNickname();
		void abandonar();
        void setFechaAbandono(DtFechaHora fechaDeAbandono);
        DtFechaHora getFechaAbandono();
        ~PartidaInfo();
};

#endif
