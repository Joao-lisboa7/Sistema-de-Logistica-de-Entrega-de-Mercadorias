#include "gerenciadorPedidos.h"
#include "pedido.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm> // Para std::find_if e std::max_element

// --- Implementação do Construtor ---
GerenciadorPedidos::GerenciadorPedidos() {
    carregarPedidosDoArquivo();
}

// --- Implementação dos Métodos Públicos (CRUD) ---

void GerenciadorPedidos::criarPedido() {
    std::cout << "\n--- Adicionar Novo Pedido ---\n";
    std::string origem, destino;
    double peso;

    // Ignora caracteres pendentes no buffer de entrada
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite o local de origem: ";
    std::getline(std::cin, origem);

    std::cout << "Digite o local de destino: ";
    std::getline(std::cin, destino);

    std::cout << "Digite o peso do item (kg): ";
    std::cin >> peso;

    // Gera um novo ID único
    int novoId = gerarNovoId();

    // Adiciona o novo pedido à lista em memória
    pedidos.emplace_back(novoId, origem, destino, peso);

    // Salva a lista completa e atualizada no arquivo
    salvarListaCompletaNoArquivo();

    std::cout << "Pedido (ID: " << novoId << ") adicionado com sucesso!\n";
}

void GerenciadorPedidos::listarPedidos() const {
    std::cout << "\n--- Lista de Pedidos Cadastrados ---\n";
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido cadastrado.\n";
    } else {
        for (const auto& pedido : pedidos) {
            std::cout << "ID: " << pedido.getId()
                      << " | Origem: " << pedido.getOrigem()
                      << " | Destino: " << pedido.getDestino()
                      << " | Peso: " << pedido.getPeso() << " kg\n";
        }
    }
    std::cout << "-------------------------------------\n";
}

void GerenciadorPedidos::atualizarPedido() {
    std::cout << "\n--- Atualizar Pedido ---\n";
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido para atualizar.\n";
        return;
    }

    int idBusca;
    std::cout << "Digite o ID do pedido que deseja atualizar: ";
    std::cin >> idBusca;

    auto it = encontrarPedidoPorId(idBusca);

    if (it != pedidos.end()) {
        std::cout << "Pedido encontrado. Digite os novos dados.\n";
        std::string novaOrigem, novoDestino;
        double novoPeso;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Digite o novo local de origem: ";
        std::getline(std::cin, novaOrigem);
        std::cout << "Digite o novo local de destino: ";
        std::getline(std::cin, novoDestino);
        std::cout << "Digite o novo peso (kg): ";
        std::cin >> novoPeso;

        // Atualiza os dados do pedido encontrado
        it->setOrigem(novaOrigem);
        it->setDestino(novoDestino);
        it->setPeso(novoPeso);

        salvarListaCompletaNoArquivo();
        std::cout << "Pedido atualizado com sucesso!\n";
    } else {
        std::cout << "Erro: Pedido com ID " << idBusca << " nao encontrado.\n";
    }
}

void GerenciadorPedidos::excluirPedido() {
    std::cout << "\n--- Excluir Pedido ---\n";
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido para excluir.\n";
        return;
    }

    int idBusca;
    std::cout << "Digite o ID do pedido que deseja excluir: ";
    std::cin >> idBusca;

    auto it = encontrarPedidoPorId(idBusca);

    if (it != pedidos.end()) {
        char confirmacao;
        std::cout << "Tem certeza que deseja excluir o pedido de ID " << it->getId()
                  << " (Origem: " << it->getOrigem() << ")? (S/N): ";
        std::cin >> confirmacao;

        if (confirmacao == 'S' || confirmacao == 's') {
            pedidos.erase(it);
            salvarListaCompletaNoArquivo();
            std::cout << "Pedido excluido com sucesso.\n";
        } else {
            std::cout << "Operacao cancelada.\n";
        }
    } else {
        std::cout << "Erro: Pedido com ID " << idBusca << " nao encontrado.\n";
    }
}

// --- Implementação dos Métodos Privados Auxiliares ---

void GerenciadorPedidos::carregarPedidosDoArquivo() {
    std::ifstream arquivo(nomeDoArquivo, std::ios::binary);
    if (!arquivo) {
        std::cout << "LOG: Arquivo de pedidos nao encontrado. Um novo sera criado ao salvar.\n";
        return;
    }

    pedidos.clear();
    Pedido pedidoLido;
    while (arquivo.read(reinterpret_cast<char*>(&pedidoLido), sizeof(Pedido))) {
        pedidos.push_back(pedidoLido);
    }
    arquivo.close();
    std::cout << "LOG: " << pedidos.size() << " pedidos carregados do arquivo binario.\n";
}

void GerenciadorPedidos::salvarListaCompletaNoArquivo() const {
    std::ofstream arquivo(nomeDoArquivo, std::ios::binary | std::ios::trunc);
    if (!arquivo) {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo para escrita." << std::endl;
        return;
    }

    for (const auto& pedido : pedidos) {
        arquivo.write(reinterpret_cast<const char*>(&pedido), sizeof(Pedido));
    }
    arquivo.close();
    std::cout << "LOG: " << pedidos.size() << " pedidos salvos em formato binario no arquivo " << nomeDoArquivo << std::endl;
}

int GerenciadorPedidos::gerarNovoId() const {
    if (pedidos.empty()) {
        return 1; // Começa do 1 se a lista estiver vazia
    }
    // Encontra o maior ID atual e retorna o próximo número
    auto it_max = std::max_element(pedidos.begin(), pedidos.end(),
                                   [](const Pedido& a, const Pedido& b) {
                                       return a.getId() < b.getId();
                                   });
    return it_max->getId() + 1;
}

std::vector<Pedido>::iterator GerenciadorPedidos::encontrarPedidoPorId(int id) {
    return std::find_if(pedidos.begin(), pedidos.end(), [&](const Pedido& pedido) {
        return pedido.getId() == id;
    });
}