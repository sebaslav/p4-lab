#ifndef Usuario_H
#define Usuario_H

#include <string>

using namespace std;

class Usuario{
	private:
		string email, contrasenia;

	public:
		Usuario(string email, string contrasenia);
		virtual ~Usuario();
		string getEmail();
		string getContrasenia();
};

#endif
