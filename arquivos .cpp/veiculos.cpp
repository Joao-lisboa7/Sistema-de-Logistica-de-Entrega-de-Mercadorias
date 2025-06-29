#include <iostream>
#include <string>
#include "veiculos.h"
#include "gerenciadorVeiculos.h"
#include <cstring>
#include <limits>
#include <fstream>
#include <vector>

/*===========Creat=============*/
Veiculos::Veiculos() {
    placa[0] = '\0';
    modelo[0] = '\0';
    status = false; // Por padrão, desocupado
}

Veiculos::Veiculos(const std::string& placa_inicial, const std::string& modelo_inicial, bool status_inicial) {
    strncpy(this->placa, placa_inicial.c_str(), TAM_PLACA - 1);
    this->placa[TAM_PLACA - 1] = '\0';

    strncpy(this->modelo, modelo_inicial.c_str(), TAM_MODELO - 1);
    this->modelo[TAM_MODELO - 1] = '\0';

    this->status = status_inicial;
    
    std::cout << "----Veiculo criado----\nPlaca: " << this->placa << ", Modelo: " << this->modelo << ", Status: " << (this->status ? "Ocupado" : "Desocupado") << std::endl;
}

void salvarVeiculoEmArquivo(const Veiculos& veiculo) {
    std::ofstream arquivo("veiculos.dat", std::ios::binary | std::ios::app);

    if (!arquivo) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo para escrita." << std::endl;
        return;
    }

    arquivo.write(reinterpret_cast<const char*>(&veiculo), sizeof(Veiculos));
    
    arquivo.close();
    std::cout << "Veiculo salvo no arquivo veiculos.dat\n";
}

/*==========Read==============*/
string Veiculos::getPlaca() const{
  return this -> placa;
}

string Veiculos::getModelo() const{
  return this -> modelo;
}

bool Veiculos::getStatus() const{
  return this -> status;
}

/*========update========*/
void Veiculos::setModelo(const std::string& novoModelo) {
    strncpy(this->modelo, novoModelo.c_str(), TAM_MODELO - 1);
    this->modelo[TAM_MODELO - 1] = '\0';
}

void Veiculos::setStatus(bool novoStatus) {
    this->status = novoStatus;
}