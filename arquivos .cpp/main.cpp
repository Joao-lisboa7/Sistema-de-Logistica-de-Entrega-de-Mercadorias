#include <iostream>
#include "menu.h"
using namespace std;

int main(){
  std::cout << "\n=== Sistema de Logistica de Entrega ===\n";
  
  Menu meuMenu;
  meuMenu.mostrarMenuPrincipal();

  cout << "\nPrograma finalizado com sucesso!";

  return 0;
}