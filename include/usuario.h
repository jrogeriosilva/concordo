#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Usuario
{
private:
	int id;
	string nome;
	string email;
	string senha;

public:
	//Parametrized Constructor
	Usuario(int id, std::string nome, std::string email, std::string senha);

	//Getters
	int getId();
	string getNome();
	string getEmail();
	string getSenha();

	//Setters
	void setId(int id);
	void setNome(string nome);
	void setEmail(string email);
	void setSenha(string senha);
};

#endif
