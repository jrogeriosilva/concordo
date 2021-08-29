#include "sistema.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>

using namespace std;

string Sistema::quit()
{
  return "Saindo...";
}

string Sistema::create_user(const string email, const string senha, const string nome)
{

  //Verificação inicial da entrada do usuário
  if (email == "" || senha == "" || nome == "")
  {
    return "Algum campo está vazio.";
  }

  //Checa se o e-mail é válido
  if (email.find("@") == string::npos || email.find(".") == string::npos)
  {
    return email + " é um Email inválido.";
  }

  //Checa se o e-amil já está cadastrado
  vector<Usuario>::iterator it;
  for (it = usuarios.begin(); it != usuarios.end(); it++)
  {
    if (it->getEmail() == email)
    {
      return "Email já cadastrado.";
    }
  }

  //Gerando o ID do usuário com base nos que estão cadastrados
  int id = 0;
  if (!usuarios.empty())
  {
    id = usuarios.back().getId() + 1;
  }

  //Cria uma instancia de um usuário e o insere no vetor de usuarios do sistema
  Usuario u(id, nome, email, senha);
  usuarios.push_back(u);

  return "Usuário ID: " + to_string(id) + " criado com sucesso!";
}

string Sistema::login(const string email, const string senha)
{
  //Verificação inicial da entrada do usuário
  if (email == "" || senha == "")
  {
    return "Erro ao efetuar login";
  }

  //Checa se as credenciais estão corretas
  vector<Usuario>::iterator it;
  for (it = usuarios.begin(); it != usuarios.end(); it++)
  {
    if (it->getEmail() == email && it->getSenha() == senha)
    {
      setUsuariosLogados(it->getId());
      return "Logado como " + it->getEmail();
    }
  }

  return "Senha ou usuário inválidos";
}

string Sistema::disconnect(int id)
{
  //Desconecta o usuário informado caso ele esteja conectado
  if (isUsuarioLogado(id))
  {
    usuariosLogados.erase(id);
    return "Desconectando usuario " + getUsuarioByID(id).getEmail();
  }
  else
  {
    return "O usuário informado não está logado";
  }
}

string Sistema::create_server(int id, const string nome)
{

  //Checa se o usuario está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  //Iterador para o servidor
  vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor s)
                                                { return s.getNome() == nome; });

  //Se for o ultimo elemento, não está cadastrado
  if (servidor == servidores.end())
  {

    //Cria uma Instancia de um servidor e adiciona o usuario que o criou como participante
    Servidor s(id, nome);
    s.setParticipanteID(id);

    //Adiciona a instancia de servidor criado no vetor de servidores do sistema
    servidores.push_back(s);

    return "Servidor " + nome + " criado com sucesso!";
  }

  return "Já existe um servidor com o nome " + nome;
}

string Sistema::set_server_desc(int id, const string nome, const string descricao)
{

  //Checa se o usuario está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  //Iterador para o servidor
  std::vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                     { return s.getNome() == nome && s.getUsuarioDonoId() == id; });
  //Se não for o ultimo, o servidor existe
  if (servidor != servidores.end())
  {
    servidor->setDescricao(descricao);
    return "Descricao do servidor alterada com sucesso";
  }
  return "Servidor não encontrado";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo)
{

  //Checa se o usuario está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  //Checa se o servidor existe e se o usuário é o dono
  std::vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                     { return s.getNome() == nome && s.getUsuarioDonoId() == id; });
  if (servidor != servidores.end())
  {
    servidor->setCodigoConvite(codigo);
    return "Código de convite do servidor alterado com sucesso";
  }
  return "Servidor não encontrado";
}

string Sistema::list_servers(int id)
{

  if (servidores.empty())
  {
    return "Nenhum servidor cadastrado";
  }

  std::string output = "";

  //Iterador para percorrer os servidores
  vector<Servidor>::iterator servidor;

  //Este Laço percorre todos os servidores do sistema, e acrescenta ao output o nome do servidor.
  for (servidor = servidores.begin(); servidor != servidores.end(); servidor++)
  {
    output += servidor->getNome();
    if (servidor != servidores.end() - 1)
    {
      output += "\n";
    }
  }

  return output;
}

