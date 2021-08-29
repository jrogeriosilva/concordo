#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include "mensagem.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class CanalTexto
{
private:
	string nome;
	vector<Mensagem> mensagens;

public:
	CanalTexto(string nome);

	//Getters
	string getNome();
	vector<Mensagem> getMensagens();
	//Setters
	void setNome(string nome);

	//Métodos
	void addMensagem(Mensagem mensagem);
};

#endif
