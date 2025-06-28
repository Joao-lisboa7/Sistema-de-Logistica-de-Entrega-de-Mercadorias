#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>

class Pedido {
private:
    // Tamanho fixo para nomes, para facilitar a escrita/leitura binária
    static const int TAM_NOME_LOCAL = 50;

    int id; // Identificador único para cada pedido
    char origem[TAM_NOME_LOCAL];
    char destino[TAM_NOME_LOCAL];
    double peso;

public:
    // Construtor padrão
    Pedido();

    // Construtor parametrizado
    Pedido(int id, const std::string& origem, const std::string& destino, double peso);

    // --- Métodos Get ---
    int getId() const;
    std::string getOrigem() const;
    std::string getDestino() const;
    double getPeso() const;

    // --- Métodos Set ---
    // O ID não deve ser alterado após a criação
    void setOrigem(const std::string& novaOrigem);
    void setDestino(const std::string& novoDestino);
    void setPeso(double novoPeso);
};

#endif // PEDIDO_H