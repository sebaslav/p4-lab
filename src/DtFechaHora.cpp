#include <iostream>
#include <string>
#include "../include/DtFechaHora.h"

using namespace std;

DtFechaHora::DtFechaHora() {}

DtFechaHora::DtFechaHora(int anio, int mes, int dia, int hora, int minuto, int segundo){
	this->anio = anio;
	this->mes = mes;
	this->dia = dia;
	this->hora = hora;
	this->minuto = minuto;
	this->segundo = segundo;
}

bool DtFechaHora::operator>(const DtFechaHora &date){
	if(this->anio !=  date.anio){
		return this->anio > date.anio;
	}

	if(this->mes !=  date.mes){
		return this->mes > date.mes;
	}

	if(this->dia !=  date.dia){
		return this->dia > date.dia;
	}

	if(this->hora !=  date.hora){
		return this->hora > date.hora;
	}

	if(this->minuto !=  date.minuto){
		return this->minuto > date.minuto;
	}

	if(this->segundo !=  date.segundo){
		return this->segundo > date.segundo;
	}

	return false; // date == this
}

bool DtFechaHora::operator>=(const DtFechaHora &date){
	if(this->anio !=  date.anio){
		return this->anio > date.anio;
	}

	if(this->mes !=  date.mes){
		return this->mes > date.mes;
	}

	if(this->dia !=  date.dia){
		return this->dia > date.dia;
	}

	if(this->hora !=  date.hora){
		return this->hora > date.hora;
	}

	if(this->minuto !=  date.minuto){
		return this->minuto > date.minuto;
	}

	if(this->segundo !=  date.segundo){
		return this->segundo > date.segundo;
	}

	return true; // date == this
}

bool DtFechaHora::operator<(const DtFechaHora &date){
	if(this->anio !=  date.anio){
		return this->anio < date.anio;
	}

	if(this->mes !=  date.mes){
		return this->mes < date.mes;
	}

	if(this->dia !=  date.dia){
		return this->dia < date.dia;
	}

	if(this->hora !=  date.hora){
		return this->hora < date.hora;
	}

	if(this->minuto !=  date.minuto){
		return this->minuto < date.minuto;
	}

	if(this->segundo !=  date.segundo){
		return this->segundo < date.segundo;
	}

	return false; // date == this
}

bool DtFechaHora::operator<=(const DtFechaHora &date){
	if(this->anio !=  date.anio){
		return this->anio < date.anio;
	}

	if(this->mes !=  date.mes){
		return this->mes < date.mes;
	}

	if(this->dia !=  date.dia){
		return this->dia < date.dia;
	}

	if(this->hora !=  date.hora){
		return this->hora < date.hora;
	}

	if(this->minuto !=  date.minuto){
		return this->minuto < date.minuto;
	}

	if(this->segundo !=  date.segundo){
		return this->segundo < date.segundo;
	}

	return true; // date == this
}


bool DtFechaHora::operator==(const DtFechaHora &date){
	if(this->anio !=  date.anio){
		return false;
	}

	if(this->mes !=  date.mes){
		return false;
	}

	if(this->dia !=  date.dia){
		return false;
	}

	if(this->hora !=  date.hora){
		return false;
	}

	if(this->minuto !=  date.minuto){
		return false;
	}

	if(this->segundo !=  date.segundo){
		return false;
	}

	return true; // date == this
}


bool DtFechaHora::operator!=(const DtFechaHora &date){
	if(this->anio !=  date.anio){
		return true;
	}

	if(this->mes !=  date.mes){
		return true;
	}

	if(this->dia !=  date.dia){
		return true;
	}

	if(this->hora !=  date.hora){
		return true;
	}

	if(this->minuto !=  date.minuto){
		return true;
	}

	if(this->segundo !=  date.segundo){
		return true;
	}

	return false; // date == this}
}

int DtFechaHora::getAnio() const {
    return anio;
}

int DtFechaHora::getMes() const {
    return mes;
}

int DtFechaHora::getDia() const {
    return dia;
}

int DtFechaHora::getHora() const {
    return hora;
}

int DtFechaHora::getMinuto() const {
    return minuto;
}

int DtFechaHora::getSegundo() const {
    return segundo;
}

