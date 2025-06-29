#include "gerenciadorPedidos.h"
#include "pedido.h"
#include "gerenciadorLocais.h" 
#include "local.h"            
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm> 
#include <cmath>     

// --- FUNÇÃO AUXILIAR ---
double calcularDistancia(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// --- Implementação do Construtor CORRIGIDA ---
GerenciadorPedidos::GerenciadorPedidos(GerenciadorVeiculos& gv, GerenciadorLocais& gl) 
    : gerenciadorVeiculos(gv), gerenciadorLocais(gl) {
    carregarPedidosDoArquivo();
}

// --- Implementação dos Métodos Públicos (CRUD) ---

void GerenciadorPedidos::criarPedido() {
    std::cout << "\n--- Adicionar Novo Pedido ---\n";
    std::string nomeOrigem, nomeDestino;
    double peso;
    int origX, origY, destX, destY;
    Local localEncontrado; // Agora o tipo 'Local' é reconhecido

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // --- LÓGICA PARA ORIGEM ---
    std::cout << "Digite o nome do local de ORIGEM: ";
    std::getline(std::cin, nomeOrigem);
    // A variável 'gerenciadorLocais' agora é reconhecida
    localEncontrado = gerenciadorLocais.encontrarLocalPorNome(nomeOrigem);

    if (!localEncontrado.getNome().empty()) {
        origX = localEncontrado.getCoordenadaX();
        origY = localEncontrado.getCoordenadaY();
        std::cout << "Local '" << nomeOrigem << "' encontrado! Coordenadas (" << origX << "," << origY << ") foram usadas.\n";
    } else {
        std::cout << "Local nao encontrado no catalogo. Por favor, insira as coordenadas manualmente.\n";
        std::cout << "Digite a coordenada X da origem: ";
        std::cin >> origX;
        std::cout << "Digite a coordenada Y da origem: ";
        std::cin >> origY;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }

    // --- LÓGICA PARA DESTINO ---
    std::cout << "\nDigite o nome do local de DESTINO: ";
    std::getline(std::cin, nomeDestino);
    localEncontrado = gerenciadorLocais.encontrarLocalPorNome(nomeDestino);
    
    if (!localEncontrado.getNome().empty()) {
        destX = localEncontrado.getCoordenadaX();
        destY = localEncontrado.getCoordenadaY();
        std::cout << "Local '" << nomeDestino << "' encontrado! Coordenadas (" << destX << "," << destY << ") foram usadas.\n";
    } else {
        std::cout << "Local nao encontrado no catalogo. Por favor, insira as coordenadas manualmente.\n";
        std::cout << "Digite a coordenada X do destino: ";
        std::cin >> destX;
        std::cout << "Digite a coordenada Y do destino: ";
        std::cin >> destY;
    }

    std::cout << "\nDigite o peso do item (kg): ";
    std::cin >> peso;

    int novoId = gerarNovoId();
    pedidos.emplace_back(novoId, nomeOrigem, nomeDestino, peso, origX, origY, destX, destY);
    salvarListaCompletaNoArquivo();
    std::cout << "Pedido (ID: " << novoId << ") adicionado com sucesso!\n";
}

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
        veiculo->setStatus(true);
        std::cout << "Simulando entrega... Veiculo " << veiculo->getPlaca() << " esta agora OCUPADO.\n";

        veiculo->setStatus(false);
        veiculo->setLocalAtual(pedidoSelecionado.getDestinoX(), pedidoSelecionado.getDestinoY());
        std::cout << "Entrega finalizada! Veiculo " << veiculo->getPlaca() << " agora esta DESOCUPADO e sua nova localizacao e (" << pedidoSelecionado.getDestinoX() << "," << pedidoSelecionado.getDestinoY() << ").\n";
        
        pedidos.erase(it);

        salvarListaCompletaNoArquivo();
        gerenciadorVeiculos.salvarDados(); 
        
        std::cout << "Pedido removido da lista de pendentes e dados atualizados com sucesso.\n";
    } else {
        std::cout << "Operacao cancelada.\n";
    }
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

void GerenciadorPedidos::carregarPedidosDoArquivo() {
    std::ifstream arquivo(nomeDoArquivo, std::ios::binary);
    if (!arquivo) {
        return;
    }
    pedidos.clear();
    Pedido pedidoLido;
    while (arquivo.read(reinterpret_cast<char*>(&pedidoLido), sizeof(Pedido))) {
        pedidos.push_back(pedidoLido);
    }
    arquivo.close();
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
}

int GerenciadorPedidos::gerarNovoId() const {
    if (pedidos.empty()) {
        return 1;
    }
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