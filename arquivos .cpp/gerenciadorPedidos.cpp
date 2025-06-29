#include "gerenciadorPedidos.h"
#include "pedido.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm> 
#include <cmath>     // Para a função de distância

// --- FUNÇÃO AUXILIAR PARA CÁLCULO DE DISTÂNCIA (pode ser repetida aqui ou colocada em um arquivo .h comum) ---
double calcularDistancia(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// --- Implementação do Construtor ---
GerenciadorPedidos::GerenciadorPedidos(GerenciadorVeiculos& gv) : gerenciadorVeiculos(gv) {
    carregarPedidosDoArquivo();
}

// --- IMPLEMENTAÇÃO DO NOVO MÉTODO ---
void GerenciadorPedidos::calcularRotaDeEntrega() {
    std::cout << "\n--- Calcular Rota de Entrega ---\n";
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido cadastrado para calcular a rota.\n";
        return;
    }

    int idBusca;
    std::cout << "Digite o ID do pedido para o qual deseja calcular a rota: ";
    std::cin >> idBusca;

    auto it = encontrarPedidoPorId(idBusca);

    if (it == pedidos.end()) {
        std::cout << "Erro: Pedido com ID " << idBusca << " nao encontrado.\n";
        return;
    }
    
    Pedido& pedidoSelecionado = *it;

    std::cout << "Buscando veiculo disponivel mais proximo da origem: " 
              << pedidoSelecionado.getOrigem() << " (" << pedidoSelecionado.getOrigemX() 
              << "," << pedidoSelecionado.getOrigemY() << ")...\n";

    Veiculos* veiculo = gerenciadorVeiculos.encontrarVeiculoMaisProximo(
        pedidoSelecionado.getOrigemX(), 
        pedidoSelecionado.getOrigemY()
    );

    if (veiculo == nullptr) {
        std::cout << "Nenhum veiculo desocupado foi encontrado para realizar a entrega.\n";
        return;
    }

    // --- ROTA CALCULADA COM SUCESSO ---
    double distVeiculoOrigem = calcularDistancia(
        veiculo->getCoordenadaX(), veiculo->getCoordenadaY(),
        pedidoSelecionado.getOrigemX(), pedidoSelecionado.getOrigemY()
    );

    double distOrigemDestino = calcularDistancia(
        pedidoSelecionado.getOrigemX(), pedidoSelecionado.getOrigemY(),
        pedidoSelecionado.getDestinoX(), pedidoSelecionado.getDestinoY()
    );

    double distanciaTotal = distVeiculoOrigem + distOrigemDestino;

    std::cout << "\n========== ROTA DE ENTREGA ==========\n";
    std::cout << "VEICULO SELECIONADO:\n";
    std::cout << "  - Placa: " << veiculo->getPlaca() << "\n";
    std::cout << "  - Modelo: " << veiculo->getModelo() << "\n";
    std::cout << "  - Localizacao Atual: (" << veiculo->getCoordenadaX() << "," << veiculo->getCoordenadaY() << ")\n";
    std::cout << "-------------------------------------\n";
    std::cout << "PEDIDO:\n";
    std::cout << "  - Origem: " << pedidoSelecionado.getOrigem() << " (" << pedidoSelecionado.getOrigemX() << "," << pedidoSelecionado.getOrigemY() << ")\n";
    std::cout << "  - Destino: " << pedidoSelecionado.getDestino() << " (" << pedidoSelecionado.getDestinoX() << "," << pedidoSelecionado.getDestinoY() << ")\n";
    std::cout << "-------------------------------------\n";
    std::cout << "DISTANCIA TOTAL DA ROTA: " << distanciaTotal << " unidades\n";
    std::cout << "=====================================\n\n";

    char confirmacao;
    std::cout << "Deseja confirmar esta entrega? (S/N): ";
    std::cin >> confirmacao;

    if (confirmacao == 'S' || confirmacao == 's') {
        // Atualiza o status do veículo para ocupado
        veiculo->setStatus(true);
        std::cout << "Simulando entrega... Veiculo " << veiculo->getPlaca() << " esta agora OCUPADO.\n";

        // Simula o final da entrega
        veiculo->setStatus(false);
        veiculo->setLocalAtual(pedidoSelecionado.getDestinoX(), pedidoSelecionado.getDestinoY());
        std::cout << "Entrega finalizada! Veiculo " << veiculo->getPlaca() << " agora esta DESOCUPADO e sua nova localizacao e (" << pedidoSelecionado.getDestinoX() << "," << pedidoSelecionado.getDestinoY() << ").\n";
        
        // Remove o pedido da lista de pendentes
        pedidos.erase(it);

        // Salva as alterações nos arquivos
        salvarListaCompletaNoArquivo();
        gerenciadorVeiculos.atualizarVeiculo(); // Usa o método de atualizar para salvar o estado do veículo
        
        std::cout << "Pedido removido da lista de pendentes e dados atualizados com sucesso.\n";
    } else {
        std::cout << "Operacao cancelada.\n";
    }
}

// (O resto do arquivo gerenciadorPedidos.cpp permanece o mesmo: criarPedido, listarPedidos, etc.)

// --- Implementação dos Métodos Públicos (CRUD) ---

void GerenciadorPedidos::criarPedido() {
    std::cout << "\n--- Adicionar Novo Pedido ---\n";
    std::string origem, destino;
    double peso;
    int origX, origY, destX, destY;

    // Ignora caracteres pendentes no buffer de entrada
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite o nome do local de origem: ";
    std::getline(std::cin, origem);
    std::cout << "Digite a coordenada X da origem: ";
    std::cin >> origX;
    std::cout << "Digite a coordenada Y da origem: ";
    std::cin >> origY;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer para o próximo getline

    std::cout << "Digite o nome do local de destino: ";
    std::getline(std::cin, destino);
    std::cout << "Digite a coordenada X do destino: ";
    std::cin >> destX;
    std::cout << "Digite a coordenada Y do destino: ";
    std::cin >> destY;


    std::cout << "Digite o peso do item (kg): ";
    std::cin >> peso;

    // Gera um novo ID único
    int novoId = gerarNovoId();

    // Adiciona o novo pedido à lista em memória
    pedidos.emplace_back(novoId, origem, destino, peso, origX, origY, destX, destY);

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
                      << " | Origem: " << pedido.getOrigem() << " (" << pedido.getOrigemX() << "," << pedido.getOrigemY() << ")"
                      << " | Destino: " << pedido.getDestino() << " (" << pedido.getDestinoX() << "," << pedido.getDestinoY() << ")"
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
        int novoOrigX, novoOrigY, novoDestX, novoDestY;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Digite o novo local de origem: ";
        std::getline(std::cin, novaOrigem);
        std::cout << "Digite a nova coordenada X da origem: ";
        std::cin >> novoOrigX;
        std::cout << "Digite a nova coordenada Y da origem: ";
        std::cin >> novoOrigY;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Digite o novo local de destino: ";
        std::getline(std::cin, novoDestino);
        std::cout << "Digite a nova coordenada X do destino: ";
        std::cin >> novoDestX;
        std::cout << "Digite a nova coordenada Y do destino: ";
        std::cin >> novoDestY;

        std::cout << "Digite o novo peso (kg): ";
        std::cin >> novoPeso;

        // Atualiza os dados do pedido encontrado
        it->setOrigem(novaOrigem);
        it->setOrigemCoords(novoOrigX, novoOrigY);
        it->setDestino(novoDestino);
        it->setDestinoCoords(novoDestX, novoDestY);
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