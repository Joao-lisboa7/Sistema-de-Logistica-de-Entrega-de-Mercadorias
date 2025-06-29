#include "gerenciadorLocais.h"
#include "local.h" /
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm> 

// --- Implementação do Construtor ---
GerenciadorLocais::GerenciadorLocais() {
    carregarLocaisDoArquivo();
}

// --- IMPLEMENTAÇÃO DO MÉTODO PUBLICADO ---
Local GerenciadorLocais::encontrarLocalPorNome(const std::string& nome) {
    auto it = std::find_if(locais.begin(), locais.end(), [&](const Local& local) {
        return local.getNome() == nome;
    });

    if (it != locais.end()) {
        return *it; // Retorna uma cópia do local encontrado
    }
    
    return Local(); // Retorna um local padrão (com nome vazio) se não encontrar
}


// --- Implementação dos Métodos Públicos (CRUD) ---

void GerenciadorLocais::criarLocal() {
    std::cout << "\n--- Adicionar Novo Local ---\n";
    std::string nome;
    int x, y;

    // Usa o método privado para obter e validar os dados
    if (pedirDadosParaLocal(nome, x, y)) {
        // Adiciona o novo local à lista em memória
        locais.emplace_back(nome, x, y);

        // Salva a lista completa e atualizada no arquivo
        salvarListaCompletaNoArquivo();

        std::cout << "Local adicionado com sucesso!\n";
    }
}

void GerenciadorLocais::listarLocais() const {
    std::cout << "\n--- Lista de Locais Cadastrados ---\n";
    if (locais.empty()) {
        std::cout << "Nenhum local cadastrado.\n";
    } else {
        for (const auto& local : locais) {
            std::cout << "Nome: " << local.getNome()
                      << " | Coordenadas: (" << local.getCoordenadaX()
                      << ", " << local.getCoordenadaY() << ")\n";
        }
    }
    std::cout << "-------------------------------------\n";
}

void GerenciadorLocais::atualizarLocal() {
    std::cout << "\n--- Atualizar Local ---\n";
    if (locais.empty()) {
        std::cout << "Nenhum local para atualizar.\n";
        return;
    }

    std::string nomeBusca;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Digite o nome do local que deseja atualizar: ";
    std::getline(std::cin, nomeBusca);

    auto it = std::find_if(locais.begin(), locais.end(), [&](const Local& local){ return local.getNome() == nomeBusca; });


    if (it != locais.end()) {
        std::cout << "Local encontrado. Digite os novos dados.\n";
        std::string novoNome;
        int novaCoordX, novaCoordY;

        // Pede os novos dados ao usuário
        std::cout << "Digite o novo nome: ";
        std::getline(std::cin, novoNome);
        std::cout << "Digite a nova coordenada X: ";
        std::cin >> novaCoordX;
        std::cout << "Digite a nova coordenada Y: ";
        std::cin >> novaCoordY;

        // Atualiza os dados do local encontrado
        it->setNome(novoNome);
        it->setCoordenadas(novaCoordX, novaCoordY);

        // Salva a lista modificada no arquivo
        salvarListaCompletaNoArquivo();
        std::cout << "Local atualizado com sucesso!\n";
    } else {
        std::cout << "Erro: Local '" << nomeBusca << "' nao encontrado.\n";
    }
}

void GerenciadorLocais::excluirLocal() {
    std::cout << "\n--- Excluir Local ---\n";
    if (locais.empty()) {
        std::cout << "Nenhum local para excluir.\n";
        return;
    }

    std::string nomeBusca;
    std::cout << "Digite o nome do local que deseja excluir: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nomeBusca);

    auto it = std::find_if(locais.begin(), locais.end(), [&](const Local& local){ return local.getNome() == nomeBusca; });

    if (it != locais.end()) {
        char confirmacao;
        std::cout << "Tem certeza que deseja excluir o local '" << it->getNome() << "'? (S/N): ";
        std::cin >> confirmacao;

        if (confirmacao == 'S' || confirmacao == 's') {
            locais.erase(it);
            salvarListaCompletaNoArquivo();
            std::cout << "Local excluido com sucesso.\n";
        } else {
            std::cout << "Operacao cancelada.\n";
        }
    } else {
        std::cout << "Erro: Local '" << nomeBusca << "' nao encontrado.\n";
    }
}


// --- Implementação dos Métodos Privados Auxiliares ---

void GerenciadorLocais::carregarLocaisDoArquivo() {
    std::ifstream arquivo(nomeDoArquivo, std::ios::binary);
    if (!arquivo) {
        std::cout << "LOG: Arquivo de locais nao encontrado. Um novo sera criado ao salvar.\n";
        return;
    }
    
    locais.clear(); // Limpa a lista antes de carregar
    Local localLido;
    while (arquivo.read(reinterpret_cast<char*>(&localLido), sizeof(Local))) {
        locais.push_back(localLido);
    }
    arquivo.close();
    std::cout << "LOG: " << locais.size() << " locais carregados do arquivo binario.\n";
}

void GerenciadorLocais::salvarListaCompletaNoArquivo() const {
    std::ofstream arquivo(nomeDoArquivo, std::ios::binary | std::ios::trunc);
    if (!arquivo) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo para escrita." << std::endl;
        return;
    }

    for (const auto& local : locais) {
        arquivo.write(reinterpret_cast<const char*>(&local), sizeof(Local));
    }
    arquivo.close();
    std::cout << "LOG: " << locais.size() << " locais salvos em formato binario no arquivo " << nomeDoArquivo << std::endl;
}

bool GerenciadorLocais::pedirDadosParaLocal(std::string& nome, int& x, int& y) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Digite o nome do local: ";
    std::getline(std::cin, nome);
    
    // Validação para garantir que o nome seja único
    if (!encontrarLocalPorNome(nome).getNome().empty()) {
        std::cout << "Erro: Ja existe um local com este nome.\n";
        return false;
    }

    std::cout << "Digite a coordenada X: ";
    std::cin >> x;
    std::cout << "Digite a coordenada Y: ";
    std::cin >> y;
    return true;
}