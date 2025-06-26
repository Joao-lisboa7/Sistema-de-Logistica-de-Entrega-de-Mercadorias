#include<iostream>
#include<string>
#include "veiculos.h"
#include<cstring>
#include <limits>

/*===========Creat=============*/
Veiculos insereDados_creatVeiculos(){
  string placa_lida, modelo_lido;

  cout << "Digite a placa: ";
  cin >> placa_lida;

  cout << "Digite o modelo: ";
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline(std::cin, modelo_lido);

  Veiculos novoVeiculo(placa_lida, modelo_lido);

  return novoVeiculo;
}

Veiculos::Veiculos(const std::string& placa_inicial, const std::string& modelo_inicial) {
    strncpy(this->placa, placa_inicial.c_str(), TAM_PLACA - 1);
    this->placa[TAM_PLACA - 1] = '\0';

    strncpy(this->modelo, modelo_inicial.c_str(), TAM_MODELO - 1);
    this->modelo[TAM_MODELO - 1] = '\0';

    this->status = true;
    
    std::cout << "LOG: Veiculo criado -> Placa: " << this->placa << ", Modelo: " << this->modelo << std::endl;
}


/*==========Read==============*/
string Veiculos::getPlaca(){
  return this -> placa;
}

string Veiculos::getModelo(){
  return this -> modelo;
}

bool Veiculos::getStatus(){
  return this -> status;
}
