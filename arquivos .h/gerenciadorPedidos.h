#ifndef GERENCIADOR_PEDIDOS_H
#define GERENCIADOR_PEDIDOS_H

#include "pedido.h"
#include "gerenciadorVeiculos.h" 
#include "gerenciadorLocais.h" 
#include <vector>
#include <string>

class GerenciadorPedidos {
private:
    std::vector<Pedido> pedidos;
    GerenciadorVeiculos& gerenciadorVeiculos; 
    GerenciadorLocais& gerenciadorLocais;   
    const std::string nomeDoArquivo = "pedidos.dat";

    void carregarPedidosDoArquivo();
    void salvarListaCompletaNoArquivo() const;
    int gerarNovoId() const;
    std::vector<Pedido>::iterator encontrarPedidoPorId(int id);

public:
    // Construtor corrigido para aceitar ambas as referências
    GerenciadorPedidos(GerenciadorVeiculos& gv, GerenciadorLocais& gl);

    void criarPedido();
    void listarPedidos() const;
    void atualizarPedido();
    void excluirPedido();
    void calcularRotaDeEntrega(); 
};

#endif // GERENCIADOR_PEDIDOS_H