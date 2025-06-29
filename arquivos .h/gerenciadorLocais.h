#ifndef GERENCIADORLOCAIS_H
#define GERENCIADORLOCAIS_H

#include <vector>
#include <string>
#include "local.h"

class GerenciadorLocais {
public: // --- Métodos que o Menu pode acessar ---
    GerenciadorLocais();
    void criarLocal();
    void listarLocais() const;
    void atualizarLocal();
    void excluirLocal();
    Local encontrarLocalPorNome(const std::string& nome); // --- MOVIDO PARA PUBLIC ---

private: 
    std::vector<Local> locais;
    const std::string nomeDoArquivo = "locais.dat";

    // Métodos auxiliares para manipulação de arquivos
    void carregarLocaisDoArquivo();
    void salvarListaCompletaNoArquivo() const;

    // Método auxiliar para obter dados do usuário
    bool pedirDadosParaLocal(std::string& nome, int& x, int& y);

    // std::vector<Local>::iterator encontrarLocalPorNome(const std::string& nome); // Versão antiga removida
};

#endif // GERENCIADORLOCAIS_H