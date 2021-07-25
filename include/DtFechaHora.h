#ifndef DtFechaHora_H
#define DtFechaHora_H

#include <iostream>

using namespace std;

class DtFechaHora {
    private:
        int anio, mes, dia, hora, minuto, segundo;

    public:

	bool operator>(const DtFechaHora &date);
	bool operator>=(const DtFechaHora &date);
	bool operator<(const DtFechaHora &date);
	bool operator<=(const DtFechaHora &date);
	bool operator==(const DtFechaHora &date);
	bool operator!=(const DtFechaHora &date);
	DtFechaHora operator+(const DtFechaHora &b);
	float operator-(const DtFechaHora &b);
    DtFechaHora(int anio, int mes, int dia, int hora, int minuto, int segundo);
    DtFechaHora();
    /* DtFechaHora(const DtFechaHora& fecha); */
    /* DtFechaHora& operator=(const DtFechaHora&); */
    int getAnio() const;
    int getMes() const;
    int getDia() const;
    int getHora() const;
    int getMinuto() const;
    int getSegundo() const;
    friend ostream &operator<<(ostream &o, const DtFechaHora &dtFechaHora);
};

#endif
