#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "canaltexto.h"

#include <string>
#include <vector>

class Servidor
{
private:
	int usuarioDonoId;
	string nome;
	string descricao;
	string codigoConvite;
	vector<CanalTexto> canaisTexto;
	vector<int> participantesIDs;

public:
	//Constructor
	Servidor(int usuarioDonoId, string nome);
	//Desconstrutor

	//Getters
	int getUsuarioDonoId();
	string getNome();
	string getDescricao();
	string getCodigoConvite();
	vector<CanalTexto> &getCanaisTexto();
	vector<int> getParticipantesIDs();

	//Setters
	void setUsuarioDonoId(int id);
	void setNome(string nome);
	void setDescricao(string descricao);
	void setCodigoConvite(string codigoConvite);
	void setCanaisTexto(CanalTexto canalTexto);

	/**
	 * @brief Insere um participante no servidor pelo seu ID
	 * 
	 * @param id 
	 */
	void setParticipanteID(int id);

	/**
	 * @brief Remove um usuário do servidor pelo ID
	 * 
	 * @param id Id do usuário a ser removido
	 */
	void removeParticipanteID(int id);

	/**
	 * @brief 
	 * 
	 * @param id 
	 * @return true 
	 * @return false 
	 */
	bool isParticipante(int id);

	/**
	 * @brief Recebe um nome e retorna true caso o canal exista no servidor
	 * 
	 * @param nome 
	 * @return true 
	 * @return false 
	 */
	bool isCanalTexto(string nome);
};

#endif