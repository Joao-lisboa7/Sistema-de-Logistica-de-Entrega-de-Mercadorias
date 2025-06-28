#ifndef LOCAL_H
#define LOCAL_H

#include <string>
#include <cstring>

class Local {
private:
    static const int MAX_NOME = 50;
    char nome[MAX_NOME];
    int coordenadaX;
    int coordenadaY;

public:
    // Construtor padrão
    Local() : coordenadaX(0), coordenadaY(0) {
        nome[0] = '\0';
    }
    
    // Construtor para facilitar a criação de um local
    Local(const std::string& nomeStr, int x, int y) {
        strncpy(nome, nomeStr.c_str(), MAX_NOME - 1);
        nome[MAX_NOME - 1] = '\0';
        this->coordenadaX = x;
        this->coordenadaY = y;
    }
    
    // Métodos getter
    std::string getNome() const { return std::string(nome); }
    int getCoordenadaX() const { return coordenadaX; }
    int getCoordenadaY() const { return coordenadaY; }
    
    // Métodos setter
    void setNome(const std::string& novoNome) { 
        strncpy(nome, novoNome.c_str(), MAX_NOME - 1);
        nome[MAX_NOME - 1] = '\0';
    }
    void setCoordenadas(int x, int y) { 
        coordenadaX = x; 
        coordenadaY = y; 
    }
};

#endif // LOCAL_H