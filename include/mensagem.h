#ifndef MENSAGEM_H
#define MENSSAGEM_H

#include <string>

using std::string;

class Mensagem
{
private:
	string dataHora;
	int enviadaPor;
	string conteudo;

public:
	/**
	 *  
	 * @brief Construct a new Mensagem object
	 * 
	 * @param dataHora 
	 * @param enviadaPor 
	 * @param conteudo 
	 */
	Mensagem(string dataHora, int enviadaPor, string conteudo);

	/**
	 * @brief Get the Data Hora object
	 * 
	 * @return string 
	 */
	string getDataHora();

	/**
	 * @brief Get the Enviada Por object
	 * 
	 * @return int 
	 */
	int getEnviadaPor();

	/**
	 * @brief Get the Conteudo object
	 * 
	 * @return string 
	 */
	string getConteudo();

	/**
	 * @brief Set the Data Hora object
	 * 
	 * @param dataHora 
	 */
	void setDataHora(string dataHora);

	/**
	 * @brief Set the Enviada Por object
	 * 
	 * @param enviadaPor 
	 */
	void setEnviadaPor(int enviadaPor);

	/**
	 * @brief Set the Conteudo object
	 * 
	 * @param conteudo 
	 */
	void setConteudo(string conteudo);
};

#endif
