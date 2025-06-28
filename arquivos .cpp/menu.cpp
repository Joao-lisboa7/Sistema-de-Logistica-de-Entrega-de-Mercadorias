#include "menu.h"
#include<iostream>
#include<string>
#include<vector>
#include<limits>
using namespace std;

void Menu::mostrarMenuPrincipal() {
    int opcao;

  do{
    cout << "========Menu Principal========\n";
    cout << "1 - Gerenciar locais\n";
    cout << "2 - Gerenciar veiculos\n";
    cout << "3 - Gerenciar pedidos\n";
    cout << "0 - Sair \n";
    cout << "Opcao: ";
    cin >> opcao;
    cout << "==============================\n";


    switch(opcao){
      case 1: menuLocais(); break;
      case 2: menuVeiculos(); break;
      case 3: menuPedidos(); break;
      case 0: cout << "Saindo...\n"; break;
      default: cout << "Opcao invalida\n"; break;
    }
  }while(opcao != 0);
}
void Menu::menuPedidos() {
    int opcao;
    do {
        cout << "\n===========Menu para Pedidos==========\n";
        cout << "1 - Adicionar pedido\n";
        cout << "2 - Listar pedidos\n";
        cout << "3 - Atualizar pedido\n";
        cout << "4 - Excluir pedido\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Opcao: ";
        cin >> opcao;
        cout << "========================================\n";

        switch (opcao) {
            case 1:
                gerenciadorPedidos.criarPedido();
                break;
            case 2:
                gerenciadorPedidos.listarPedidos();
                break;
            case 3:
                gerenciadorPedidos.atualizarPedido();
                break;
            case 4:
                gerenciadorPedidos.excluirPedido();
                break;
            case 0:
                cout << "Voltando ao menu principal...\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
                break;
        }

    } while (opcao != 0);
}
void Menu::menuLocais() {
    int opcao;
    do {
        cout << "===========Menu para Locais===========\n";
        cout << "1 - Adicionar local\n";
        cout << "2 - Listar locais\n";
        cout << "3 - Atualizar local\n";
        cout << "4 - Excluir local\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Opcao: ";
        cin >> opcao;
        cout << "======================================\n";

        switch (opcao) {
            case 1:
                gerenciadorLocais.criarLocal();
                break;
            case 2:
                gerenciadorLocais.listarLocais();
                break;
            case 3:
                gerenciadorLocais.atualizarLocal();
                break;
            case 4:
                gerenciadorLocais.excluirLocal();
                break;
            case 0:
                cout << "Voltando ao menu principal...\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
                break;
        }
    } while (opcao != 0);
}

void Menu::menuVeiculos(){
  int opcao; 
  do{
    cout << "===========Menu para veiculos===========\n";
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
        cout << "Opcao invalida. Tente novamente.\n"; break;
      }

    }
  }while(opcao != 0);  cout << "";
}


void Menu::menuPedidos() {
    int opcao;
    do {
        cout << "\n===========Menu para Pedidos==========\n";
        cout << "1 - Adicionar pedido\n";
        cout << "2 - Listar pedidos\n";
        cout << "3 - Atualizar pedido\n";
        cout << "4 - Excluir pedido\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "========================================\n";

    } while (opcao != 0);
}