string Sistema::remove_server(int id, const string nome)
{

  //Checa se o usuario está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  /**
   * Iterador para o servidor
   * Caso o servidor não exista ou o Id do usuario que estiver executando seja diferente do dono do servidor
   * Esse O começo e o fim do iterador serão iguais.
   */
  std::vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                     { return s.getNome() == nome && s.getUsuarioDonoId() == id; });
  if (servidor != servidores.end())
  {
    //Remove o servidor do vetor
    servidores.erase(servidor);

    // Iterador para o mapa de usuários logados
    std::map<int, std::pair<std::string, std::string>>::iterator itrUsuariosLogados;

    //Este Laço Atualiza o campo de Servidor do Map de usuários todos os usuarios logados do servidor que está sendo removido
    for (itrUsuariosLogados = usuariosLogados.begin(); itrUsuariosLogados != usuariosLogados.end(); itrUsuariosLogados++)
    {
      if (itrUsuariosLogados->second.first == nome)
      {
        itrUsuariosLogados->second.first = "";
        itrUsuariosLogados->second.second = "";
      }
    }

    return "Servidor " + nome + " removido com sucesso";
  }

  return "Servidor " + nome + " não encontrado";
}

string Sistema::enter_server(int id, const string nome, const string codigo)
{
  //Verifica se o usuário está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  const string servidorLogado = usuariosLogados[id].first;
  const string canalLogado = usuariosLogados[id].second;

  if (servidorLogado == "nome")
  {
    return "Já está logado no servidor";
  }

  //Iterador para o servidor que o usuario está entrando
  std::vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                     { return s.getNome() == nome; });
  // Se o servidor existir
  if (servidor != servidores.end())
  {
    //Verifica se o usuario se o usuario é participante
    if (servidor->isParticipante(id))
    {
      usuariosLogados[id].first = nome;
      return getUsuarioByID(id).getNome() + " Entrou no servidor " + nome;
    }
    else if (servidor->getCodigoConvite() == "")
    {
      servidor->setParticipanteID(id);
      usuariosLogados[id].first = nome;
      return getUsuarioByID(id).getNome() + " (Novo Usuario) Entrou no servidor " + nome;
    }
    else if (servidor->getCodigoConvite() == codigo)
    {
      servidor->setParticipanteID(id);
      usuariosLogados[id].first = nome;
      return getUsuarioByID(id).getNome() + " (Novo Usuario) Entrou no servidor " + nome + " com código de convite";
    }
    else
    {
      return "Código de convite Inválido";
    }
  }
  return "Servidor " + nome + " não encontrado";
}

string Sistema::leave_server(int id, const string nome)
{
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  //Iterador para servidor
  vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                { return s.getNome() == nome; });
  //Se o informado servidor existir
  if (servidor != servidores.end())
  {
    //Remove o usuário do servidor pelo seu ID
    servidor->removeParticipanteID(id);

    //Atualiza o campo de servidor do usuário logado
    usuariosLogados[id].first = "";
    usuariosLogados[id].second = "";

    return getUsuarioByID(id).getNome() + " Saiu do servidor " + nome;
  }

  return "Servidor não encontrado";
}

string Sistema::list_participants(int id)
{
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  //Capturar o nome do servidor que o usuário está visualizando
  string servidorVisualizado = usuariosLogados[id].first;

  if (servidorVisualizado == "")
  {
    return "Precisa estar visualizando um servidor para executar este comando";
  }

  //Iterador para servidor
  vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                { return s.getNome() == servidorVisualizado; });

  string output = "";

  //Se o servidor existir
  if (servidor != servidores.end())
  {
    //Iterador para os participantes do servidor
    vector<int> idParticipantes = servidor->getParticipantesIDs();

    //Para cada um dos participantes
    for (auto idParticipante : idParticipantes)
    {
      output += getUsuarioByID(idParticipante).getNome() + "\n";
    }
  }
  return output;
}

string Sistema::list_channels(int id)
{
  //Verifica se o usuário está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  string output = "#canais de texto\n";

  //Iterador para servidor
  vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                { return s.getNome() == usuariosLogados[id].first; });

  //Se o servidor existir
  if (servidor != servidores.end())
  {

    if (servidor->getCanaisTexto().empty())
    {
      return "Não há canais de texto";
    }

    for (auto canal : servidor->getCanaisTexto())
    {
      output += canal.getNome() + "\n";
    }
  }
  else
  {
    return "É Preciso entrar em um servidor para executar este comando";
  }

  return output;
}

string Sistema::create_channel(int id, const string nome)
{
  //Checar se o usuário está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  //Se o servidor existir e o canal não existir
  if (find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
              { return s.getNome() == usuariosLogados[id].first && !(s.isCanalTexto(nome)); }) != servidores.end())
  {

    vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                  { return s.getNome() == usuariosLogados[id].first; });

    CanalTexto c(nome);
    servidor->setCanaisTexto(c);
    return "Criando canal " + nome;
  }

  return "Não é possível executar este comando sem entrar em um servidor";
}

