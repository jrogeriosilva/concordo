#include "usuario.h"

#include <string>

Usuario::Usuario(int id, std::string nome, std::string email, std::string senha)
{
    this->id = id;
    this->nome = nome;
    this->email = email;
    this->senha = senha;
}

//Getters
int Usuario::getId() { return this->id; }
string Usuario::getNome() { return this->nome; }
string Usuario::getEmail() { return this->email; }
string Usuario::getSenha() { return this->senha; }

//Setters
void Usuario::setId(int id) { this->id = id; }
void Usuario::setNome(string nome) { this->nome = nome; }
void Usuario::setEmail(string email) { this->email = email; }
void Usuario::setSenha(string senha) { this->senha = senha; }