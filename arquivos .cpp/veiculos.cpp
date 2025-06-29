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
    status = false; 
    coordenadaX = 0;
    coordenadaY = 0;
}

Veiculos::Veiculos(const std::string& placa_inicial, const std::string& modelo_inicial, bool status_inicial, int coordX, int coordY) {
    strncpy(this->placa, placa_inicial.c_str(), TAM_PLACA - 1);
    this->placa[TAM_PLACA - 1] = '\0';

    strncpy(this->modelo, modelo_inicial.c_str(), TAM_MODELO - 1);
    this->modelo[TAM_MODELO - 1] = '\0';

    this->status = status_inicial;
    this->coordenadaX = coordX;
    this->coordenadaY = coordY;
    
    std::cout << "----Veiculo criado----\nPlaca: " << this->placa << ", Modelo: " << this->modelo << ", Status: " << (this->status ? "Ocupado" : "Desocupado") << ", Local: (" << this->coordenadaX << ", " << this->coordenadaY << ")" << std::endl;
}

// ... (salvarVeiculoEmArquivo)

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

int Veiculos::getCoordenadaX() const {
    return this->coordenadaX;
}

int Veiculos::getCoordenadaY() const {
    return this->coordenadaY;
}

/*========update========*/
void Veiculos::setModelo(const std::string& novoModelo) {
    strncpy(this->modelo, novoModelo.c_str(), TAM_MODELO - 1);
    this->modelo[TAM_MODELO - 1] = '\0';
}

void Veiculos::setStatus(bool novoStatus) {
    this->status = novoStatus;
}

void Veiculos::setLocalAtual(int novoX, int novoY) {
    this->coordenadaX = novoX;
    this->coordenadaY = novoY;
}