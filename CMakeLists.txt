cmake_minimum_required(VERSION 3.5)
project(concordo VERSION 0.1 LANGUAGES CXX )
set (CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic -Werror -std=c++17)

### Executável
# Diretório contendo os .hpp
include_directories(include)

# Cria um executável com nome "concordo", adiciona neste executável os arquivos src/concordo.cpp src/sistema.cpp src/executor.cpp
add_executable( concordo
                src/concordo.cpp
                src/sistema.cpp 
								src/executor.cpp 
                src/mensagem.cpp
                src/usuario.cpp
                src/canaltexto.cpp
                src/servidor.cpp)
             

# The end
