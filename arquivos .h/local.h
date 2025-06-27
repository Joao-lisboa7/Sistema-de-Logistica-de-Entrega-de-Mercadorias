#ifndef LOCAL_H
#define LOCAL_H

#include <string>

class Local {
private:
    std::string nome;
    int coordenadaX;
    int coordenadaY;

public:
    // Construtor padrão
    Local() : nome(""), coordenadaX(0), coordenadaY(0) {}
    
    // Construtor para facilitar a criação de um local
    Local(std::string nome, int x, int y) {
        this->nome = nome;
        this->coordenadaX = x;
        this->coordenadaY = y;
    }
    
    // Métodos getter
    std::string getNome() const { return nome; }
    int getCoordenadaX() const { return coordenadaX; }
    int getCoordenadaY() const { return coordenadaY; }
    
    // Métodos setter
    void setNome(const std::string& novoNome) { nome = novoNome; }
    void setCoordenadas(int x, int y) { 
        coordenadaX = x; 
        coordenadaY = y; 
    }
};

#endif // LOCAL_H