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
    
    // Tratamento de erro para entrada inválida
    if (!(cin >> opcao)) {
        cin.clear(); // Limpa o estado de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a entrada inválida
        opcao = -1; // Define um valor inválido para mostrar mensagem de erro
    }
    
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
    int opcao = -1; // Inicializa com valor inválido
    do {
        cout << "\n===========Menu para Pedidos==========\n";
        cout << "1 - Adicionar pedido\n";
        cout << "2 - Listar pedidos\n";
        cout << "3 - Atualizar pedido\n";
        cout << "4 - Excluir pedido\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Opcao: ";
        
        // Lê a entrada de forma mais robusta
        cin >> opcao;
        
        // Se a entrada falhou, limpa e define como inválida
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
        }
        
        cout << "========================================\n";

        switch (opcao) {
            case 1:
                gerenciadorPedidos.criarPedido();
                // Limpa o buffer após a operação
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 2:
                gerenciadorPedidos.listarPedidos();
                // Limpa o buffer após a operação
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 3:
                gerenciadorPedidos.atualizarPedido();
                // Limpa o buffer após a operação
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 4:
                gerenciadorPedidos.excluirPedido();
                // Limpa o buffer após a operação
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        
        // Tratamento de erro para entrada inválida
        if (!(cin >> opcao)) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a entrada inválida
            opcao = -1; // Define um valor inválido para mostrar mensagem de erro
        }
        
        cout << "======================================\n";

        switch (opcao) {
            case 1:
                gerenciadorLocais.criarLocal();
                // Limpa o buffer após a operação
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 2:
                gerenciadorLocais.listarLocais();
                // Limpa o buffer após a operação
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 3:
                gerenciadorLocais.atualizarLocal();
                // Limpa o buffer após a operação
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 4:
                gerenciadorLocais.excluirLocal();
                // Limpa o buffer após a operação
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cout << "0 -  Voltar ao menu principal\n";
    cout << "Opcao: ";
    
    // Tratamento de erro para entrada inválida
    if (!(cin >> opcao)) {
        cin.clear(); // Limpa o estado de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a entrada inválida
        opcao = -1; // Define um valor inválido para mostrar mensagem de erro
    }

    cout << "========================================\n";
    switch(opcao){
      case 1: {
        this->gerenciadorVeiculos.adicionarNovoVeiculo();
        // Limpa o buffer após a operação
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
      }
      case 2:{
        this -> gerenciadorVeiculos.listarVeiculos();
        // Limpa o buffer após a operação
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
      }
      case 3:{
        this->gerenciadorVeiculos.atualizarVeiculo();
        // Limpa o buffer após a operação
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
      }
      case 4:{
        this ->gerenciadorVeiculos.excluirVeiculo();
        // Limpa o buffer após a operação
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
      }
      case 0:{
        cout << "Voltando ao menu principal...\n";
        break;
      }
      default:{
        cout << "Opcao invalida. Tente novamente.\n"; 
        break;
      }

    }
  }while(opcao != 0);
}
