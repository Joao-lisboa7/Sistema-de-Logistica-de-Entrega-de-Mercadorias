#include <iostream>
#include "menu.h"
using namespace std;

int main(){
  std::cout << "=== Sistema de Logistica de Entrega ===\n";
  
  Menu meuMenu;
  meuMenu.mostrarMenuPrincipal();

  cout << "\nPrograma finalizado com sucesso!\n";

  return 0;
}