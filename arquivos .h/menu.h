#ifndef MENU_H
#define MENU_H

#include "gerenciadorLocais.h"

class Menu{

  private:
    GerenciadorLocais gerenciadorLocais;
    
  public:
    void mostrarMenuPrincipal();
    void menuLocais();
    void menuVeiculos();
    void menuPedidos();
};


#endif //MENU_H