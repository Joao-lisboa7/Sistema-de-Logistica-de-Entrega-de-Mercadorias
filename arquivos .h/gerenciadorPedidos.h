#ifndef GERENCIADOR_PEDIDOS_H
#define GERENCIADOR_PEDIDOS_H

#include "pedido.h"
#include "gerenciadorVeiculos.h" // --- ADICIONADO ---
#include <vector>
#include <string>

class GerenciadorPedidos {
private:
    std::vector<Pedido> pedidos;
    GerenciadorVeiculos& gerenciadorVeiculos; // --- ADICIONADO ---
    const std::string nomeDoArquivo = "pedidos.dat";

    // Métodos auxiliares privados
    void carregarPedidosDoArquivo();
    void salvarListaCompletaNoArquivo() const;
    int gerarNovoId() const;
    std::vector<Pedido>::iterator encontrarPedidoPorId(int id);

public:
    // Construtor
    GerenciadorPedidos(GerenciadorVeiculos& gv); // --- MODIFICADO ---

    // Métodos CRUD públicos
    void criarPedido();
    void listarPedidos() const;
    void atualizarPedido();
    void excluirPedido();
    void calcularRotaDeEntrega(); // --- NOVO MÉTODO ---
};

#endif // GERENCIADOR_PEDIDOS_H