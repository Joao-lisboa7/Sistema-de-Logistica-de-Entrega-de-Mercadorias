#ifndef GERENCIADORLOCAIS_H
#define GERENCIADORLOCAIS_H

#include <vector>
#include <string>
#include "local.h" // Certifique-se de que este arquivo define a classe/struct Local

class GerenciadorLocais {
public:
    // --- Métodos Públicos ---
    GerenciadorLocais(); // Construtor para carregar os locais do arquivo
    void criarLocal();
    void listarLocais();
    void atualizarLocal();
    void excluirLocal();

private:
    // --- Atributos e Métodos Privados ---
    std::vector<Local> locais;
    const std::string nomeDoArquivo = "locais.dat";

    void carregarLocaisDoArquivo();
    void salvarLocaisNoArquivo();
};

#endif // GERENCIADORLOCAIS_H