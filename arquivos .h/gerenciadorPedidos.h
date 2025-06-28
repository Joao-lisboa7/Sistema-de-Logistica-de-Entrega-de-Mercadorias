#ifndef GERENCIADOR_PEDIDOS_H
#define GERENCIADOR_PEDIDOS_H

#include "pedido.h"
#include <vector>
#include <string>

class GerenciadorPedidos {
private:
    std::vector<Pedido> pedidos;
    const std::string nomeDoArquivo = "pedidos.dat";

    // Métodos auxiliares privados
    void carregarPedidosDoArquivo();
    void salvarListaCompletaNoArquivo() const;
    int gerarNovoId() const;
    std::vector<Pedido>::iterator encontrarPedidoPorId(int id);

public:
    // Construtor
    GerenciadorPedidos();

    // Métodos CRUD públicos
    void criarPedido();
    void listarPedidos() const;
    void atualizarPedido();
    void excluirPedido();
};

#endif // GERENCIADOR_PEDIDOS_H