bool esSecular(int year);
bool esBisiesto(int year);
//Este operador le suma a una fecha una tiempo determinado por el segundo parámetro
//En caso de sumar una fecha y caer fuera de las fechas válidas se lleva a la fecha más cercana 
//Ejemplo 1 : 31 de enero 2000 + un mes = 29 febrero del 2000  
//Ejemplo 2 : 29 febrero del 2000 + un año = 28 febrero del 2001
DtFechaHora DtFechaHora::operator+(const DtFechaHora &b){

	enum mesDelAnio {Enero, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Setiempre, Octubre, Noviembre, Diciembre};
	int diasDelMes [12] = { 30 , 27 , 30 , 29 , 30 , 29 , 30 , 30 , 29 , 30 , 29 , 30 };

	int carryMinutos = (this->segundo + b.segundo)/60;
	int resSegundo = (this->segundo + b.segundo) % 60; 

	int carryHora = (this->minuto + b.minuto + carryMinutos) / 60;
	int resMinuto = (this->minuto + b.minuto + carryMinutos) % 60; 

	int carryDia = ((this->hora + b.hora) + carryHora) / 24;
	int resHora = ((this->hora + b.hora) + carryHora) % 24; 

	int resDia = this->dia + b.dia + carryDia;

	int auxMes = this->mes;
	
	int resAnio = this->anio;

	while(resDia > diasDelMes[auxMes] + (int)((esBisiesto(resAnio) && auxMes == Febrero)?1:0) ){
		resDia -= diasDelMes[auxMes] + (int)((esBisiesto(resAnio) && auxMes == Febrero)?1:0); 
		auxMes = (auxMes + 1) % 12;
		resAnio += (int)((auxMes == Enero)?1:0);
	}
	int resMes = (auxMes + b.mes) % 12;
	resAnio += b.anio + (auxMes + b.mes) / 12;

	return DtFechaHora(resAnio,resMes,resDia,resHora,resMinuto,resSegundo);
}

