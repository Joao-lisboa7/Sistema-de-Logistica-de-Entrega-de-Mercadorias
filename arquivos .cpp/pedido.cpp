#include "pedido.h"
#include <string>
#include <cstring> // Para strncpy

// --- Implementação dos Construtores ---

Pedido::Pedido() : id(0), peso(0.0), origemX(0), origemY(0), destinoX(0), destinoY(0) {
    // Inicializa os arrays de char com terminador nulo
    origem[0] = '\0';
    destino[0] = '\0';
}

Pedido::Pedido(int id, const std::string& origem, const std::string& destino, double peso, int origX, int origY, int destX, int destY)
        : id(id), peso(peso), origemX(origX), origemY(origY), destinoX(destX), destinoY(destY) {
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

int Pedido::getOrigemX() const {
    return origemX;
}

int Pedido::getOrigemY() const {
    return origemY;
}

int Pedido::getDestinoX() const {
    return destinoX;
}

int Pedido::getDestinoY() const {
    return destinoY;
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

void Pedido::setOrigemCoords(int x, int y) {
    origemX = x;
    origemY = y;
}

void Pedido::setDestinoCoords(int x, int y) {
    destinoX = x;
    destinoY = y;
}