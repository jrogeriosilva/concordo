#include "canaltexto.h"

#include <string>
#include <vector>

CanalTexto::CanalTexto(std::string nome)
{
	this->nome = nome;
}

//Getters
std::string CanalTexto::getNome()
{
	return this->nome;
}

std::vector<Mensagem> CanalTexto::getMensagens()
{
	return this->mensagens;
}

//Setters
void CanalTexto::setNome(std::string nome)
{
	this->nome = nome;
}

void CanalTexto::addMensagem(Mensagem mensagem)
{
	this->mensagens.push_back(mensagem);
}
