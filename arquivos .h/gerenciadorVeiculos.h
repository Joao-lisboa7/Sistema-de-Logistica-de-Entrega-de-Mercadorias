#ifndef GERENCIADOR_VEICULOS_H
#define GERENCIADOR_VEICULOS_H

#include <vector>
#include <string>
#include "veiculos.h"

class GerenciadorVeiculos {

public:
    GerenciadorVeiculos();
    void adicionarNovoVeiculo();
    void listarVeiculos() const;
    void excluirVeiculo();
    void atualizarVeiculo();
    Veiculos* encontrarVeiculoMaisProximo(int x, int y);
    void salvarDados() const; 

private: 
    std::vector<Veiculos> listaDeVeiculos;
    const std::string nomeDoArquivo = "veiculos.dat";

    void carregarVeiculosDoArquivo();
    void salvarListaCompletaNoArquivo() const; 
    Veiculos pedirDadosParaNovoVeiculo();
};

#endif