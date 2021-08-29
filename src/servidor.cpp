#include "servidor.h"

#include <algorithm>

//Construtor
Servidor::Servidor(int id, string nome)
{
    this->usuarioDonoId = id;
    this->nome = nome;
}

//Getters
int Servidor::getUsuarioDonoId()
{
    return this->usuarioDonoId;
}

string Servidor::getNome()
{
    return this->nome;
}

string Servidor::getDescricao()
{
    return this->descricao;
}

string Servidor::getCodigoConvite()
{
    return this->codigoConvite;
}

vector<CanalTexto> &Servidor::getCanaisTexto()
{
    return canaisTexto;
}

vector<int> Servidor::getParticipantesIDs()
{
    return this->participantesIDs;
}

//Setters
void Servidor::setUsuarioDonoId(int id)
{
    this->usuarioDonoId = id;
}

void Servidor::setNome(string nome)
{
    this->nome = nome;
}
void Servidor::setDescricao(string descricao)
{
    this->descricao = descricao;
}
void Servidor::setCodigoConvite(string codigoConvite)
{
    this->codigoConvite = codigoConvite;
}
void Servidor::setCanaisTexto(CanalTexto canalTexto)
{
    canaisTexto.push_back(canalTexto);
}
void Servidor::setParticipanteID(int id)
{
    this->participantesIDs.push_back(id);
}

void Servidor::removeParticipanteID(int id)
{
    std::vector<int>::iterator usuario = std::find(this->participantesIDs.begin(), this->participantesIDs.end(), id);

    this->participantesIDs.erase(usuario);
}

bool Servidor::isParticipante(int id)
{
    if (find(this->participantesIDs.begin(), this->participantesIDs.end(), id) != this->participantesIDs.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Servidor::isCanalTexto(string nome)
{
    if (find_if(this->canaisTexto.begin(), this->canaisTexto.end(), [&](CanalTexto ct)
                { return ct.getNome() == nome; }) != this->canaisTexto.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