float DtFechaHora::operator-(const DtFechaHora &b){
	enum mesDelAnio {Enero, Febrero, Marzo, Abril, Mayo, Junio, Julio, Agosto, Setiempre, Octubre, Noviembre, Diciembre};
	int diasDelMes [12] = { 30 , 27 , 30 , 29 , 30 , 29 , 30 , 30 , 29 , 30 , 29 , 30 };
	float HorasDeUnAnio = 365*24;
	float SegundosDeUnDia = 24*60*60;
	float SegundosDeUnaHora = 60*60;

	//caso fácil
	if(this->anio == b.anio && this->mes == b.mes && this->dia == b.dia){
		return ( (this->hora*SegundosDeUnaHora + this->minuto*60 + this->segundo) - (b.hora*SegundosDeUnaHora + b.minuto*60 + b.segundo) ) / SegundosDeUnaHora;
	}

	float resHoras = 0;
	int finalSegundos = this->hora*SegundosDeUnaHora +  this->minuto*60 + this->segundo;
	int comienzoSegundos = b.hora*SegundosDeUnaHora + b.minuto*60 + b.segundo;

	int comienzoDia;
	int comienzoMes;
	int comienzoAnio;
	//left gap (dias)
	if(comienzoSegundos != 0){

		//segundos para terminar el dia
		resHoras += (SegundosDeUnDia - comienzoSegundos) / SegundosDeUnaHora;

		//update fecha comienzo ++
		if(b.dia + 1 > diasDelMes[b.mes] + (float)((esBisiesto(b.mes) && b.mes == Febrero)?1:0)){//si al sumar 1 me cambio de mes ...
			comienzoDia = 0;
			comienzoMes = (b.mes + 1) % 12;
			comienzoAnio = b.anio + (float)((comienzoMes == Enero)?1:0);
		}
		else{//si al sumar 1 NO me cambio de mes ...
			comienzoDia = b.dia + 1;
			comienzoMes = b.mes;
			comienzoAnio = b.anio; 
		}
	}
	else{
		comienzoDia = b.dia;
		comienzoMes = b.mes;
		comienzoAnio = b.anio; 
	
	}
	//end left gap (dias)

	int finalDia;
	int finalMes;
	int finalAnio;
	//right gap
	resHoras += finalSegundos / SegundosDeUnaHora;	

	//update fecha final --
	if(this->dia > 0){
		finalDia = this->dia - 1;
		finalMes = this->mes;
		finalAnio = this->anio;
	}
	else{
		finalMes = (this->mes + 11) % 12;//finalMes --
		finalDia = diasDelMes[finalMes] + ((esBisiesto(this->anio) && finalMes == Febrero)?1:0);
		finalAnio = this->anio - ((finalMes == Diciembre)?1:0);
	}
	//end right gap	

	//de ahora en más podemos manejarnos en términos de dias

	//caso en donde de me invierte el orden ya que eran fechas contiguas
	if((finalAnio < comienzoAnio) or(finalAnio == comienzoAnio and finalMes < comienzoMes) or (finalMes == comienzoMes and finalMes == comienzoMes and finalDia < comienzoDia)){ return resHoras; }	

	//caso fácil
	if(finalAnio == comienzoAnio && comienzoMes == finalMes){
		return resHoras + (finalDia - comienzoDia + 1)*24;
	}

	//left gap 
	if(comienzoDia != 0){// completar los dias del mes
		resHoras += (diasDelMes[comienzoMes] + ((esBisiesto(comienzoAnio) && comienzoMes == Febrero)?1:0) - comienzoDia + 1)*24; // horas restantes para cambiar de mes 


		//update fecha comienzo Mes ++
		comienzoMes = (comienzoMes + 1) % 12;
		comienzoAnio += (comienzoMes == Enero)?1:0;
	}


	//right gap

	resHoras += (finalDia + 1)*24;//dias del mes de la fecha final

	//update fecha final Mes--
 	finalMes = (finalMes + 11) % 12; //finalMes --
	finalAnio -= (finalMes == Diciembre)?1:0;



	//De ahora en más podemos manejarnos en términos de meses


	//caso en donde al ser fecha de meses contuguos se pueden cambiar de lugar
	if((finalAnio < comienzoAnio) or (finalAnio == comienzoAnio and finalMes < comienzoMes)){
		return resHoras;
	}

	//caso fácil
	if(finalAnio == comienzoAnio){
		for(int i = comienzoMes; i <= finalMes; i++){
			resHoras += (diasDelMes[i] + 1 + (float)((i == Febrero) && (esBisiesto(finalAnio))?1:0))*24;			
		}
		return resHoras;
	}

	//left gap (meses)

	if(comienzoMes != Enero){
		for(int i = comienzoMes; i <= Diciembre ; i++){
			resHoras += resHoras += (diasDelMes[i] + 1 + (float)((i == Febrero) && (esBisiesto(finalAnio))?1:0))*24;
		}
		comienzoAnio++;
	}

	//right gap (meses)
	if(finalMes != Diciembre){
		for(int i = finalMes; i >= Enero ; i--){
			resHoras += (diasDelMes[i] + 1 + (float)((i == Febrero) && (esBisiesto(finalAnio))?1:0))*24; 
		}
		finalAnio--;
	}

	//deahora en más podemos manejarnos en términos de años 

	//caso en donde al ser fechas de años contiguos se pueden cambiar de lugar
	if(comienzoAnio > finalAnio){return resHoras;}
	
	for(int i = comienzoAnio; i <= finalAnio ; i++){
		resHoras += HorasDeUnAnio + (float)((esBisiesto(i))?1:0)*24;
	}
	return resHoras;
}//end operator-
bool esSecular(int year){
	return year % 100 == 0;	
}
bool esBisiesto(int year){
	return esSecular(year)? year % 400 == 0 : year % 4 == 0;	
}
/* DtFechaHora::DtFechaHora(const DtFechaHora& fecha) { */
/*     this->dia = fecha.dia; */
/*     this->mes = fecha.mes; */
/* 	this->anio = fecha.anio; */
/*     this->hora = fecha.hora; */
/*     this->minuto = fecha.minuto; */
/* } */

/* DtFechaHora& DtFechaHora::operator=(const DtFechaHora &fecha) { */
/*     this->dia = fecha.dia; */
/*     this->mes = fecha.mes; */
/* 	this->anio = fecha.anio; */
/*     this->hora = fecha.hora; */
/*     this->minuto = fecha.minuto; */
/*     return *this; */
/* } */

ostream &operator<<(ostream &o, const DtFechaHora &f) {
	o << f.getAnio() << "/" << f.getMes() << "/" << f.getDia() << " - ";
	if (f.getHora() < 10) 
		o << 0;
	o << f.getHora() << ":";
	if (f.getMinuto() < 10) 
		o << 0;
	o << f.getMinuto() << ":";
	if (f.getSegundo() < 10) 
		o << 0;
	o << f.getSegundo();
	return o;
}