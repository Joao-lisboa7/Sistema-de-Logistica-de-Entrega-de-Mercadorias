#include <iostream>
#include "menu.h" 

int main() {
    std::cout << "\n=== Sistema de Logistica de Entrega ===\n" << std::endl;

    Menu menu; 
    menu.mostrarMenuPrincipal();

    std::cout << "\nPrograma finalizado com sucesso!" << std::endl;
    return 0;
}