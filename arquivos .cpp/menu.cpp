#include "menu.h"
#include<iostream>
#include<string>
#include<vector>
#include<limits>
using namespace std;

void Menu::mostrarMenuPrincipal(){
  int opcao;

  do{
    cout << "============Menu============\n";
    cout << "1 -  Gerenciar locais\n";
    cout << "2 -  Gerenciar veiculos\n";
    cout << "3 -  Gerenciar pedidos\n";
    cout << "0 -  Sair \n";
    cout << "Opcao: ";
    cin >> opcao;
    cout << "============================\n";


    switch(opcao){
      case 1: menuLocais(); break;
      case 2: menuVeiculos(); break;
      case 3: menuPedidos(); break;
      case 0: cout << "Saiu\n"; break;
      default: cout << "Opcao invalida\n"; break;
    }
  }while(opcao != 0);
}

void Menu::menuLocais(){
  int opcao;
  do{
    cout << "============Menu para locais============\n";
    cout << "1 -  Adicionar local\n";
    cout << "2 -  Listar locais\n";
    cout << "3 -  Atualizar local\n";
    cout << "4 -  Excluir local\n";
    cout << "0 -  Sair\n";
    cout << "Opcao: ";
    cin >> opcao;
    cout << "========================================\n";
  }while(opcao != 0);
}

void Menu::menuVeiculos(){
  int opcao; 
  do{
    cout << "============Menu para veiculos============\n";
    cout << "1 -  Adicionar veiculo\n";
    cout << "2 -  Listar veiculos\n";
    cout << "3 -  Atualizar veiculo\n";
    cout << "4 -  Excluir veiculo\n";
    cout << "0 -  Sair\n";
    cout << "Opcao: ";
    cin >> opcao;

     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "========================================\n";
    switch(opcao){
      case 1: {
        this->gerenciadorVeiculos.adicionarNovoVeiculo();
        break;
      }
      case 2:{
        this -> gerenciadorVeiculos.listarVeiculos();
        break;
      }
      case 3:{
        this->gerenciadorVeiculos.atualizarVeiculo();
        break;
      }
      case 4:{
        this ->gerenciadorVeiculos.excluirVeiculo();
        break;
      }
      default:{
        cout << "Opcao invalida \n"; break;
      }

    }
  }while(opcao != 0);  cout << "";
}


void Menu::menuPedidos(){
   int opcao;
  do{
    cout << "============Menu para pedidos============\n";
    cout << "1 -  Adicionar pedido\n";
    cout << "2 -  Listar pedidos\n";
    cout << "3 -  Atualizar pedido\n";
    cout << "4 -  Excluir pedido\n";
    cout << "0 -  Sair\n";
    cout << "Opcao: ";
    cin >> opcao;
    cout << "========================================";

  }while(opcao != 0);
}
