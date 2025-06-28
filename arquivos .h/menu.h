#ifndef MENU_H
#define MENU_H
#include <vector>
#include "veiculos.h"
#include "GerenciadorVeiculos.h"

#include "gerenciadorLocais.h"

class Menu{

  private:
    GerenciadorLocais gerenciadorLocais;
    
  public:
    void mostrarMenuPrincipal();
    void menuLocais();
    void menuVeiculos();
    void menuPedidos();

  private:
  GerenciadorVeiculos gerenciadorVeiculos;
};


#endif //MENU_H