#include <iostream>
#include "gerenciadorLocais.h"

using namespace std;

// Operação de CRIAR (Create)
void GerenciadorLocais::criarLocal() {
    string nome;
    int x, y;

    cout << "\n--- Adicionar Novo Local ---\n";
    cout << "Digite o nome do local: ";
    cin.ignore(); // Limpa o buffer antes de ler a string
    getline(cin, nome);

    // Validação para garantir que o nome seja único
    for (const auto& local : locais) {
        if (local.nome == nome) {
            cout << "Erro: Ja existe um local com este nome.\n";
            return;
        }
    }

    cout << "Digite a coordenada X: ";
    cin >> x;
    cout << "Digite a coordenada Y: ";
    cin >> y;

    locais.emplace_back(nome, x, y);
    cout << "Local adicionado com sucesso!\n";
}

// Operação de LER (Read)
void GerenciadorLocais::listarLocais() {
    cout << "\n--- Lista de Locais Cadastrados ---\n";
    if (locais.empty()) {
        cout << "Nenhum local cadastrado.\n";
    } else {
        for (const auto& local : locais) {
            cout << "Nome: " << local.nome 
                 << ", Coordenadas: (" << local.coordenadaX 
                 << ", " << local.coordenadaY << ")\n";
        }
    }
}

// Operação de ATUALIZAR (Update)
void GerenciadorLocais::atualizarLocal() {
    string nomeBusca;
    cout << "\n--- Atualizar Local ---\n";
    if (locais.empty()) {
        cout << "Nenhum local para atualizar.\n";
        return;
    }

    cout << "Digite o nome do local que deseja atualizar: ";
    cin.ignore();
    getline(cin, nomeBusca);

    for (auto& local : locais) {
        if (local.nome == nomeBusca) {
            cout << "Digite o novo nome: ";
            getline(cin, local.nome);
            cout << "Digite a nova coordenada X: ";
            cin >> local.coordenadaX;
            cout << "Digite a nova coordenada Y: ";
            cin >> local.coordenadaY;
            cout << "Local atualizado com sucesso!\n";
            return;
        }
    }
    cout << "Erro: Local nao encontrado.\n";
}

// Operação de EXCLUIR (Delete)
void GerenciadorLocais::excluirLocal() {
    string nomeBusca;
    cout << "\n--- Excluir Local ---\n";
     if (locais.empty()) {
        cout << "Nenhum local para excluir.\n";
        return;
    }

    cout << "Digite o nome do local que deseja excluir: ";
    cin.ignore();
    getline(cin, nomeBusca);

    for (auto it = locais.begin(); it != locais.end(); ++it) {
        if (it->nome == nomeBusca) {
            it = locais.erase(it);
            cout << "Local excluido com sucesso!\n";
            return;
        }
    }
    cout << "Erro: Local nao encontrado.\n";
}