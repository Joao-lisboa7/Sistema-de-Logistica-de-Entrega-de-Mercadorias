#include "gerenciadorVeiculos.h"
#include "veiculos.h"
#include <iostream>
#include <fstream>
#include <limits>

// --- Implementação do Construtor ---
GerenciadorVeiculos::GerenciadorVeiculos() {
    carregarVeiculosDoArquivo();
}

// --- Implementação do Método Principal do "Create" ---
void GerenciadorVeiculos::adicionarNovoVeiculo() {
    // 1. O gerenciador usa seu método privado para conversar com o usuário.
    Veiculos veiculoNovo = pedirDadosParaNovoVeiculo();

    // 2. Adiciona o novo veículo à sua lista em memória.
    this->listaDeVeiculos.push_back(veiculoNovo);

    // 3. Usa seu outro método privado para salvar o novo veículo no arquivo.
    salvarVeiculoNoArquivo(veiculoNovo);

    std::cout << "\nVeiculo adicionado com sucesso!\n";
}

// --- Implementações dos Métodos Auxiliares ---

Veiculos GerenciadorVeiculos::pedirDadosParaNovoVeiculo() {
    string placa_lida, modelo_lido;

    cout << "--- Adicionar Novo Veiculo ---\n";

    do{
      cout << "Digite a placa: ";
      cin >> placa_lida;

      if(placa_lida.length() != 7){
        cout << "Erro: A placa deve conter exatamente 7 \n";
      }
    }while(placa_lida.length() != 7);

    cout << "Digite o modelo: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, modelo_lido);

    return Veiculos(placa_lida, modelo_lido);
}

void GerenciadorVeiculos::salvarVeiculoNoArquivo(const Veiculos& veiculo) {
    // Abre o arquivo para adicionar no final (append), em modo binário.
    std::ofstream arquivo(this->nomeDoArquivo, std::ios::binary | std::ios::app);

    if (!arquivo) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo para escrita." << std::endl;
        return;
    }

    arquivo.write(reinterpret_cast<const char*>(&veiculo), sizeof(Veiculos));
    arquivo.close();
}

void GerenciadorVeiculos::carregarVeiculosDoArquivo() {
    // Abre o arquivo para leitura, em modo binário.
    std::ifstream arquivo(this->nomeDoArquivo, std::ios::binary);

    if (!arquivo) {
        std::cout << "LOG: Arquivo de dados nao encontrado. Um novo sera criado ao salvar o primeiro veiculo.\n";
        return;
    }
    
    Veiculos veiculoLido;
    // Lê o arquivo objeto por objeto e adiciona na lista
    while (arquivo.read(reinterpret_cast<char*>(&veiculoLido), sizeof(Veiculos))) {
        this->listaDeVeiculos.push_back(veiculoLido);
    }
    arquivo.close();
}

/*=========read========*/
void GerenciadorVeiculos::listarVeiculos() const {
    std::cout << "\n--- LISTA DE VEICULOS ---\n";
    if (this->listaDeVeiculos.empty()) {
        std::cout << "Nenhum veiculo cadastrado.\n";
    } else {
        for (const auto& veiculo : this->listaDeVeiculos) {
            std::cout << "Placa: " << veiculo.getPlaca() << " | Modelo: " << veiculo.getModelo() << std::endl;
        }
    }
    std::cout << "---------------------------\n";
} 

void GerenciadorVeiculos::excluirVeiculo() {
    std::string placa_busca;
    std::cout << "--- Excluir Veiculo ---\n";
    std::cout << "Digite a placa do veiculo que deseja excluir: ";
    std::cin >> placa_busca;

    // Usamos um 'iterador' para encontrar a posição do veículo na lista
    auto it = listaDeVeiculos.begin();
    while (it != listaDeVeiculos.end()) {
        // it->getPlaca() é o mesmo que (*it).getPlaca()
        if (it->getPlaca() == placa_busca) {
            // --- Veículo encontrado! ---
            std::cout << "Veiculo encontrado: " << it->getModelo() << std::endl;
            
            char confirmacao;
            std::cout << "Tem certeza que deseja excluir este veiculo? (S/N): ";
            std::cin >> confirmacao;

            if (confirmacao == 'S' || confirmacao == 's') {
                // Remove o veículo do vetor usando o iterador
                it = listaDeVeiculos.erase(it);

                // Reescreve o arquivo .dat com a lista atualizada
                salvarListaCompletaNoArquivo();
                
                std::cout << "Veiculo excluido com sucesso.\n";
            } else {
                std::cout << "Operacao cancelada.\n";
            }
            return; // Sai da função pois já encontrou e tratou o veículo
        }
        ++it; // Avança para o próximo item da lista
    }

    // Se o loop terminar, significa que o veículo não foi encontrado
    std::cout << "Veiculo com a placa '" << placa_busca << "' nao encontrado.\n";
}


// --- Implementação do novo método de salvar ---
void GerenciadorVeiculos::salvarListaCompletaNoArquivo() const {
    // Abre o arquivo em modo de escrita binária (sem 'app'), o que SOBRESCREVE o conteúdo.
    std::ofstream arquivo(this->nomeDoArquivo, std::ios::binary);

    if (!arquivo) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo para reescrever." << std::endl;
        return;
    }

    // Itera sobre a lista em memória e escreve cada veículo no arquivo novo/limpo.
    for (const auto& veiculo : this->listaDeVeiculos) {
     arquivo.write(reinterpret_cast<const char*>(&veiculo), sizeof(veiculo));
    }

    arquivo.close();
}