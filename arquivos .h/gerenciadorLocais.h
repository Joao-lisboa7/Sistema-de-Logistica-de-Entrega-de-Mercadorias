#ifndef GERENCIADORLOCAIS_H
#define GERENCIADORLOCAIS_H

#include <vector>
#include <string>
#include "local.h" // Garanta que este arquivo defina a classe/struct Local

class GerenciadorLocais {
public: // --- Métodos que o Menu pode acessar ---
    GerenciadorLocais();
    void criarLocal();
    void listarLocais() const;
    void atualizarLocal();
    void excluirLocal();

private: // --- Detalhes internos que o Menu não precisa conhecer ---
    std::vector<Local> locais;
    const std::string nomeDoArquivo = "locais.dat";

    // Métodos auxiliares para manipulação de arquivos
    void carregarLocaisDoArquivo();
    void salvarListaCompletaNoArquivo() const;

    // Método auxiliar para obter dados do usuário
    bool pedirDadosParaLocal(std::string& nome, int& x, int& y);

    // Método auxiliar para encontrar um local
    std::vector<Local>::iterator encontrarLocalPorNome(const std::string& nome);
};

#endif // GERENCIADORLOCAIS_H
