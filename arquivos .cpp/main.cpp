#include <iostream>
#include "menu.h" 

int main() {
    // Mensagem para provar que o programa começou
    std::cout << "O programa iniciou com sucesso!" << std::endl;
    std::cout << "Pressione Enter para mostrar o menu..." << std::endl;
    std::cin.get(); // Pausa e espera o usuário pressionar Enter

    Menu menu; 
    menu.mostrarMenuPrincipal();

    // Mensagem para provar que o programa terminou
    std::cout << "\nO programa terminou. Pressione Enter para fechar." << std::endl;
    std::cin.ignore(); // Limpa qualquer input residual
    std::cin.get(); // Pausa novamente antes de fechar

    return 0;
}