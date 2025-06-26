#include<iostream>
#include<string>
#include "veiculos.h"

/*===========Creat=============*/
void insereDados_creatVeiculos(){
  string placa, modelo;

  cout << "Digite a placa: ";
  cin >> placa;

  cout << "Digite o modelo: ";
  cin >> modelo;

  Veiculos(placa, modelo);
}
Veiculos::Veiculos(string placa, string modelo){
  this -> placa = placa;
  this -> modelo = modelo;
};


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
