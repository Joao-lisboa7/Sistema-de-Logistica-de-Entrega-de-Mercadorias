#ifndef MENU_H
#define MENU_H
#include <vector>
#include "veiculos.h"
#include "gerenciadorVeiculos.h"
#include "gerenciadorLocais.h"
#include "gerenciadorPedidos.h"

class Menu{
    
  public:
    Menu(); 
    void mostrarMenuPrincipal();
    void menuLocais();
    void menuVeiculos();
    void menuPedidos();

  private:
    GerenciadorLocais gerenciadorLocais;
    GerenciadorVeiculos gerenciadorVeiculos;
    GerenciadorPedidos gerenciadorPedidos;
};


#endif //MENU_H