#ifndef GERENCIADORLOCAIS_H
#define GERENCIADORLOCAIS_H

#include <vector>
#include "local.h"

class GerenciadorLocais {
private:
    std::vector<Local> locais;

public:
    void criarLocal();
    void listarLocais();
    void atualizarLocal();
    void excluirLocal();
};

#endif // GERENCIADORLOCAIS_H