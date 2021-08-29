# Atividade 02 de LP1
#### Aluno: José Rogério da Silva Júnior
#### [Auto-Avaliação](https://github.com/LP12021-1/trabalho-02-jrogeriosilva/blob/master/Notas_U2.ods)
---
# Sobre o projeto: 
Backend de sistema com recursos de criação de servidores de troca de mensagens similar ao discord, onde é possivel criar canais de textos e troca de mensagens entre usuarios.

![image](https://user-images.githubusercontent.com/15113099/128610441-4ad22d67-4baf-42b3-ae06-77ebbc42b6c4.png)

## Como Compilar o projeto:
### CMAKE
```console
mkdir build
cd build
cmake ..
cmake --build .
```
### Compilando diretamente pelo g++
```console
g++ -o concordo ./src/*.cpp -Iinclude -Wall -pedantic -Werror  -fsanitize=address -std=c++17
```

## Como Executar o projeto:
Você pode rodar o sistema e logo depois digitar os comandos seguidos de ENTER.
Veja a [lista de comandos](https://github.com/LP12021-1/trabalho-02-jrogeriosilva/blob/master/README.md#comandos-do-sistema)
```console
./concordo
```

# Executando com sequencia de comandos via arquivo
Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
./concordo < script_comandos.txt
```

## Como Testar o Projeto 

Na Pasta data existem dois Arquivos txt. que podem ser utilizados para testar o programa.
### Exemplo:
```console
./concordo < ../data/script_comandos2.txt
```

## Comandos do Sistema

### Interação com Usuarios
```	console
create-user <email> <senha_sem_espaços> <nome com espaços>
login <email> <senha>
disconnect <id-de-usuario-logado>
```

### Interação com Servidor

```console
create-server <id-de-usuario-logado> <nome>
set-server-invite-code <id-de-usuario-logado> <nome> <codigo>
list-servers <id-de-usuario-logado>
remove-server <id-de-usuario-logado> <nome>
enter-server <id-de-usuario-logado> <nome>
leave-server <id-de-usuario-logado> <nome>
list-participants <id-de-usuario-logado>
```

### Interaçao com Canais
```console
list-channels <id-de-usuario-logado>
create-channel <id-de-usuario-logado> <nome>
leave-channel <id-de-usuario-logado>
list-messages <id-de-usuario-logado>
send-message <id-de-usuario-logado> <mensagem>
```
