#ifndef GERENCIADOR_VEICULOS_H
#define GERENCIADOR_VEICULOS_H

#include <vector>
#include <string>
#include "veiculos.h"



class GerenciadorVeiculos {

public: // --- Métodos que o Menu pode acessar ---
    GerenciadorVeiculos();
    void adicionarNovoVeiculo();
    void listarVeiculos() const;
    void excluirVeiculo();

private: // --- Detalhes internos que o Menu não precisa conhecer ---
    // A lista de veículos fica aqui, sob a responsabilidade do gerenciador.
    std::vector<Veiculos> listaDeVeiculos;
    const std::string nomeDoArquivo = "veiculos.dat";

    void carregarVeiculosDoArquivo();
    void salvarVeiculoNoArquivo(const Veiculos& veiculo);
    Veiculos pedirDadosParaNovoVeiculo();

    void salvarListaCompletaNoArquivo() const;
};

#endif