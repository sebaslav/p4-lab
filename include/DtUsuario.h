#ifndef DtUsuario_H
#define DtUsuario_H

#include <string>

using namespace std;

class DtUsuario{
	private:
		string email, contrasenia;

	public:
		DtUsuario();
		DtUsuario(string email, string contrasenia);
		virtual ~DtUsuario();
		string getEmail();
		string getContrasenia();
};

#endif
