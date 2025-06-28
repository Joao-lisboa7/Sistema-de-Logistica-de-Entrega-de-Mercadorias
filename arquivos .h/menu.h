#ifndef MENU_H
#define MENU_H
#include <vector>
#include "veiculos.h"
#include "GerenciadorVeiculos.h"

class Menu{
  public:
    void mostrarMenuPrincipal();
    void menuLocais();
    void menuVeiculos();
    void menuPedidos();

  private:
  GerenciadorVeiculos gerenciadorVeiculos;
};


#endif //MENU_H