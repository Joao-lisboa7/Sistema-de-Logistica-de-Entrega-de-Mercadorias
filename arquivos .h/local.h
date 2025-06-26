#ifndef LOCAL_H
#define LOCAL_H

#include <string>

class Local {
public:
    std::string nome;
    int coordenadaX;
    int coordenadaY;

    // Construtor para facilitar a criação de um local
    Local(std::string nome, int x, int y) {
        this->nome = nome;
        this->coordenadaX = x;
        this->coordenadaY = y;
    }
};

#endif // LOCAL_H