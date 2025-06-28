#include "pedido.h"
#include <string>
#include <cstring> // Para strncpy

// --- Implementação dos Construtores ---

Pedido::Pedido() : id(0), peso(0.0) {
    // Inicializa os arrays de char com terminador nulo
    origem[0] = '\0';
    destino[0] = '\0';
}

Pedido::Pedido(int id, const std::string& origem, const std::string& destino, double peso)
        : id(id), peso(peso) {
    // Copia os dados de std::string para os arrays de char de forma segura
    strncpy(this->origem, origem.c_str(), TAM_NOME_LOCAL - 1);
    this->origem[TAM_NOME_LOCAL - 1] = '\0'; // Garante terminação nula

    strncpy(this->destino, destino.c_str(), TAM_NOME_LOCAL - 1);
    this->destino[TAM_NOME_LOCAL - 1] = '\0'; // Garante terminação nula
}

// --- Implementação dos Métodos Get ---

int Pedido::getId() const {
    return id;
}

std::string Pedido::getOrigem() const {
    return std::string(origem);
}

std::string Pedido::getDestino() const {
    return std::string(destino);
}

double Pedido::getPeso() const {
    return peso;
}

// --- Implementação dos Métodos Set ---

void Pedido::setOrigem(const std::string& novaOrigem) {
    strncpy(this->origem, novaOrigem.c_str(), TAM_NOME_LOCAL - 1);
    this->origem[TAM_NOME_LOCAL - 1] = '\0';
}

void Pedido::setDestino(const std::string& novoDestino) {
    strncpy(this->destino, novoDestino.c_str(), TAM_NOME_LOCAL - 1);
    this->destino[TAM_NOME_LOCAL - 1] = '\0';
}

void Pedido::setPeso(double novoPeso) {
    this->peso = novoPeso;
}