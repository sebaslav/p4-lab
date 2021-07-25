#ifndef Desarrollador_H
#define Desarrollador_H

#include "Usuario.h"
#include "Estadistica.h"
#include "DtDesarrollador.h"
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Desarrollador : public Usuario{
    private:
        string empresa;
		set<Estadistica*> estadisticas;
    public:
        Desarrollador(DtDesarrollador* datos);
        ~Desarrollador();
        string getEmpresa();
		void removerEstadisticas();
		void agregarEstadistica(Estadistica* estadistica);
		set<Estadistica*> getEstadisticas();
};

#endif
