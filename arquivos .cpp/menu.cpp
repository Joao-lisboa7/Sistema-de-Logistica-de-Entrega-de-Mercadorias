#include<iostream>
#include<string>
#include "menu.h"
using namespace std;

void Menu::mostrarMenuPrincipal(){
  int opcao;

  do{
    cout << "============Menu============";
    cout << "1 -  Gerenciar locais";
    cout << "2 -  Gerenciar veiculos";
    cout << "3 -  Gerenciar pedidos";
    cout << "0 -  Sair \n";
    cout << "Opcao: ";
    cin >> opcao;
    cout << "============================";


    switch(opcao){
      case 1: menuLocais(); break;
      case 2: menuVeiculos(); break;
      case 3: menuPedidos(); break;
      case 0: cout << "Saindo...\n"; break;
      default: cout << "Opcao invalida\n"; break;
    }
  }while(opcao != 0);  
}

void Menu::menuLocais(){
  int opcao;
  do{
    cout << "============Menu para locais============";
    cout << "1 -  Adicionar local";
    cout << "2 -  Listar locais";
    cout << "3 -  Atualizar local";
    cout << "4 -  Excluir local";
    cout << "0 -  Sair";
    cout << "========================================";
  }while(opcao != 0);
}

void Menu::menuVeiculos(){
  int opcao;
  do{
    cout << "============Menu para veiculos============";
    cout << "1 -  Adicionar veiculo";
    cout << "2 -  Listar veiculos";
    cout << "3 -  Atualizar veiculo";
    cout << "4 -  Excluir veiculo";
    cout << "0 -  Sair";
    cout << "========================================";
  }while(opcao != 0);  cout << "";
}

void Menu::menuPedidos(){
   int opcao;
  do{
    cout << "============Menu para pedidos============";
    cout << "1 -  Adicionar pedido";
    cout << "2 -  Listar pedidos";
    cout << "3 -  Atualizar pedido";
    cout << "4 -  Excluir pedido";
    cout << "0 -  Sair";
    cout << "========================================";

  }while(opcao != 0);
}