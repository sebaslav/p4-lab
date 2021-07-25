#include "../include/PartidaInfo.h"
#include "../include/FechaHoraSistema.h"

using namespace std;

PartidaInfo::PartidaInfo(Jugador* jugadorAsociadoAInfo){
    this->jugadorAsociadoAInfo = jugadorAsociadoAInfo;
    fechaAbandono = DtFechaHora(-1, -1, -1, -1, -1, -1);
}

string PartidaInfo::getNickname(){
    return this->jugadorAsociadoAInfo->getNickname();
}

void PartidaInfo::abandonar(){
    fechaAbandono = FechaHoraSistema::getInstance()->getFechaSistema();
}

void PartidaInfo::setFechaAbandono(DtFechaHora fechaAbandono){
    this->fechaAbandono = fechaAbandono;
}

DtFechaHora PartidaInfo::getFechaAbandono(){
    return fechaAbandono;
}

PartidaInfo::~PartidaInfo() {}