string Sistema::enter_channel(int id, const string nome)
{
  //Checar se o usuário está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  //Captura o nome do Servidor que o Usuario está logado
  const string servidorLogado = usuariosLogados[id].first;

  if (servidorLogado == "")
  {
    return "Não é possível executar este comando sem entrar em um servidor";
  }

  //Entra no canal do servidor visualizado caso o canal exista no servidor
  if (find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
              { return s.getNome() == servidorLogado && s.isCanalTexto(nome); }) != servidores.end())
  {
    //Atualiza as informações do usuário logado com o nome do canal que o usuário entrou
    usuariosLogados[id].second = nome;
    return getUsuarioByID(id).getNome() + " entrou no canal " + nome;
  }

  return "O Canal Informado não existe no servidor";
}
string Sistema::leave_channel(int id)
{
  //Checar se o usuário está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }

  const string servidorLogado = usuariosLogados[id].first;
  const string canalLogado = usuariosLogados[id].second;

  if (servidorLogado == "")
  {
    return "Não é possível executar este comando sem entrar em um servidor";
  }

  if (canalLogado == "")
  {
    return "Não é possível executar este comando sem estar em um canal";
  }

  //Caso Exista o Servidor e o canal
  if (find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
              { return s.getNome() == servidorLogado && s.isCanalTexto(canalLogado); }) != servidores.end())
  {
    //Atualiza As informações de Canal Logado em usuariosLogados
    usuariosLogados[id].second = "";
    return "Saindo do canal " + canalLogado;
  }
  return "Erro: O canal ou servidor informado não existe";
}

string Sistema::send_message(int id, const string mensagem)
{
  //Checar se o usuário está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }
  //Captura o nome do Servidor que o Usuario está logado
  const string servidorLogado = usuariosLogados[id].first;

  //Captura o nome do Servidor que o Usuario está logado
  const string canalLogado = usuariosLogados[id].second;

  if (servidorLogado == "")
  {
    return "Não é possível executar este comando sem entrar em um servidor";
  }

  if (canalLogado == "")
  {
    return "Não é possível executar este comando sem estar em um canal";
  }

  char dataHora[20];
  time_t now = time(NULL);
  strftime(dataHora, 20, "%d/%m/%Y - %H:%M", localtime(&now));
  //Converte o vetor de caracteres para string
  string strDataHora(dataHora);

  //Iterador para o servidor
  vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                { return s.getNome() == servidorLogado; });

  //Iterador para o canal
  vector<CanalTexto>::iterator canal = find_if((servidor->getCanaisTexto()).begin(), (servidor->getCanaisTexto()).end(),
                                               [&](CanalTexto &c)
                                               { return c.getNome() == canalLogado; });

  //Cria uma instancia do objeto mensagem
  Mensagem m(strDataHora, id, mensagem);

  //Insere a mensagem no canal
  canal->addMensagem(m);

  return "Mensagem enviada";
}

string Sistema::list_messages(int id)
{
  //Checar se o usuário está logado
  if (!isUsuarioLogado(id))
  {
    return "Usuário não logado";
  }
  //Captura o nome do Servidor que o Usuario está logado
  const string servidorLogado = usuariosLogados[id].first;
  const string canalLogado = usuariosLogados[id].second;
  if (servidorLogado == "")
  {
    return "Não é possível executar este comando sem entrar em um servidor";
  }
  if (canalLogado == "")
  {
    return "Não é possível executar este comando sem estar em um canal";
  }
  //Iterador para o servidor
  vector<Servidor>::iterator servidor = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                                { return s.getNome() == servidorLogado; });

  //Iterador para o canal
  vector<CanalTexto>::iterator canal = find_if((servidor->getCanaisTexto()).begin(), (servidor->getCanaisTexto()).end(),
                                               [&](CanalTexto &c)
                                               { return c.getNome() == canalLogado; });

  vector<Mensagem> mensagens = canal->getMensagens();

  string output = "";
  for (auto mensagem : mensagens)
  {
    output += getUsuarioByID(mensagem.getEnviadaPor()).getNome() + "<" + mensagem.getDataHora() + ">: " + mensagem.getConteudo() + "\n";
  }
  if (output == "")
  {
    return "Não há mensagens no canal";
  }
  return output;
}

void Sistema::setUsuariosLogados(int id)
{
  usuariosLogados.insert({id, {"", ""}});
}

Usuario Sistema::getUsuarioByID(int id)
{
  vector<Usuario>::iterator it;
  for (it = usuarios.begin(); it != usuarios.end(); it++)
  {
    if (it->getId() == id)
    {
      return *it;
    }
  }
  return *usuarios.end();
}

bool Sistema::isUsuarioLogado(int id)
{
  return usuariosLogados.find(id) != usuariosLogados.end();
}

bool Sistema::servidorExiste(const string nome)
{
  vector<Servidor>::iterator it = find_if(servidores.begin(), servidores.end(), [&](Servidor &s)
                                          { return s.getNome() == nome; });

  if (it != servidores.end())
  {
    return true;
  }

  return false;
}