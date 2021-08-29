#include "mensagem.h"
#include <string>

//Construtor
Mensagem::Mensagem(std::string dataHora, int enviadaPor, std::string conteudo)
{
    this->dataHora = dataHora;
    this->enviadaPor = enviadaPor;
    this->conteudo = conteudo;
}

//Getters
std::string Mensagem::getDataHora()
{
    return dataHora;
}
int Mensagem::getEnviadaPor()
{
    return enviadaPor;
}
std::string Mensagem::getConteudo()
{
    return conteudo;
}

//Setters
void Mensagem::setDataHora(std::string dataHora)
{
    this->dataHora = dataHora;
}
void Mensagem::setEnviadaPor(int enviadaPor)
{
    this->enviadaPor = enviadaPor;
}
void Mensagem::setConteudo(std::string conteudo)
{
    this->conteudo = conteudo;
}
